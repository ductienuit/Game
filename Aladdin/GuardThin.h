#ifndef _RUNNINGSOLDIER_H
#define _RUNNINGSOLDIER_H

#include"BaseEnemy.h"
#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../Aladdin/FrameWork/IComponent.h"

using namespace std;

#define GUARDTHIN_SPEED 120
#define GUARDTHIN_SCORE 100

class GuardThin : public BaseEnemy
{
public:
	GuardThin(eStatus status, int posX,int posY, eDirection direction);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, Viewport*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);


	IComponent* getComponent(string componentName);
	~GuardThin();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
};
#endif
