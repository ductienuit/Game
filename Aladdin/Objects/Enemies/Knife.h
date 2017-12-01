#ifndef _KNIFE_H
#define _KNIFE_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "BaseEnemy.h"
using namespace std;

#define KNIFE_SPEED 100
#define KNIFE_GRAVITY 800
#define KNIFE_JUMP 100

class Knife : public BaseEnemy
{
public:
	Knife(eStatus status, int posX, int posY, eDirection direction);
	void Set(eStatus status, int posX, int posY, eDirection direction);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, Viewport*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	float distanceBetweenAladdin();
	void UpdateStatus(float dt);

	IComponent* getComponent(string componentName);

	Text* text;
	~Knife();
private:
	void movingLeft();
	void movingRight();
	void standing();
	void Throw();
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
};
#endif
