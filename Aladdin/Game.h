#ifndef _CGAME_H_
#define _CGAME_H_
#include<Windows.h>
#include"Engine.h"
#include"GameTime.h"
#include"define.h"

class Game
{
public:
	Game(HINSTANCE, LPCSTR = "Window Game", int width = WINDOWS_WIDTH, int height = WINDOWS_HEIGHT, int fps = FPS, int isFullScreen = 0);
	virtual      ~Game() {}
	virtual void Release();
	virtual void Run();
	virtual void Exit();	
	static  bool isExit;
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	virtual void                    Init();
	virtual bool					InitWindows();
	virtual bool                    InitDevice();
	virtual bool					LoadResource();
	pGameTime                       gameTime;
private:
	float frameRate;			// time for 1 frame, milisecond
	float oldTime;
	float deltaTime;
};

#endif _CGAME_H_


