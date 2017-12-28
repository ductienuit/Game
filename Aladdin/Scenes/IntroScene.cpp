#include "IntroScene.h"
ViewPort* IntroScene::_viewport = ViewPort::getInstance();
IntroScene::IntroScene()
{
	//âm thanh
	SoundManager::getInstance()->StopAllSound();
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
	_menuBackground = new BackgroundMenu();
	_menuBackground->InIt();

	_choose	= (new Choose(120,190));
	
	_strScene1 = new Alphabet(250, 200);
	_strScene1->setString("AGRABAH MARKET",false);
	_strSceneBoss = new Alphabet(250, 160);
	_strSceneBoss->setString("JAFAR",false);
	//âm thanh
	SoundManager::getInstance()->PlaySound("Resources/Audio/AWholeNewWorld.mp3", 1);
	return true;
}

void IntroScene::UpdateInput(float dt)
{
	_choose->UpdateInput(dt);
}

void IntroScene::Update(float dt)
{
	_choose->Update(dt);
	_strScene1->Update(dt);
	_strSceneBoss->Update(dt);
}

void IntroScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_menuBackground->Draw(spriteHandle, _viewport);
	_choose->Draw(spriteHandle, _viewport);
	_strScene1->Draw(spriteHandle, _viewport);
	_strSceneBoss->Draw(spriteHandle, _viewport);
}

void IntroScene::Release()
{
	_menuBackground->Release();
	_choose->Release();
}