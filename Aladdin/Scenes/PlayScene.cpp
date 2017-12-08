﻿#include "PlayScene.h"
#include<iostream>
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
	//Chú ý: Top Left của land ở bên dưới chứ không ở trên
	//  **********(B,R)
	//	**********
	//  **********
	//  **********
	//	**********
	//  **********
	// (T,L)


	//Tường
	_listObject.push_back(new Land(1432, 0, 51, 110, eDirection::INSIDE, eLandType::WALL));



	//Dây và cục chặn
	_listObject.push_back(new Land(2084, 105, 10, 200, eDirection::INSIDE, eLandType::CLIMBABLE0));
	_listObject.push_back(new Land(2084, 333, 20, 20, eDirection::BOTTOM, eLandType::STOP));
	_listObject.push_back(new Land(1541, 688-333, 10, 157, eDirection::INSIDE, eLandType::CLIMBABLE0));
	_listObject.push_back(new Land(1541, 688-149, 20, 20, eDirection::BOTTOM, eLandType::STOP));

	//Thanh xà ngang
	_listObject.push_back(new Land(130, 850, 800, 30, eDirection::BOTTOM, eLandType::BAR));
	//Nền
	_listObject.push_back(new Land(1454, 12, 4771, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(5, 50, 1454, 10, eDirection::TOP, eLandType::SOLID));
	//Miến gỗ đứng rớt
	_listObject.push_back(new Land(1641, 239, 36, 10, eDirection::TOP, eLandType::SOLID));
	//Miến gỗ đứng ko rớt
	_listObject.push_back(new Land(1757, 239, 284, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1477, 688-451, 102, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1477, 688-402, 40, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1585, 688 - 292, 685, 10, eDirection::TOP, eLandType::SOLID));
	//Bật thang
	_listObject.push_back(new Land(1146, 0, 43, 71, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1189, 0, 43, 79, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1229, 0, 43, 87, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1266, 0, 43, 95, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1307, 0, 43, 103, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1347, 0, 43, 111, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1387, 0, 43, 119, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1430, 110, 43, 10, eDirection::TOP, eLandType::STAIR));
	//platform

	_background = new BackGround();
	_background->InIt();

	_backgroundfront = new BackGroundFront();
	_backgroundfront->InIt();

	auto guardLu = new GuardLu(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	guardLu->InIt();
	_listObject.push_back(guardLu);
	guardLu->setPositionY(0);

	/*auto guardThin = new GuardThin(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	guardThin->InIt();
	_listObject.push_back(guardThin);

	auto guardShort = new GuardShort(eStatus::MOVING_LEFT, 600, 140, eDirection::LEFT);
	guardShort->InIt();
	_listObject.push_back(guardShort);*/

    _aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(1053,250);
	_listObject.push_back(_aladdin);

	return true;
}

void PlayScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void PlayScene::Update(float dt)
{

	/*char str[100];
	sprintf(str, "delta time: %f", dt);
	_text->setText(str);*/
	
	
	this->UpdateViewport(_aladdin);

	for each (auto object in _listObject)
	{
		object->Update(dt);
	}

	for(auto i : _listObject)
		for (auto j : _listObject)
		{
			if (i->getId() != j->getId())
				i->checkCollision(j, dt);
		}
}

void PlayScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_background->Draw(spriteHandle,_viewport);
	for each (auto object in _listObject)
	{
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}
	_backgroundfront->Draw(spriteHandle, _viewport);
}

void PlayScene::Release()
{
	for each (auto object in _listObject)
	{
		object->Release();
	}
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
		Vector2(max(aladdin->getPositionX() - 420, 0),
			max(aladdin->getPositionY() + 500, WINDOWS_HEIGHT));		// 420 va 500 khoảng cách tối đa giữa object và map -> hardcode
																		// Không cho đi quá map.
	if (new_position.x + WINDOWS_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOWS_WIDTH;
	}
	_viewport->setPositionWorld(new_position);
}