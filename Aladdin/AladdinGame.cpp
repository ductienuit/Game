#include "AladdinGame.h"
USEGAME_FRAMEWORK


AladdinGame::AladdinGame(HINSTANCE hInstance, LPCSTR Name) :Game(hInstance, Name)
{
}

AladdinGame::~AladdinGame()
{
}

void AladdinGame::InIt()
{
	Game::Init();
}

void AladdinGame::Run()
{
	Game::Run();
}


