#include "PlayScene.h"
#include<iostream>
using namespace std;

Viewport* PlayScene::_viewport = new Viewport(0, WINDOWS_HEIGHT);

PlayScene::PlayScene()
{
	//_viewport = new Viewport(0,600);
}

PlayScene::~PlayScene()
{
	delete _viewport;
	_viewport = nullptr;
}
void PlayScene::setViewport(Viewport * viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

Viewport * PlayScene::getViewport()
{
	return _viewport;
}

bool PlayScene::InIt()
{
	_listobject.push_back(new Land(200, 350, 10, 200, eDirection::NONE, eLandType::CLIMBABLE0));
	_listobject.push_back(new Land(100, 100, 1000, 50, eDirection::NONE,eLandType::SOLID));

	

	/*auto guard = new GuardThin(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	guard->InIt();
	_listobject.push_back(guard);*/

	auto aladdin = new Aladdin();
	aladdin->InIt();
	aladdin->setPosition(100,300);
	_listControlObject.push_back(aladdin);
	_listobject.push_back(aladdin);
	return true;
}

void PlayScene::UpdateInput(float dt)
{
	for each (IControlable* obj in _listControlObject)
	{
		obj->UpdateInput(dt);
	}
}

void PlayScene::Update(float dt)
{

	/*char str[100];
	sprintf(str, "delta time: %f", dt);
	_text->setText(str);*/

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
