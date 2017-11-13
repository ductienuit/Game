﻿#ifndef __GAME_FRAMEWORK__
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
#include"../testSweepAABB.h"


enum eStatus
{
	NORMAL =		0,					// 00000 = 0
	NORMAL1 =		(1 << 0),
	MOVING_LEFT =	(1 << 1),				// 000001 = 2^0
	MOVING_RIGHT =	(1 << 2),				// 00010 = 2^1
	JUMPING =		(1 << 3),				// 00100 = 2^2
	SITTING_DOWN =	(1 << 4),				// 01000 = 2^3
	RUNNING =		(1 << 5),				// 10000 = 2^4
	LOOKING_UP =	(1 << 6),				// 2^5
	THROW =			(1 << 7),			//Ném táo.
	FREE =			(1 << 8),			//Trạng thái sau trạng thái normal khi chờ player rờ phím
	JUMPING_LEFT =  (1 << 9),			//Đang moveLeft nhấn C
	JUMPING_RIGHT = (1 << 10),			//Đang moveRight nhấn C
	CLIMB =			(1 << 11),			//Leo lên trên
	SWING =			(1 << 12),			//Leo xà ngang
	DROP =			(1 << 13),			//Đứng trên nhảy xuống
	DYING =			(1 << 14),			//Chết
	ATTACK =	    (1 << 15),			//Cầm kiếm chém
	WORKING=		(1 << 16),			//Trạng thái không anime. Kết hợp với các trạng thái với các trạng thái khác để tạo 1 trạng thái.
};

enum eID
{
	ALADDIN,
	ROPE
};

enum eDirection
{
	NONE =		(1<<26),
	TOP =		(1<<27),
	BOTTOM =	(1<<28),
	LEFT =		(1<<29),
	RIGHT =		(1<<30),
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


