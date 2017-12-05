#include "PlayScene.h"
#include<iostream>
using namespace std;

Viewport* PlayScene::_viewport = new Viewport(1, WINDOWS_HEIGHT);

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
	_listobject.push_back(new Land(100, 100, 1000, 50, eDirection::TOP, eLandType::SOLID));
	_listobject.push_back(new Land(600, 300, 10, 200, eDirection::INSIDE, eLandType::CLIMBABLE0));
	_listobject.push_back(new Land(600, 350, 20, 20, eDirection::BOTTOM, eLandType::STOP));
	_listobject.push_back(new Land(130, 460, 550, 30, eDirection::BOTTOM, eLandType::BAR));

	camera = new Camera(800, 600, 0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));


	background = new BackGround();
	background->InIt();


	/*auto guard = new GuardThin(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	guard->InIt();
	_listobject.push_back(guard);*/

	/*auto guardShort = new GuardShort(eStatus::MOVING_LEFT, 600, 140, eDirection::LEFT);
	guardShort->InIt();
	_listobject.push_back(guardShort);*/

	auto knifeThrower = new KnifeThrower(eStatus::MOVING_LEFT, 300, 100, eDirection::LEFT);
	knifeThrower->InIt();
	_listobject.push_back(knifeThrower);

    _aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(100,300);
	_listobject.push_back(_aladdin);

	return true;
}

void PlayScene::UpdateInput(float dt)
{
	if (camera)
	{
		if (GetAsyncKeyState(70)) //70 is the vKey value for F
		{
			if (!camera->IsFollowing())
			{
				camera->Follow(_aladdin);
			}
		}

		if (GetAsyncKeyState(85)) //85 is the vKey value for U
		{
			if (camera->IsFollowing())
			{
				camera->Unfollow();
			}
		}

		camera->Update();
	}

	_aladdin->UpdateInput(dt);
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
	LPDIRECT3DDEVICE9 device = DeviceManager::getInstance()->getDevice();
	device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 100, 100), 1.0f, 0);
	device->BeginScene();

	if (camera)
	{
		camera->SetTransform();
	}

	background->Draw(spriteHandle,_viewport);
	for each (auto object in _listobject)
	{
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

void PlayScene::Release()
{
	for each (auto object in _listobject)
	{
		object->Release();
	}
}
