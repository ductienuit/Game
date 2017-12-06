
#ifndef _GUARDLU_H
#define _GUARDLU_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "BaseEnemy.h"
using namespace std;

#define GUARDLU_SPEED 80
#define GUARDLU_SCORE 100

class GuardLu : public BaseEnemy
{
public:
	GuardLu(eStatus status, int posX, int posY, eDirection direction);

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
	~GuardLu();
private:
	void movingLeft();
	void movingRight();
	void standing();

	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	vector<BaseObject*> _listobject;
	vector<IControlable*> _listControlObject;
};
#endif
