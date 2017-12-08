
#ifndef _THROWJAR_H
#define _THROWJAR_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../Enemies/Jar.h"
#include "BaseEnemy.h"
using namespace std;

#define THROWJAR_SPEED 0
#define THROWJAR_SCORE 100

class ThrowJar : public BaseEnemy
{
public:
	ThrowJar(eStatus status, int posX, int posY);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	Vector2 distanceBetweenAladdin();
	void UpdateStatus(float dt);

	IComponent* getComponent(string componentName);

	Text* text;
	~ThrowJar();
private:
	void standing();
	//void Throw(float deltatime);

	Jar* jar;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	vector<BaseObject*> _listobject;
	vector<IControlable*> _listControlObject;
	eStatus _currentAnimateIndex;
	bool _canDrop;
};
#endif