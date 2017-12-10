#ifndef _GUARDFAT_H
#define _GUARDFAT_H

#include "BaseEnemy.h"
#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../GameObjects/Objects/Aladdin.h"

using namespace std;

#define GUARDFAT_SPEED 50
#define GUARDFAT_SCORE 100

class GuardFat : public BaseEnemy
{
public:
	GuardFat(eStatus status, int posX, int posY, eDirection direction);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	float distanceBetweenAladdin();
	void UpdateStatus(float dt);

	IComponent* getComponent(string componentName);
	Text* text;
	~GuardFat();
private:
	void movingLeft();
	void movingRight();
	void standing();
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
};
#endif _GUARDFAT_H
