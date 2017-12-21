#ifndef _HEALTH_H
#define _HEALTH_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../../FrameWork/CollisionBody.h"
#include "../BaseObject.h"
#include"../Score/ScoreAladdin.h"

class Health :public BaseObject
{
public:
	Health(int posX=100, int posY=100);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	~Health();
private:
	map<int, Animation*> _animations;
	int strStatus;
};
#endif _HEALTH_H