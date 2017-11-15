#ifndef __ALADDIN_H__
#define __ALADDIN_H__

#include "../../FrameWork/define.h"
#include "../../FrameWork/Animation.h"
#include "../../FrameWork/InputController.h"
#include"../../FrameWork/IComponent.h"
#include"../../FrameWork/StopWatch.h"
#include "BaseObject.h"
#include"../../FrameWork/CollisionBody.h"
#include<iostream>

using namespace std;

#define ALADDIN_MOVE_SPEED 125
#define ALADDIN_JUMP_VEL 450
#define ALADDIN_ACC_MOVE 300
#define TEST_ROPE 100
#define GRAVITY 800
#define ALADDIN_CLIMB_SPEED 90


[event_receiver(native)]
class Aladdin : public BaseObject, public IControlable
{
public:
	Aladdin();
	~Aladdin();

	void InIt();
	void UpdateInput(float dt);
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void Release();

	void onCollisionBegin(CollisionEventArg* collision_event);
	void onCollisionEnd(CollisionEventArg* collision_event);

	float checkCollision(BaseObject* object, float dt);

	void setPosition(float x, float y);

private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _componentList;

	void onKeyReleased(KeyEventArg* key_event);

	void standing();
	void moveLeft();
	void moveRight();
	void jump(eStatus status);
	void sitDown();
	void swingSword();
	void sitAttack();
	void climbUp(float dt);
	void climbDown(float dt);
	void climbJump();


	//Dong ho dem
	StopWatch* _firstAnimateStopWatch;
	StopWatch* _normalAnimateStopWatch;

	//void setState(int state);
	void addStatus(eStatus status);
	void removeStatus(eStatus status);
	bool isInStatus(eStatus status);

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
