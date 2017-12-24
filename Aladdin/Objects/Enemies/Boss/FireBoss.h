#ifndef _FIRE_BOSS_H
#define _FIRE_BOSS_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../../BaseObject.h"
#include"../../FrameWork/CollisionBody.h"
#include"../../GameObjects/Aladdin.h"

using namespace std;

#define FIRE_SPEED 270

class FireBoss : public BaseObject
{
public:
	FireBoss(int posX, int posY, bool isLeft);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	Text* text;

	void movingLeft();
	void movingRight();
	void standing();
	~FireBoss();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	bool _isLeft;
};
#endif _FIRE_BOSS_H
