
#ifndef _KNIFETHROWER_H
#define _KNIFETHROWER_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../Enemies/Knife.h"
#include "BaseEnemy.h"
using namespace std;

#define KNIFETHROWER_SPEED 0
#define KNIFETHROWER_SCORE 100

class KnifeThrower : public BaseEnemy
{
public:
	KnifeThrower(eStatus status, int posX, int posY, eDirection direction);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	float distanceBetweenAladdin();
	void UpdateStatus(float dt);

	IComponent* getComponent(string componentName);

	Text* text;
	~KnifeThrower();
private:
	void movingLeft();
	void movingRight();

	Knife* knife;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	vector<BaseObject*> _listobject;
	vector<IControlable*> _listControlObject;
	bool _canThrow;
};
#endif
