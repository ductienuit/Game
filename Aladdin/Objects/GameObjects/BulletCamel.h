#ifndef _BULLETCAMEL_H
#define _BULLETCAMEL_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../../FrameWork/CollisionBody.h"
using namespace std;

#define BULLETCAMEL_SPEED 300
#define BULLETCAMEL_GRAVITY 800

class BulletCamel : public BaseObject
{
public:
	BulletCamel(eStatus status, int posX, int posY, eDirection direction);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	IComponent* getComponent(string componentName);

	Text* text;

	void Shoot(float x, float y);
	void standing();
	~BulletCamel();
private:

	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	Vector2 _originPosition;
	Vector2 _currentPosition;
};
#endif _BULLETCAMEL_H