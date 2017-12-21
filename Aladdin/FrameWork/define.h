#ifndef __GAME_FRAMEWORK__
#define __GAME_FRAMEWORK__
#define WINDOWS_WIDTH 640
#define WINDOWS_HEIGHT 480
#define SIZEMAP	D3DXVECTOR2(7634,1321) //4771*1,6 ; 688*1.92 
#define FPS 60
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
#include "utils.h"

enum eStatus
{
	NORMAL =		0,					// 00000 = 0
	NORMAL1 =		(1 << 0),
	MOVING_LEFT =	(1 << 1),				// 000001 = 2^0
	MOVING_RIGHT =	(1 << 2),				// 00010 = 2^1
	JUMPING =		(1 << 3),				// 00100 = 2^2
	SITTING_DOWN =	(1 << 4),				// 01000 = 2^3
	STOPWALK =		(1 << 5),			//Aladdin sẽ là dừng
	LOOKING_UP =	(1 << 6),				// 2^5
	DESTROY =		(1 << 7),			//Ném táo.
	FREE =			(1 << 8),			//Trạng thái sau trạng thái normal khi chờ player rờ phím
	JUMPING_LEFT =  (1 << 9),			//Đang moveLeft nhấn C
	JUMPING_RIGHT = (1 << 10),			//Đang moveRight nhấn C
	CLIMB =			(1 << 11),			//Leo lên trên
	SWING =			(1 << 12),			//Leo xà ngang
	DROP =			(1 << 13),			//Đứng trên nhảy xuống
	DYING =			(1 << 14),			//Chết
	ATTACK =	    (1 << 15),			//Cầm kiếm chém
    BEHIT   =		(1 << 16),			//Trạng thái không anime. Kết hợp với các trạng thái với các trạng thái khác để tạo 1 trạng thái.
	CLIMB_JUMP =    (1 << 17),
	THROW_LEFT_NEAR  =	(1 << 18),		//Trang thai cua knife
	THROW_RIGHT_NEAR =	(1 << 19),		//Trang thai cua knife
	THROW_LEFT_FAR   =	(1 << 20),		//Trang thai cua knife
	THROW_RIGHT_FAR  =	(1 << 21),		//Trang thai cua knife
	THROW			 =  (1 << 22),
	THROW_LEFT	   	 =	(1 << 23),
	THROW_RIGHT		 =	(1 << 24),
	REVIVAL			 =  (1 << 25),      //Hồi Sinh
	AEROBATIC		 =  (1 << 26)
};

enum eID
{
	LAND,
	ALADDIN,
	GUARDTHIN,
	GUARDSHORT,
	KNIFETHROWER,
	GUARDLU,
	KNIFE,
	BACKGROUND,
	BACKGROUNDFRONT,
	JAR,
	GUARDTHROWJAR,
	APPLETHROW,
	GUARDFAT,
	FIRE,
	FALLINGPLATFORM,
	
	CAMEL,
	BULLETCAMEL,

	APPLEEAT,
	HEARTEAT,
	ITEMSPARK,

	COINEAT,

	RESTARTPOINT,


	SPRING
};

enum eDirection
{
	NONE =		(1<0),
	TOP =		(1<<27),
	BOTTOM =	(1<<28),
	LEFT =		(1<<29),
	RIGHT =		(1<<30),
	INSIDE = (TOP | BOTTOM | LEFT | RIGHT),
};

enum eLandType
{
	ROPE,	//Dây
	SOLID,	//Nền đất
	PLATFORM, //Tấm gỗ
	BAR,  //Thanh xà ngang
	CLIMBABLE0,//Dây 1
	CLIMBABLE1,//Dây 2
	CLIMBABLE2,//Dây 3
	STOP,
	STAIR, //Bậc thang,
	WALL,
	CHECKSTAIR1,  //Cờ đặt cầu thang lên xuống
	CHECKSTAIR2,
	CHECKSTAIR3,
	CHECKSTAIR4,
};
#define C_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)				// màu trắnng
#define COLOR_KEY D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)				// màu khi mà load hình nó bỏ qua > trong suốt
#define SCALEFACTOR D3DXVECTOR2(1.6f,1.92f)
#define SCALEAPPLE D3DXVECTOR2(2.0f,2.0f)
#define SCALEHEART D3DXVECTOR2(2.0f,2.0f)
#define SCALECHARACTER D3DXVECTOR2(1.6f,1.92f)
#define SCALEALADDIN D3DXVECTOR2(1.8f,2.16f)
#define SCALEMAP D3DXVECTOR2(1.6f,1.92f)
#define SCALEONE D3DXVECTOR2(1.0f,1.0f)
#define ORIGINCHARACTER D3DXVECTOR2(0.5f, 0.0f)
#define ORIGINZERO D3DXVECTOR2(0.0f, 0.0f)





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

//
// corecrt_math_defines.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Definitions of useful mathematical constants
//
#pragma once

#ifndef _MATH_DEFINES_DEFINED
#define _MATH_DEFINES_DEFINED
// Definitions of useful mathematical constants
//
// Define _USE_MATH_DEFINES before including <math.h> to expose these macro
// definitions for common math constants.  These are placed under an #ifdef
// since these commonly-defined names are not part of the C or C++ standards
#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)
#endif

#endif __GAME_FRAMEWORK__


