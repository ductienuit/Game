#include"../Aladdin/FrameWork/define.h"
#include"AladdinGame.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game* myGame = new AladdinGame(hInstance, "ALADDIN");
	myGame->InIt();
	myGame->Run();
	myGame->Release();
	delete myGame;

	return 1;
}