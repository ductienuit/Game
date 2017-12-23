﻿#ifndef __ALADDIN_H__
#define __ALADDIN_H__

#include "../../FrameWork/define.h"
#include"../../FrameWork/Manager/SoundManager.h"
#include"../../FrameWork/Animation.h"
#include "../../FrameWork/InputController.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/StopWatch.h"
#include "../BaseObject.h"
#include "../../FrameWork/CollisionBody.h"
#include "AppleThrow.h"
#include"RestartPoint.h"

#include"Land.h"
#include"FallingPlatform.h"
#include<iostream>

using namespace std;

#define ALADDIN_MOVE_SPEED 270
#define ALADDIN_MOVE_JUMP_SPEED 200
#define ALADDIN_JUMP_VEL 500
#define ALADDIN_AEROBATIC_VEL 600
#define ALADDIN_JUMP_DOUBLE_VEL 400
#define ALADDIN_CLIMB_JUMP_VEL 300
#define ALADDIN_ACC_MOVE 300
#define GRAVITY 800
#define ALADDIN_CLIMB_SPEED 110 


[event_receiver(native)]
class Aladdin : public BaseObject, public IControlable
{
public:
	Aladdin();
	~Aladdin();

	void InIt();
	void UpdateInput(float dt);
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE spriteHandle, ViewPort* viewport);
	void Release();

	void	onCollisionBegin(CollisionEventArg* collision_event);
	void	onCollisionEnd(CollisionEventArg* collision_event);

	float	checkCollision(BaseObject* object, float dt);

	RECT	getBounding() override;
	void	setBounding(RECT);

			//get index Animation Attack
	int		getIndex() override;

	void	Stop() override;
	void	Stop(bool);


	// Hồi Sinh
	void SetRestartPoint(BaseObject*) override;
	void Revival();

private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _listComponent;
	RECT _boundAla;
	BaseObject* landstop;
	BaseObject* _preObjectColli;  //Đối tượng va chạm trước đó
	BaseObject* _restartPoint;

	void onKeyReleased(KeyEventArg* key_event);

	void standing();
	void moveLeft();
	void moveRight();
	void jump(eStatus status);
	void jumpDouble();
	void sitDown();
	void swingSword();

	void aerobatic();

	void moveLeftJump();
	void moveRightJump();

	void climb();
	void climbUp(float dt);
	void climbDown(float dt);
	void climbJump();
	void climbLeft();
	void climbRight();

	void swing();
	void swingLeft(float dt);
	void swingRight(float dt);
	void swingJump();
	bool _stopLeft;

	//Dong ho dem
	StopWatch* _firstAnimateStopWatch;
	StopWatch* _normalAnimateStopWatch;
	StopWatch* _beAttackSW;

	//void setState(int state);
	void addStatus(eStatus status);
	void removeStatus(eStatus status);
	bool isInStatus(eStatus status);
	bool isExist(eStatus status);


	Vector2 getVelocity();
	void updateStatus(float dt);
	//Kiểm tra loại trạng thái và cho thực hiện đến những ảnh cuối cùng
	void updateStatusOneAction(float deltatime); 

	eStatus _currentAnimateIndex;
	eDirection _currentDirection;
	void updateCurrentAnimateIndex();

	void unHookInputEvent();
};


#endif // !__ALADDIN_H__
