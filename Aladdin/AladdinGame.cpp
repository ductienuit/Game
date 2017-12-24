#include "AladdinGame.h"
USEGAME_FRAMEWORK


AladdinGame::~AladdinGame()
{
}

void AladdinGame::InIt()
{
	Game::InIt();
	SceneManager::getInstance()->AddScene(new  BossScene());
}

void AladdinGame::Release()
{
	Game::Release();
	// release game
	SceneManager::getInstance()->ClearScenes();
}

void AladdinGame::UpdateInput(float deltatime)
{
	SceneManager::getInstance()->UpdateInput(deltatime);
}

void AladdinGame::Update(float deltatime)
{
	SceneManager::getInstance()->Update(deltatime);
}

void AladdinGame::Draw()
{
	this->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	SceneManager::getInstance()->Draw(_spriteHandler);

	this->_spriteHandler->End();
}

void AladdinGame::LoadResource()
{
	// Game::init đã gọi hàm này rồi nên không cần gọi lại ContraGame::loadResource
	// load resource
	SpriteManager::getInstance()->LoadResource(_spriteHandler);
}




