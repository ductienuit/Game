#ifndef _CGAME_H_
#define _CGAME_H_
#include"GameTime.h"
#include"define.h"
#include"Graphics.h"
#include"../FrameWork/Manager/DeviceManager.h"
#include"InputController.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

class Game
{
public:
	Game(HINSTANCE, LPCSTR = "Aladdin Game", int width = WINDOWS_WIDTH,
		                                     int height = WINDOWS_HEIGHT,
		                                     int fps = FPS,
		                                     int isFullScreen = 0);
	virtual				~Game() {}
	virtual void		InIt();
	virtual void		Release();

	//Đống dưới này chưa code cái nào
	virtual	void		UpdateInput(float deltatime);   //Update input, play object and menu control
	virtual void		Update(float deltatime);        //update your objects
	virtual void		Draw();							//Draw your objects
	virtual void		LoadResource();

	void				Run();	
	void				Render();						//Vẽ ...

	static  void		Exit();	
	static  bool		isExit;
	static  int		    isFullScreen;
	static  Graphics*   getWindow();
protected:	
	pGameTime			_gameTime;            //Quản lí time	
	pDeviceManager		_deviceManager;       //Thiết bị xuất, surface
	pInputController    _input;               //Quản lí các nút bấm
	static Graphics*	_graphics;            //Dùng khởi tạo Window and pointer window hwnd
	LPD3DXSPRITE		_spriteHandler;

private:
	float		        _frameRate;				  // time for 1 frame, milisecond
	float			    _oldTime;
	float				_deltaTime;
};
GAME_FRAMEWORK_END
#endif _CGAME_H_


