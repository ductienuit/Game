
#ifndef _GuardThrowJar_H
#define _GuardThrowJar_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../Enemies/Jar.h"
#include "BaseEnemy.h"
using namespace std;

#define GuardThrowJar_SPEED 0
#define GuardThrowJar_SCORE 100

class GuardThrowJar : public BaseEnemy
{
public:
	GuardThrowJar(eStatus status, int posX, int posY,int distancebroken);

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
	~GuardThrowJar();
private:
	void standing();
	//void Throw(float deltatime);
	int _distancebroken;
	vector<Jar*> _listJar;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	vector<BaseObject*> _listobject;
	vector<IControlable*> _listControlObject;
	eStatus _currentAnimateIndex;
	bool _canDrop;
};
#endif