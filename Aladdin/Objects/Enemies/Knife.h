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

	float distanceBetweenAladdin();

	IComponent* getComponent(string componentName);

	Text* text;
	void ThrowLeftNear();
	void ThrowRightNear();
	void ThrowLeftFar();
	void ThrowRightFar();
	bool canChangeThrowDirection();
	void movingLeft(float x, float y);
	void movingRight(float x, float y);
	~Knife();
private:
	void movingLeft();
	void movingRight();
	void standing();
	
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	Vector2 _originPosition;
	Vector2 _currentPosition;
};
#endif
