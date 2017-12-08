#ifndef _JAR_H
#define _JAR_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "BaseEnemy.h"
using namespace std;

#define JAR_GRAVITY 800


class Jar : public BaseEnemy
{
public:
	Jar(eStatus status, int posX, int posY, eDirection direction);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	float distanceBetweenAladdin();

	IComponent* getComponent(string componentName);
	float PositionY();
	Text* text;
	map<int, Animation*> _animations;
	void standing();
	void Drop();
	~Jar();
private:
	void movingDown();


	map<string, IComponent*> _listComponent;

	Sprite *_divingSprite;
	Vector2 _originPosition;
	eStatus _currentAnimateIndex;
};
#endif