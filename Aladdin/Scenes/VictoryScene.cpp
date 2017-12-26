#include "VictoryScene.h"
#include"IntroScene.h"

ViewPort* VictoryScene::_viewport = ViewPort::getInstance();
VictoryScene::VictoryScene()
{
	ViewPort::getInstance()->setPositionWorld(Vector2(0, 480));
	//âm thanh
	SoundManager::getInstance()->StopAllSound();
}

VictoryScene::~VictoryScene()
{
}

bool VictoryScene::InIt()
{
	_endSceneBackground = new BackgroundEndScene();

	_aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(800, 100);
	_aladdin->setStatus(eStatus::ENDSCENE);

	_monkey = new Monkey(eStatus::ENDSCENE, 700, 70, eDirection::LEFT);
	//âm thanh
	SoundManager::getInstance()->PlaySound("Resources/Audio/LevelComplete.mp3", 1); 

	return true;
}

void VictoryScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void VictoryScene::Update(float dt)
{
	_aladdin->Update(dt);
	_monkey->Update(dt);
	if (_aladdin->getPositionX() < 0)
	{
		auto scene = new IntroScene();
		SceneManager::getInstance()->ReplaceScene(scene);
	}
}

void VictoryScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_endSceneBackground->Draw(spriteHandle, _viewport);
	_aladdin->Draw(spriteHandle, _viewport);
	_monkey->Draw(spriteHandle, _viewport);
}

void VictoryScene::Release()
{
	_endSceneBackground->Release();
	delete _endSceneBackground;

	_aladdin->Release();
	delete _aladdin;

	_monkey->Release();
	delete _monkey;

	auto _input = InputController::getInstance();
	if (_input != nullptr)
		__unhook(_input);
	SoundManager::getInstance()->StopAllSound();
}
