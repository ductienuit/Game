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
#define KNIFE_SHORT_GRAVITY 3000
#define KNIFE_SHORT_JUMP -100

class KnifeShort : public BaseEnemy
{
public:
	KnifeShort(eStatus status, int posX, int posY);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	IComponent* getComponent(string componentName);

	Text* text;
	void Restart(float x, float y, bool isleft);

	void movingLeft();
	void movingRight();
	~KnifeShort();
private:

	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Vector2 _originPosition;
	bool _isLeft;
};
#endif _KNIFE_SHORT_H
