

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <Windows.h>
#include "define.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

class Graphics
{
public:
	Graphics(HINSTANCE hInstance, LPCSTR name, int width, int height, int fps, int isFullScreen);
	~Graphics();

	bool		InItWindow();

	int			getIsFullScreen();
	int			getWindowWidth();
	int			getWindowHeight();
	int			getFrameRate();
	HWND		getHwnd();
	HINSTANCE   gethInstance();
protected:

	HINSTANCE		_hInstance;
	HWND			_hWnd;

	LPCSTR			_gameName;
	int				_isFullScreen;

	int				_windowWidth;
	int				_windowHeight;
	int				_fps;

	static LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	Graphics();
};

//Pointer to a Windows object
typedef Graphics* pGraphics;

GAME_FRAMEWORK_END

#endif // !__GRAPHICS_H__
