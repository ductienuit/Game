#ifndef _APPLETHROW_H
#define _APPLETHROW_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../../FrameWork/CollisionBody.h"
using namespace std;

#define APPLE_SPEED 630
#define APPLE_GRAVITY 600

class AppleThrow : public BaseObject
{
public:
	AppleThrow(int posX, int posY,bool isLeft);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	IComponent* getComponent(string componentName);

	Text* text;

	void movingLeft();
	void movingRight();
	void standing();
	~AppleThrow();
private:

	int count = 0;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Vector2 _originPosition;
	bool _isLeft;
};
#endif _APPLETHROW_H
