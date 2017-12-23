#include "IntroScene.h"

using namespace std;

ViewPort* IntroScene::_viewport = ViewPort::getInstance();
IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
	delete _viewport;
	_viewport = nullptr;
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

void IntroScene::UpdateViewport(BaseObject * aladdin)
{
	// Vị trí hiện tại của viewport. 
	Vector2 current_position = _viewport->getPositionWorld();
	//Kích thước của map
	Vector2 worldsize = Vector2(SIZEMAP.x, SIZEMAP.y);
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