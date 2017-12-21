#ifndef _KNIFE_SHORT_H
#define _KNIFE_SHORT_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../Score/InforAladdin.h"
#include "BaseEnemy.h"
using namespace std;

#define KNIFE_SHORT_SPEED 500
#define KNIFE_SHORT_GRAVITY 800
#define KNIFE_SHORT_JUMP 100

class KnifeShort : public BaseEnemy
{
public:
	KnifeShort(eStatus status, int posX, int posY, eDirection direction);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	IComponent* getComponent(string componentName);

	Text* text;
	void movingLeft(float x, float y);
	void movingRight(float x, float y);
	~KnifeShort();
private:

	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	Vector2 _originPosition;
};
#endif _KNIFE_SHORT_H
