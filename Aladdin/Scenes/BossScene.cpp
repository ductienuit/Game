#include "BossScene.h"
#include<iostream>
using namespace std;

extern vector<BaseObject*> listActive; 
extern vector<BaseObject*> _listObject;
vector<BaseObject*>	listStrip;

ViewPort* BossScene::_viewport = ViewPort::getInstance();
BossScene::BossScene()
{
	ViewPort::getInstance()->setPositionWorld(Vector2(0, 480));

	InforAladdin::getInstance()->NonInfinity();
	_listObject.clear();
}

BossScene::~BossScene()
{
	
	//delete _viewport;
	//_viewport = nullptr;
}

bool BossScene::InIt()
{

	_aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(100, 300);

	mMap = new ReadMapEditor(_aladdin,"Resources/Images/Boss/boss.tmx", _root,true);

	_back = new BackGroundBossBack();

	_front = new BackGroundBossFront();
	_front->InIt();

	_scoreAla = InforAladdin::getInstance();


	_boss = new Boss(PULL_LEFT, 757, (691-492-148), _aladdin);
	_boss->InIt();

	_listScore.push_back(new Health(_aladdin));
	_listScore.push_back(new Life());
	_listScore.push_back(new Coin());
	_listScore.push_back(new Apple());

	//âm thanh
	//SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli_loop.mp3", 1);
	return true;
}

void BossScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void BossScene::Update(float dt)
{
	if (_boss->getHitpoint() <= 0)
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

	_activeObject.clear();
	mMap->ListObject(&screenx,_boss->isVersion2());
	_activeObject = mMap->GetList;
	listActive.push_back(_boss);

#pragma endregion

	RECT sizeMap;
	sizeMap.left = 0;
	sizeMap.top = 0;
	sizeMap.bottom = SIZEMAPBOSS.y;
	sizeMap.right = SIZEMAPBOSS.x;
	_boss->OptimizeFire(&sizeMap);


	_aladdin->Update(dt);

	_boss->Update(dt);


	for each (auto object in _activeObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY) || object->getId() == LAND)
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

	_boss->checkCollision(_aladdin, dt);


	//Object nổ khi táo va chạm 
	for (int i = 0; i < listStrip.size(); i++)
	{
		if (listStrip[i]->isInStatus(DESTROY))
		{
			listStrip[i]->Release();
			delete listStrip[i];
			listStrip.erase(listStrip.begin() + i);
		}
		else
			listStrip[i]->Update(dt);
	}
	

	//Cập nhật điểm, máu, táo, mạng sống trên màn hình
	for each(auto score in _listScore)
		score->Update(dt);

	_back->Update(dt);



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
	if (input->isKeyDown(DIK_5))
	{
		InforAladdin::getInstance()->Infinity();
	}
	#pragma endregion

}

void BossScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_back->Draw(spriteHandle, _viewport);
	_front->Draw(spriteHandle, _viewport);
	for each (auto object in _activeObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY))
			continue;
		object->Draw(spriteHandle, _viewport);
	}
	_boss->Draw(spriteHandle, _viewport);
	_aladdin->Draw(spriteHandle, _viewport);


	

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
		_boss->ShowBB();
	}

#pragma endregion

	for each(auto score in _listScore)
		score->Draw(spriteHandle, _viewport);

	for (int i = 0; i<listStrip.size(); i++)
	{
		if (listStrip[i]->isInStatus(DESTROY))
		{
			listStrip[i]->Release();
			delete listStrip[i];
			listStrip.erase(i + listStrip.begin());
		}
		else listStrip[i]->Draw(spriteHandle, _viewport);
	}
}

void BossScene::Release()
{
	for each (auto object in _activeObject)
	{
		object->Release();

		delete object;
	}
	_activeObject.clear();

	_back->Release();
	delete _back;

	_front->Release();
	delete _front;

	_aladdin->Release();
	delete  _aladdin;

	_boss->Release();
	delete _boss;

	for each (auto object in _listScore)
	{
		object->Release();

		delete object;
	}
	_listScore.clear();



	auto _input= InputController::getInstance();
	if (_input != nullptr)
		__unhook(_input);

	SoundManager::getInstance()->StopAllSound();
}

void BossScene::UpdateViewport(BaseObject * aladdin)
{
	// Vị trí hiện tại của viewport. 
	Vector2 current_position = _viewport->getPositionWorld();
	//Kích thước của map
	Vector2 worldsize = Vector2(SIZEMAPBOSS.x, SIZEMAPBOSS.y);
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