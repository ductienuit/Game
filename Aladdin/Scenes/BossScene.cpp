#include "BossScene.h"
#include<iostream>
using namespace std;


ViewPort* BossScene::_viewport = ViewPort::getInstance();
BossScene::BossScene()
{

}

BossScene::~BossScene()
{
	delete _viewport;
	_viewport = nullptr;
}

bool BossScene::InIt()
{
	mMap = new ReadMapEditor("Resources/Images/Boss/boss.tmx", _root,true);

	//Background
	_back = new BackGroundBoss();
	_back->InIt();

	_front = new BackGroundBossFront();
	_front->InIt();

	_scoreAla = InforAladdin::getInstance();

	_aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(100, 300);

	_listScore.push_back(new Health(_aladdin));
	_listScore.push_back(new Life());
	_listScore.push_back(new Coin());
	_listScore.push_back(new Apple());

	//âm thanh
	SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli_loop.mp3", 1);
	return true;
}

void BossScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void BossScene::Update(float dt)
{
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
	mMap->ListObject(&screenx);
	_activeObject = mMap->GetList;

#pragma endregion

	_aladdin->Update(dt);


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

	//Cập nhật điểm, máu, táo, mạng sống trên màn hình
	for each(auto score in _listScore)
		score->Update(dt);
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
	}

#pragma endregion

	for each(auto score in _listScore)
		score->Draw(spriteHandle, _viewport);
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

	for each (auto object in _listScore)
	{
		object->Release();

		delete object;
	}
	_listScore.clear();
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