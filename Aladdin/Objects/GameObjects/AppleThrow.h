#ifndef _APPLETHROW_H
#define _APPLETHROW_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../../FrameWork/CollisionBody.h"
using namespace std;

#define APPLETHROW_SPEED 300
#define APPLETHROW_GRAVITY 800
#define APPLETHROW_JUMP 100

class AppleThrow : public BaseObject
{
public:
	AppleThrow(eStatus status, int posX, int posY, eDirection direction);
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
	~AppleThrow();
private:


	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	Vector2 _originPosition;
};
#endif _APPLETHROW_H
