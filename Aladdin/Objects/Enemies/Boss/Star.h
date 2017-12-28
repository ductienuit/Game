#ifndef _STAR_H
#define _STAR_H

#include "../../../FrameWork/Animation.h"
#include "../../../FrameWork/StopWatch.h"
#include "../../../FrameWork/IComponent.h"
#include "../../../FrameWork/Text.h"
#include "../../BaseObject.h"
#include"../../../FrameWork/CollisionBody.h"
#include"../../GameObjects/Aladdin.h"
#include"StripAladdin.h"
using namespace std;

#define STAR_SPEED 270
#define STAR_GRAVITY 800

class Star : public BaseObject
{
public:
	Star(int posX, int posY, bool isLeft, Aladdin* aladdin);
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
	void setVelocity(float vy);
	~Star();
private:
	Aladdin* _aladdin;
	int count = 0;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Vector2 _originPosition;
	bool _isLeft;
};
#endif _STAR_H
