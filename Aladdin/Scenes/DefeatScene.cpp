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
	_aladdin->setPosition(300, 200);
	_aladdin->setStatus(eStatus::DYING);


	_monkey = new Monkey(eStatus::FREE, 450, 150, eDirection::NONE);
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
	_monkey->Update(dt);
	if (_aladdin->getIndexImageStatus(DYING) >=27)
	{
		auto scene = new IntroScene();
		SceneManager::getInstance()->ReplaceScene(scene);
	}
}

void DefeatScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_aladdin->Draw(spriteHandle, _viewport);
	_monkey->Draw(spriteHandle, _viewport);
}

void DefeatScene::Release()
{

	_aladdin->Release();
	_monkey->Release();
	delete _aladdin;
	delete _monkey;

	auto _input = InputController::getInstance();
	if (_input != nullptr)
		__unhook(_input);
	SoundManager::getInstance()->StopAllSound();
}
