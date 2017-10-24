#pragma once
#ifndef __ALADDIN_H__
#define	__ALADDIN_H__

#include"../../FrameWork/define.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/InputController.h"
#include"../../FrameWork/Manager/SceneManager.h"
//stopwatch

#include"BaseObject.h"
#include"IComponent.h"
//Collision

#include<vector>

[event_receiver(native)]
class Aladdin:public BaseObject
{
public:
	Aladdin();
	~Aladdin();
};
#endif __ALADDIN_H__

