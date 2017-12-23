#include "IntroScene.h"
ViewPort* IntroScene::_viewport = ViewPort::getInstance();
IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{

}

void IntroScene::setViewPort(ViewPort * viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

bool IntroScene::InIt()
{
	_menuBackground = new MenuBackground();
	_menuBackground->InIt();

	_choose	= (new Choose(120,190));

	return true;
}

void IntroScene::UpdateInput(float dt)
{
	_choose->UpdateInput(dt);
}

void IntroScene::Update(float dt)
{
	_choose->Update(dt);
}

void IntroScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_menuBackground->Draw(spriteHandle, _viewport);
	_choose->Draw(spriteHandle, _viewport);
}

void IntroScene::Release()
{
	_menuBackground->Release();
	_choose->Release();
}