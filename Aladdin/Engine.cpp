#include "Engine.h"
#include"define.h"
USEGAME_FRAMEWORK

#pragma region Inintilize all value
HINSTANCE						Engine::_hInstance = NULL;
HWND							Engine::_hwnd = NULL;
LPDIRECT3D9						Engine::_direct = NULL;
LPDIRECT3DDEVICE9				Engine::_directDevice = NULL;
LPDIRECT3DSURFACE9				Engine::_backBuffer = NULL;
LPD3DXSPRITE					Engine::_spriteHandler = NULL;
int								Engine::_windowWidth=WINDOWS_WIDTH;
int								Engine::_windowHeight=WINDOWS_HEIGHT;
LPCSTR							Engine::_gameName = "TEST GAME";
int								Engine::_fPS=FPS;
int								Engine::_currentFrame = 0;

#pragma endregion



Engine::Engine()
{
}


Engine::~Engine()
{
}
