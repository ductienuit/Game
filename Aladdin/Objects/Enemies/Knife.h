#ifndef _KNIFE_H
#define _KNIFE_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "BaseEnemy.h"
#include<math.h>
using namespace std;

#define KNIFE_SPEED 300
#define KNIFE_GRAVITY 800
#define KNIFE_JUMP 100

class Knife : public BaseEnemy
{
public:
	Knife(eStatus status, int posX, int posY, eDirection direction);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	IComponent* getComponent(string componentName);

	Text* text;
	void ThrowLeftNear();
	void ThrowRightNear();
	void ThrowLeftFar();
	void ThrowRightFar();
	bool canChangeThrowDirection();
	~Knife();
private:
	
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Vector2 _originPosition;
	Vector2 _currentPosition;
};
#endif
