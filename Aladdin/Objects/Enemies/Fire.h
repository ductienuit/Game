#ifndef _FIRE_H
#define _FIRE_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../Score/ScoreAladdin.h"
#include "BaseEnemy.h"
#include<math.h>
using namespace std;

class Fire : public BaseEnemy
{
public:
	Fire(eStatus, int , int, eDirection direction);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	IComponent* getComponent(string componentName);

	RECT getBounding() override;
	Text* text;
	~Fire();
private:

	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
};
#endif
