#ifndef _CGAME_H_
#define _CGAME_H_
#include<Windows.h>
#include"Engine.h"
#include"GameTime.h"
#include"define.h"
#include"Graphics.h"
#include"DeviceManager.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

class Game
{
public:
	Game(HINSTANCE, LPCSTR = "Aladdin Game", int width = WINDOWS_WIDTH,
		                                     int height = WINDOWS_HEIGHT,
		                                     int fps = FPS,
		                                     int isFullScreen = 0);
	virtual			~Game() {}
	virtual void	Release();
	virtual void	Run();
	virtual void	Exit();	
	static  bool	isExit;
	static  int     isFullScreen;	
protected:
	virtual void    InIt();
	//virtual bool	InitWindows();
	//virtual bool    InitDevice();
	virtual bool	LoadResource();
	pGameTime       gameTime;
	pGraphics       graphics;
	pDeviceManager  deviceManager;
	LPD3DXSPRITE    spriteHandle;
private:
	float			frameRate;			// time for 1 frame, milisecond
	float			oldTime;
	float			deltaTime;
};
GAME_FRAMEWORK_END
#endif _CGAME_H_


