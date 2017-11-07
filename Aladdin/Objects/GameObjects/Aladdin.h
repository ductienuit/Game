#pragma once
#ifndef __ALADDIN_H__
#define	__ALADDIN_H__

#include"../../FrameWork/define.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/InputController.h"
#include"../../FrameWork/Manager/SceneManager.h"
#include"../../FrameWork/StopWatch.h"



#include"BaseObject.h"
//Collision

#include<vector>

[event_receiver(native)]
class Aladdin:public BaseObject,public IControlable
{
public:
	Aladdin();
	~Aladdin();

	//Override function
	void InIt();
	void UpdateInput(float dt);
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void Release();

	//Check event
	void onKeyPressed(KeyEventArg* key_event);
	void onKeyReleased(KeyEventArg* key_event);

	void setStatus(eStatus status) override;



	float getMovingSpeed();

	RECT getBounding() override;

private:
	map<int, Animation*> _animations;
	map<int, IComponent*> _componentList;

	float		_movingSpeed;
	StopWatch*  _stopWatch;
	eStatus		_currentAnimateIndex;
	Vector2	    getVelocity();

	//Action aladdin
	void		Standing();
	void		MoveLeft();
	void		MoveRight();
	void		Jump();
	void		DropDown();
	void		SwingLeft();
	void		SwingRight();

	

	void		updateStatus(float dt);
	void		updateCurrentAnimateIndex();
	eDirection  getAimingDirection();
};
#endif __ALADDIN_H__

