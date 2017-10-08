#ifndef __GAME_FRAMEWORK__
#define __GAME_FRAMEWORK__
#define WINDOWS_WIDTH 1000
#define WINDOWS_HEIGHT 600
#define FPS 30


#include <d3d9.h>		// d3d9.lib
#include <d3dx9.h>		// d3dx9.lib
#include <dinput.h>		// dinput8.lib, dxguid.lib
#include <dsound.h>		// dsound.lib

#include <windows.h>
#include <exception>
#include <math.h>
#include <string>
#include <map>
#include <vector>


//enum StateGame
//{	
//	Alive,
//	Pause,
//	Resume
//};
#define GAME_FRAMEWORK		    namespace FrameWork

#define GAME_FRAMEWORK_BEGIN	{

#define GAME_FRAMEWORK_END	    }

#define USEGAME_FRAMEWORK		using namespace FrameWork;

#endif


