#include "PlayScene.h"
#include<iostream>
extern bool Enter[3];
extern bool TurnOn[4];
extern vector<BaseObject*> _listObject;
vector<BaseObject*> Stair[2];
using namespace std;
ViewPort* PlayScene::_viewport = ViewPort::getInstance();
PlayScene::PlayScene()
{
	
}

PlayScene::~PlayScene()
{
	delete _viewport;
	_viewport = nullptr;
}

void PlayScene::setViewPort(ViewPort * viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

bool PlayScene::InIt()
{
	mMap = new ReadMapEditor("Resources/Images/mapobject.tmx", _root);

	//_activeObject = mMap->GetList(rect);
	//Chú ý: Top Left của land ở bên dưới chứ không ở trên
	//  **********(B,R)
	//	**********
	//  **********
	//  **********
	//	**********
	//  **********
	// (T,L) (x,y)

	TurnOn[0] = true;	
	//Bật thang 2
	Enter[0] = false; //Check 1
	CheckOn[0].push_back(new Land(2660, 688-67-591, 5, 67, eDirection::TOP, eLandType::CHECKSTAIR1));
	CheckOn[1].push_back(new Land(2645, 688 - 67 - 593, 5, 67, eDirection::TOP, eLandType::CHECKSTAIR2));
	//Bậc thang 3
	Enter[1] = false;  //Check 2
	CheckOn[2].push_back(new Land(2245, 688 - 86 - 492, 5, 86, eDirection::TOP, eLandType::CHECKSTAIR3));
	CheckOn[3].push_back(new Land(2269, 688 - 83 - 493, 5, 83, eDirection::TOP, eLandType::CHECKSTAIR4));

	//Background
	_background = new BackGround();
	_background->InIt();

	_backgroundfront = new BackGroundFront();
	_backgroundfront->InIt();



    _aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(2000, 600);
	_listObject.push_back(_aladdin);

	return true;
}

void PlayScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void PlayScene::Update(float dt)
{
	this->UpdateViewport(_aladdin);

	Vector2 viewport_position = _viewport->getPositionWorld();
	RECT viewport_in_transform = _viewport->getBounding();
	//// Hàm getlistobject của quadtree yêu cầu truyền vào một hình chữ nhật theo hệ top left, nên cần tính lại khung màn hình
	
	RECT screenx;
	screenx.top = viewport_in_transform.bottom;
	screenx.bottom = viewport_in_transform.top;
	screenx.left = viewport_in_transform.left;
	screenx.right = viewport_in_transform.left + WINDOWS_WIDTH;

#if _DEBUG									 // clock_t để test thời gian chạy đoạn code update (milisecond)
	clock_t t;
	t = clock();
#endif
	_activeObject.clear();
	mMap->ListObject(&screenx);	
	_activeObject = mMap->GetList;
#if _DEBUG
	t = clock() - t;
	__debugoutput((float)t / CLOCKS_PER_SEC);
#endif

	_aladdin->Update(dt);

	for each (auto object in _activeObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY)|| object->getId()==LAND)
			continue;
		object->Update(dt);
	}

	/*Check collision aladdin with land
	@i Object*/
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
		if (i->getId() != eID::LAND || _aladdin->getId() == temp)
			continue;
		_aladdin->checkCollision(i, dt);
	}


	/*Check collision (*1)enermy with (*2)aladdin (chú ý thứ tự )
	@i Enermyobject*/
	for (auto obj : _activeObject)
	{
		// obj la Enermy va aladdin
		if (obj == nullptr)
			continue;

		eID temp = obj->getId();
		if (temp == LAND || temp == ALADDIN || obj->getStatus()==DESTROY)
			continue;	
		obj->checkCollision(_aladdin, dt);
	}

	
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
}

void PlayScene::Draw(LPD3DXSPRITE spriteHandle)
{
    _background->Draw(spriteHandle,_viewport);
	for each (auto object in _activeObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY))
			continue;
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}
	_aladdin->Draw(spriteHandle, _viewport);
	

	for each(auto object in Stair[0])
	{
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}
	for each(auto object in Stair[1])
	{
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}

#pragma region Draw check stair
	if (TurnOn[0]) {
		CheckOn[0].back()->Draw(spriteHandle, _viewport);
		CheckOn[0].back()->ShowBB();
	}
	if (TurnOn[1]) {
		CheckOn[1].back()->Draw(spriteHandle, _viewport);
		CheckOn[1].back()->ShowBB();
	}
	if (TurnOn[2]) {
		CheckOn[2].back()->Draw(spriteHandle, _viewport);
		CheckOn[2].back()->ShowBB();
	}
	if (TurnOn[3]) {
		CheckOn[3].back()->Draw(spriteHandle, _viewport);
		CheckOn[3].back()->ShowBB();
	}

#pragma endregion
	_backgroundfront->Draw(spriteHandle, _viewport);
}

void PlayScene::Release()
{
	for each (auto object in _listObject)
	{
		object->Release();
	}

	for each (auto object in _activeObject)
	{
		object->Release();
	}
	_background->Release();
	_backgroundfront->Release();
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
	_viewport->setPositionWorld(new_position);
}