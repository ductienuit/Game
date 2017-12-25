#ifndef _GUARDTHIN_H
#define _GUARDTHIN_H

#include "BaseEnemy.h"
#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../Enemies/BaseEnemy.h"
#include"../GameObjects/Aladdin.h"

using namespace std;

#define GUARDTHIN_SPEED 50
#define GUARDTHIN_SCORE 100

class GuardThin : public BaseEnemy
{
public:
	GuardThin(eStatus status, int posX, int posY,BaseObject* aladdin, int minMove, int maxMove);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	Vector2 distanceBetweenAladdin();
	void UpdateStatus(float dt);

	IComponent* getComponent(string componentName);
	Text* text;
	~GuardThin();
private:
	BaseObject * _aladdin;
	void movingLeft();
	void movingRight();
	void standing();
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
};
#endif _GUARDTHIN_H

