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

	/*_listObject.push_back(new Land(600, 300, 10, 200, eDirection::INSIDE, eLandType::CLIMBABLE0));
	_listObject.push_back(new Land(600, 350, 20, 20, eDirection::BOTTOM, eLandType::STOP));
	_listObject.push_back(new Land(130, 460, 550, 30, eDirection::BOTTOM, eLandType::BAR));*/
	_listObject.push_back(new Land(1, 100, 4771, 10, eDirection::TOP, eLandType::SOLID));

	test.top = 100;
	test.left = 10;
	test.bottom = 0;
	test.right = 20;

	background = new BackGround();
	background->InIt();

	auto guardLu = new GuardLu(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	guardLu->InIt();
	_listObject.push_back(guardLu);

	auto guardThin = new GuardThin(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	guardThin->InIt();
	_listObject.push_back(guardThin);

	auto guardShort = new GuardShort(eStatus::MOVING_LEFT, 600, 140, eDirection::LEFT);
	guardShort->InIt();
	_listObject.push_back(guardShort);

    _aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(00,250);
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
	background->Draw(spriteHandle,_viewport);
	for each (auto object in _listObject)
	{
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}
	RECT test1;
	Vector3 p1 = Vector3(test.left, test.top,1);
	p1 = ViewPort::getInstance()->getPositionInViewPort(&p1);
	test1.left = p1.x;
	test1.top = WINDOWS_HEIGHT - p1.y;
	p1 = Vector3(test.right, test.bottom, 1);
	p1 = ViewPort::getInstance()->getPositionInViewPort(&p1);
	test1.right = p1.x;
	test1.bottom = WINDOWS_HEIGHT - p1.y;
	DrawRect(test1);
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