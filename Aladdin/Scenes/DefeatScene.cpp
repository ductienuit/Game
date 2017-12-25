#include "DefeatScene.h"
#include"IntroScene.h"

ViewPort* DefeatScene::_viewport = ViewPort::getInstance();
DefeatScene::DefeatScene()
{
	ViewPort::getInstance()->setPositionWorld(Vector2(0, 480));
	//âm thanh
	SoundManager::getInstance()->StopAllSound();
}

DefeatScene::~DefeatScene()
{
}

bool DefeatScene::InIt()
{
	_aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(800, 100);
	_aladdin->setStatus(eStatus::ENDSCENE);


	_monkey = new Monkey(eStatus::ENDSCENE, 700, 70, eDirection::LEFT);
	//âm thanh
	SoundManager::getInstance()->PlaySound("Resources/Audio/LevelComplete.mp3", 1);

	return true;
}

void DefeatScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void DefeatScene::Update(float dt)
{
	_aladdin->Update(dt);
	if (_aladdin->getPositionX() < 0)
	{
		auto scene = new IntroScene();
		SceneManager::getInstance()->ReplaceScene(scene);
	}
}

void DefeatScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_aladdin->Draw(spriteHandle, _viewport);
}

void DefeatScene::Release()
{

	_aladdin->Release();
	delete _aladdin;
	
	auto _input = InputController::getInstance();
	if (_input != nullptr)
		__unhook(_input);
	SoundManager::getInstance()->StopAllSound();
}
