#ifndef __GAME_FRAMEWORK__
#define __GAME_FRAMEWORK__
#define WINDOWS_WIDTH 1000
#define WINDOWS_HEIGHT 600
#define FPS 30
#define MAX_KEYS 256

#include <d3d9.h>		// d3d9.lib
#include <d3dx9.h>		// d3dx9.lib
#include <dinput.h>		// dinput8.lib, dxguid.lib
#include <dsound.h>		// dsound.lib

#include <Windows.h>
#include <exception>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include"debug.h"
#include<corecrt_math_defines.h>


enum eStatus
{
	NORMAL = 0,					// 00000 = 0	
	MOVING_LEFT = (1 << 0),				// 000001 = 2^0
	MOVING_RIGHT = (1 << 1),				// 00010 = 2^1
	JUMPING = (1 << 2),				// 00100 = 2^2
	SITTING_DOWN = (1 << 3),				// 01000 = 2^3
	RUNNING = (1 << 4),				// 10000 = 2^4
	LOOKING_UP = (1 << 5),				// 2^5
	SHOOTING = (1 << 6),
	FREE = (1 << 7),			//Trạng thái sau trạng thái normal khi chờ player rờ phím
	JUMPING_LEFT = (1 << 8),
	JUMPING_RIGHT = (1 << 9),
	CLIMB = (1<<10),	//leo lên trên
	SWING= (1<<11),		//leo xà ngang
	DROP = (1<<12),
	DYING=(1<<13)
};

enum eID
{
	ALADDIN
};

enum eDirection
{
	NONE = 0,
	TOP = 1,
	BOTTOM = 2,
	LEFT = 4,
	RIGHT = 8,
	ALL = (TOP | BOTTOM | LEFT | RIGHT),
};

#define C_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)				// màu trắnng
#define COLOR_KEY D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)				// màu khi mà load hình nó bỏ qua > trong suốt

//enum StateGame
//{	
//	Alive,
//	Pause,
//	Resume
//};

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
#define VECTOR2ZERO Vector2(0.0f, 0.0f)

#define GAME_FRAMEWORK		    namespace FrameWork

#define GAME_FRAMEWORK_BEGIN	{

#define GAME_FRAMEWORK_END	    }

#define USEGAME_FRAMEWORK		using namespace FrameWork;

#ifndef SAFE_DELETE

#define SAFE_DELETE(p) \
if(p) \
{\
	delete (p); \
	p = nullptr; \
} \

#endif SAFE_DELETE

#endif __GAME_FRAMEWORK__


