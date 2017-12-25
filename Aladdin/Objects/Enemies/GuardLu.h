#ifndef _GUARDLU_H
#define _GUARDLU_H
#include "BaseEnemy.h"
#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../Enemies/BaseEnemy.h"
#include"../GameObjects/Aladdin.h"

using namespace std;

#define GUARDLU_SPEED 30
#define GUARDLU_SCORE 100

class GuardLu : public BaseEnemy
{
public:
	GuardLu(eStatus status, int posX, int posY, BaseObject* aladdin, int minMove, int maxMove);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	RECT getBounding() override;

	Vector2 distanceBetweenAladdin();
	void UpdateStatus(float dt);

	IComponent* getComponent(string componentName);

	Text* text;
	~GuardLu();
private:
	BaseObject * _aladdin;
	void movingLeft();
	void movingRight();
	void standing();

	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	vector<BaseObject*> _listObject;
	vector<IControlable*> _listControlObject;
};
#endif
