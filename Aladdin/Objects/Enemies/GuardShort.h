
#ifndef _GUARDSHORT_H
#define _GUARDSHORT_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../Enemies/KnifeShort.h"
#include "BaseEnemy.h"
#include	<math.h>

using namespace std;

#define GUARDSHORT_SPEED 30
#define GUARDSHORT_SCORE 100

class GuardShort : public BaseEnemy
{
public:
	GuardShort(eStatus status, int posX, int posY, BaseObject* aladdin, int minMove, int maxMove);

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
	~GuardShort();
private:
	void movingLeft();
	void movingRight();
	void standing();
	void Throw(float deltatime);

	KnifeShort* knife;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	BaseObject* _aladdin;
	vector<BaseObject*> _listObject;
	vector<IControlable*> _listControlObject;
	Vector2 _originPosition;
	bool _canThrow;
};
#endif
