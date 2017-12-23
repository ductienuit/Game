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
	return true;
}

void EndScene::UpdateInput(float dt)
{
}

void EndScene::Update(float dt)
{
}

void EndScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_endSceneBackground->Draw(spriteHandle, _viewport);
}

void EndScene::Release()
{
	_endSceneBackground->Release();
}
