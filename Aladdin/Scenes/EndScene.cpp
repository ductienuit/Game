#include "EndScene.h"
#include"IntroScene.h"

ViewPort* EndScene::_viewport = ViewPort::getInstance();
EndScene::EndScene()
{
	ViewPort::getInstance()->setPositionWorld(Vector2(0, 480));
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
	if (_aladdin->getPositionX() < 0)
	{
		auto scene = new IntroScene();
		SceneManager::getInstance()->ReplaceScene(scene);
	}
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
