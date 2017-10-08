#pragma once
#ifndef __ENGINE_H__
#define __ENGINE_H__

#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include"define.h"

using namespace std;

#define NUMBEROFSPRITE 10

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

class Engine
{
public:	
	static HINSTANCE GethInstance() { return _hInstance; }
	static void SethInstance(HINSTANCE hInstance) { _hInstance = hInstance; }

	static HWND GetHwnd() { return Engine::_hwnd; }
	static void SetHwnd(HWND hwnd) { Engine::_hwnd = hwnd; }

	static LPDIRECT3D9 GetDirect() { return Engine::_direct; }
	static void SetDirect(LPDIRECT3D9 direct) { Engine::_direct = direct; }

	static LPDIRECT3DDEVICE9 GetDirectDevice() { return Engine::_directDevice; }
	static void SetDirectDevice(LPDIRECT3DDEVICE9 directDevice) { Engine::_directDevice = directDevice; }

	static LPDIRECT3DSURFACE9 GetBackBuffer() { return Engine::_backBuffer; }
	static void SetBackBuffer(LPDIRECT3DSURFACE9 backBuffer) { Engine::_backBuffer = backBuffer; }

	static LPD3DXSPRITE GetSpriteHandler() { return Engine::_spriteHandler; }
	static void SetSpriteHandler(LPD3DXSPRITE spriteHandler) { Engine::_spriteHandler = spriteHandler; }

	static int GetWindowHeight() { return Engine::_windowHeight; }
	static void SetWindowHeight(int height) { Engine::_windowHeight = height; }

	static int GetWindowWidth() { return Engine::_windowWidth; }
	static void SetWindowWidth(int width) { Engine::_windowWidth = width; }

	static LPCSTR GetGameName() { return Engine::_gameName; }
	static void SetGameName(LPCSTR nameOfGame) { Engine::_gameName = nameOfGame; }

	static int GetFrameRate() { return Engine::_fPS; }
	static void SetFrameRate(int Fps) { Engine::_fPS = Fps; }

	static int GetCurrentFrame() { return Engine::_currentFrame; }
	static void SetCurrentFrame(int currentFrame) { Engine::_currentFrame = (_currentFrame >= NUMBEROFSPRITE) ? 1 : ++_currentFrame; }

	Engine();
	~Engine();
private:	
	static  HINSTANCE						_hInstance;
	static	HWND							_hwnd; //Biến toàn cục chứa con trỏ quản lý cửa số
	static	LPDIRECT3D9						_direct;//Đối tượng direct
	static	LPDIRECT3DDEVICE9			    _directDevice; //Thiết bị hiển thị direct
	static	LPDIRECT3DSURFACE9				_backBuffer;//Vẽ trước đây rồi xuất screen
	static	LPD3DXSPRITE					_spriteHandler;
	static	int								_windowWidth;
	static	int								_windowHeight;
	static	LPCSTR					    	_gameName;
	static	int								_fPS; //frame per second
	static	int								_currentFrame;

};
GAME_FRAMEWORK_END
#endif _ENGINE_H_


