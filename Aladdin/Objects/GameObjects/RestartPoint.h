#pragma once
#ifndef _RESTARTPOINT_H
#define _RESTARTPOINT_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../../FrameWork/CollisionBody.h"
#include "../BaseObject.h"

using namespace std;

class RestartPoint : public BaseObject
{
public:
	RestartPoint(int posX, int posY);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	~RestartPoint();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Text* text;
	bool _canTurn;
	
	StopWatch* _firstAnimateStopWatch;
	StopWatch* _normalAnimateStopWatch;
	StopWatch* _beAttackSW;
};
#endif _RESTARTPOINT_H