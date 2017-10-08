#include <windows.h>
#include <d3d9.h>
#include<d3dx9.h>
#include"AladdinGame.h"
#include"Engine.h"

using namespace std;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AladdinGame* myGame = new AladdinGame(hInstance, "ALADDIN");
	myGame->InIt();
	myGame->Run();
	myGame->Release();
	delete myGame;
	system("pause");
	return 1;
}
//Test