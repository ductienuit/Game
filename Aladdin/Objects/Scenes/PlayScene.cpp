#include "PlayScene.h"
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

void PlayScene::UpdateViewport(BaseObject * aladdin)
{
	// Vị trí hiện tại của viewport. 
	Vector2 current_position = _viewport->getPositionWorld();
	Vector2 worldsize = Vector2(4771, 688);
	// Bám theo object.
	float y = aladdin->getPositionY() - WINDOWS_HEIGHT;
	Vector2 new_position = Vector2(max(aladdin->getPositionX() - 420, 0),
		max(aladdin->getPositionY()+500,WINDOWS_HEIGHT));		// 420 va 500 khoảng cách tối đa giữa object và map -> hardcode
	// Không cho đi quá map.
	if (new_position.x + WINDOWS_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOWS_WIDTH;
	}
	_viewport->setPositionWorld(new_position);
}

bool PlayScene::InIt()
{
	_listobject.push_back(new Land(0, 50, 4771, 50, eDirection::TOP, eLandType::SOLID));
	/*_listobject.push_back(new Land(600, 300, 10, 200, eDirection::INSIDE, eLandType::CLIMBABLE0));
	_listobject.push_back(new Land(600, 350, 20, 20, eDirection::BOTTOM, eLandType::STOP));
	_listobject.push_back(new Land(130, 460, 550, 30, eDirection::BOTTOM, eLandType::BAR));*/


	background = new BackGround();
	background->InIt();

	/*auto guard = new GuardThin(eStatus::MOVING_LEFT,100, 100, eDirection::LEFT);
	guard->InIt();
	_listobject.push_back(guard);*/

	/*auto guardShort = new GuardShort(eStatus::MOVING_LEFT, 400, 80, eDirection::LEFT);
	guardShort->InIt();
	_listobject.push_back(guardShort);*/

    _aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(00,250);
	_listobject.push_back(_aladdin);

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

	for each (auto object in _listobject)
	{
		object->Update(dt);
	}

	for(auto i : _listobject)
		for (auto j : _listobject)
		{
			if (i->getId() != j->getId())
				i->checkCollision(j, dt);
		}
}

void PlayScene::Draw(LPD3DXSPRITE spriteHandle)
{
	background->Draw(spriteHandle,_viewport);

	for each (auto object in _listobject)
	{
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}
}

void PlayScene::Release()
{
	for each (auto object in _listobject)
	{
		object->Release();
	}
}
