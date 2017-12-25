#include "EndScene.h"


ViewPort* EndScene::_viewport = ViewPort::getInstance();
EndScene::EndScene()
{
	InIt();
}

EndScene::~EndScene()
{
}

bool EndScene::InIt()
{
	_endSceneBackground = new EndSceneBackground();

	_aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(800, 100);
	_aladdin->setStatus(eStatus::ENDSCENE);

	_monkey = new Monkey(eStatus::ENDSCENE, 700, 70, eDirection::LEFT);

	return true;
}

void EndScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void EndScene::Update(float dt)
{
	_aladdin->Update(dt);
	_monkey->Update(dt);
}

void EndScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_endSceneBackground->Draw(spriteHandle, _viewport);
	_aladdin->Draw(spriteHandle, _viewport);
	_monkey->Draw(spriteHandle, _viewport);
}

void EndScene::Release()
{
	_endSceneBackground->Release();
	_aladdin->Release();
	_monkey->Release();
}
