#include "PlayScene.h"
#include<iostream>
extern bool Enter[3];
extern bool TurnOn[4];
extern vector<BaseObject*> _listObject;
extern vector<BaseObject*> listFireActive;
extern vector<BaseObject*> listApple;
void OptimizeApple(RECT* rect);
bool isContain(BaseObject*object, RECT rect1);
vector<BaseObject*> Stair[2];
using namespace std;


ViewPort* PlayScene::_viewport = ViewPort::getInstance();
PlayScene::PlayScene()
{
	ViewPort::getInstance()->setPositionWorld(Vector2(0, 480));

	InforAladdin::getInstance()->NonInfinity();
}

PlayScene::~PlayScene()
{
}

void PlayScene::setViewPort(ViewPort * viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

bool PlayScene::InIt()
{
	Enter[2] = true;
	_aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(100, 100);

	//_aladdin->setPosition(3169*1.6, (688-376)*1.92);
   // _aladdin->setPosition(7100, 1000);
	_listObject.push_back(_aladdin);

	mMap = new ReadMapEditor(_aladdin,"Resources/Images/mapobject.tmx", _root);
	TurnOn[0] = true;	
	//Bật thang 2
	Enter[0] = false; //Check 1
	CheckOn[0].push_back(new Land(2660, 688-67-591, 5, 67, eDirection::TOP, eLandType::CHECKSTAIR1));
	CheckOn[1].push_back(new Land(2645, 688 - 67 - 593, 5, 67, eDirection::TOP, eLandType::CHECKSTAIR2));
	//Bậc thang 3
	Enter[1] = false;  //Check 2
	CheckOn[2].push_back(new Land(2245, 688 - 86 - 492, 5, 86, eDirection::TOP, eLandType::CHECKSTAIR3));
	CheckOn[3].push_back(new Land(2269, 688 - 83 - 493, 5, 83, eDirection::TOP, eLandType::CHECKSTAIR4));

	Vitory = new Land(4721, 688 - 11 - 200, 11, 11, eDirection::TOP, eLandType::VICTORY);

	//Background
	_background = new BackGround();
	_background->InIt();

	_backgroundfront = new BackGroundFront();
	_backgroundfront->InIt();

	_scoreAla = InforAladdin::getInstance();



	_listScore.push_back(new Health(_aladdin));
	_listScore.push_back(new Life());
	_listScore.push_back(new Coin());
	_listScore.push_back(new Apple());

	//âm thanh
	SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli_loop.mp3", 1);
	return true;
}

void PlayScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void PlayScene::Update(float dt)
{
	//Kiem tra win game
	_aladdin->checkCollision(Vitory, dt);
	if (Enter[2])
	{
		SceneManager::getInstance()->ReplaceScene(new EndScene());
		return;
	}

	this->UpdateViewport(_aladdin);

	#pragma region  Update list object in camera
	Vector2 viewport_position = _viewport->getPositionWorld();
	RECT viewport_in_transform = _viewport->getBounding();
	//// Hàm getlistobject của quadtree yêu cầu truyền vào một hình chữ nhật theo hệ top left, nên cần tính lại khung màn hình

	RECT screenx;
	screenx.top = viewport_in_transform.bottom;
	screenx.bottom = viewport_in_transform.top;
	screenx.left = viewport_in_transform.left;
	screenx.right = viewport_in_transform.left + WINDOWS_WIDTH;

	//#if _DEBUG									 // clock_t để test thời gian chạy đoạn code update (milisecond)
	//	clock_t t;
	//	t = clock();
	//#endif
	_activeObject.clear();
	mMap->ListObject(&screenx);
	_activeObject = mMap->GetList;

	//	t = clock() - t;
	//	__debugoutput((float)t / CLOCKS_PER_SEC);
	//#endif
#pragma endregion


	#pragma region Optimize apple in camera
	OptimizeApple(&screenx);
	#pragma endregion


	_aladdin->Update(dt);


	for each (auto object in _activeObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY)|| object->getId()==LAND)
			continue;
		object->Update(dt);
	}

	#pragma region Check collision witch land and enermy

	/*Check collision aladdin with land*/
	for (auto i : _activeObject)
	{
		// i la Enermy va aladdin
		if (i == nullptr)
			continue;
		eID temp = i->getId();

		/*Fallingplatform cần kiểm tra riêng
		aladdin với nó và ngược lại ở for dưới*/
		if (temp == eID::FALLINGPLATFORM)
			_aladdin->checkCollision(i, dt);
		if (temp == eID::CAMEL)
			_aladdin->checkCollision(i, dt);
		if (temp == eID::SPRING)
			_aladdin->checkCollision(i, dt);
		if (i->getId() != eID::LAND || _aladdin->getId() == temp)
			continue;
		_aladdin->checkCollision(i, dt);
	}


	/*Check collision (*1)enermy with (*2)aladdin (chú ý thứ tự )*/
	for (auto obj : _activeObject)
	{
		// obj la Enermy va aladdin
		if (obj == nullptr)
			continue;

		eID temp = obj->getId();
		if (temp == LAND || temp == ALADDIN || obj->getStatus() == DESTROY)
			continue;
		obj->checkCollision(_aladdin, dt);
	}


#pragma endregion


	#pragma region Flag check stair

	if (Enter[0])
	{
		for (auto i : Stair[0])
		{
			// i la Enermy va aladdin
			if (i == nullptr)
				continue;
			_aladdin->checkCollision(i, dt);
		}
	}
	if (Enter[1])
	{
		for (auto i : Stair[1])
		{
			// i la Enermy va aladdin
			if (i == nullptr)
				continue;
			_aladdin->checkCollision(i, dt);
		}
	}

	#pragma region TurnOn check stair
	if (TurnOn[0]) {
		_aladdin->checkCollision(CheckOn[0].back(), dt);
	}
	if (TurnOn[1]) {
		_aladdin->checkCollision(CheckOn[1].back(), dt);
	}
	if (TurnOn[2]) {
		_aladdin->checkCollision(CheckOn[2].back(), dt);
	}
	if (TurnOn[3]) {
		_aladdin->checkCollision(CheckOn[3].back(), dt);
	}

#pragma endregion


#pragma endregion


	//Cập nhật điểm, máu, táo, mạng sống trên màn hình
	for each(auto score in _listScore)
		score->Update(dt);



#pragma region Hack Game
	auto input = InputController::getInstance();
	if (input->isKeyDown(DIK_1))
	{
		InforAladdin::getInstance()->plusApple(100);
	}
	if (input->isKeyDown(DIK_2))
	{
		InforAladdin::getInstance()->plusHealth(100);
	}
	if (input->isKeyDown(DIK_3))
	{
		InforAladdin::getInstance()->plusCoin(100);
	}
	if (input->isKeyDown(DIK_4))
	{
		InforAladdin::getInstance()->plusLife(3);
	}
#pragma endregion
}

void PlayScene::Draw(LPD3DXSPRITE spriteHandle)
{
    _background->Draw(spriteHandle,_viewport);
	for each (auto object in _activeObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY))
			continue;
		object->Draw(spriteHandle, _viewport);
	}
	_aladdin->Draw(spriteHandle, _viewport);

	for each(auto object in Stair[0])
	{
		object->Draw(spriteHandle, _viewport);
	}
	for each(auto object in Stair[1])
	{
		object->Draw(spriteHandle, _viewport);
	}

	#pragma region Draw check stair
	if (TurnOn[0]) {
		CheckOn[0].back()->Draw(spriteHandle, _viewport);
	}
	if (TurnOn[1]) {
		CheckOn[1].back()->Draw(spriteHandle, _viewport);
	}
	if (TurnOn[2]) {
		CheckOn[2].back()->Draw(spriteHandle, _viewport);
	}
	if (TurnOn[3]) {
		CheckOn[3].back()->Draw(spriteHandle, _viewport);
	}

#pragma endregion

	_backgroundfront->Draw(spriteHandle, _viewport);


	#pragma region F1 to show all bounding box
	//Vẽ bounding
	auto _input = InputController::getInstance();
	if (_input->isKeyDown(DIK_F1))
	{
		for each (auto object in _activeObject)
		{
			if (object == nullptr || object->isInStatus(DESTROY))
				continue;
			object->ShowBB();
		}
		_aladdin->ShowBB();

		for each(auto object in Stair[0])
		{
			object->ShowBB();
		}
		for each(auto object in Stair[1])
		{
			object->ShowBB();
		}

		if (TurnOn[0]) {
			CheckOn[0].back()->ShowBB();
		}
		if (TurnOn[1]) {
			CheckOn[1].back()->ShowBB();
		}
		if (TurnOn[2]) {
			CheckOn[2].back()->ShowBB();
		}
		if (TurnOn[3]) {
			CheckOn[3].back()->ShowBB();
		}
	}

#pragma endregion

	for each(auto score in _listScore)
		score->Draw(spriteHandle, _viewport);
}

void PlayScene::Release()
{
	for each (auto object in _listObject)
	{
		object->Release();
		delete object;
	}
	_listObject.clear();
	for each (auto object in _activeObject)
	{
		object->Release();

		delete object;
	}
	_activeObject.clear();

	_background->Release();
	delete _background;
	_backgroundfront->Release();
	delete _backgroundfront;

	for each (auto object in _listScore)
	{
		object->Release();

		delete object;
	}
	_listScore.clear();

	auto _input = InputController::getInstance();
	if (_input != nullptr)
		__unhook(_input);

	TurnOn[0] = true;
	TurnOn[1] = false;
	TurnOn[2] = false;
	TurnOn[3] = false;
	Enter[0] = false;
	Enter[1] = false;
	Enter[2] = false;

	SoundManager::getInstance()->StopAllSound();
}

void PlayScene::UpdateViewport(BaseObject * aladdin)
{
	// Vị trí hiện tại của viewport. 
	Vector2 current_position = _viewport->getPositionWorld();
	//Kích thước của map
	Vector2 worldsize = Vector2(SIZEMAP.x, SIZEMAP.y);
	// Bám theo object.
	float y = aladdin->getPositionY() - WINDOWS_HEIGHT;
	Vector2 new_position =
		/*Khi max ở đây sẽ cho mình biết khi nào camera sẽ đi theo aladdin 
		và khi nào không*/
		Vector2(max(aladdin->getPositionX() - 320, 0),
			max(aladdin->getPositionY() + 280, WINDOWS_HEIGHT));		
	// 320 va 280 khoảng cách hardcode dựa vào test thực tế.
																		
	if (new_position.x + WINDOWS_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOWS_WIDTH;
	}
	if (new_position.y > worldsize.y)
	{
		new_position.y = worldsize.y;
	}
	_viewport->setPositionWorld(new_position);
}

void OptimizeApple(RECT* rect)
{
	for (size_t i = 0; i < listApple.size(); i++)
	{
		RECT apple = listApple[i]->getBounding();
		RECT temp = *rect;
		temp.top = apple.bottom;

		if (!isContain(listApple[i], temp))
		{
			listApple[i]->Release();
			delete listApple[i];
			listApple.erase(listApple.begin() + i);
		}
	}
}

bool isContain(BaseObject*object, RECT rect1)
{
	/*25/11 Đức Tiến đã sửa*/
	RECT rect2 = object->getBounding();
	swap(rect2.top, rect2.bottom);
	return !(rect2.left > rect1.right || rect2.right < rect1.left || rect2.top > rect1.bottom || rect2.bottom < rect1.top);
}