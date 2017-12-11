#ifndef _FALLING_PLATFORM_H
#define _FALLING_PLATFORM_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../../FrameWork/CollisionBody.h"
#include "../BaseObject.h"
using namespace std;

#define FALLING_SPEED 80
#define GRAVITY 800

class FallingPlatform : public BaseObject
{
public:
	FallingPlatform(int posX, int posY, eDirection direction);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	IComponent* getComponent(string componentName);

	Text* text;
	void falling();
	void stopFalling();
	void startCount();
	~FallingPlatform();
private:

	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Vector2 _originPosition;
	StopWatch* _countTime;
	bool _drop;
};
#endif _FALLING_PLATFORM_H

