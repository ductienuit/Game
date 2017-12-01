
#ifndef _GUARDSHORT_H
#define _GUARDSHORT_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../Enemies/Knife.h"
#include "BaseEnemy.h"
using namespace std;

#define GUARDSHORT_SPEED 30
#define GUARDSHORT_SCORE 100

class GuardShort : public BaseEnemy
{
public:
	GuardShort(eStatus status, int posX, int posY, eDirection direction);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, Viewport*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	float distanceBetweenAladdin();
	void UpdateStatus(float dt);

	IComponent* getComponent(string componentName);

	Text* text;
	~GuardShort();
private:
	void movingLeft();
	void movingRight();
	void standing();
	void Throw(float deltatime);

	Knife* knife;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	vector<BaseObject*> _listobject;
	vector<IControlable*> _listControlObject;
	bool _canThrow;
};
#endif
