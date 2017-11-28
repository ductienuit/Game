#ifndef _THROWACTION
#define _THROWACTION

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "BaseEnemy.h"
using namespace std;

#define THROWACTION_SPEED 30
#define SWORD_GRAVITY 800

class ThrowAction : public BaseEnemy
{
public:
	ThrowAction(eStatus status, int posX, int posY, eDirection direction);

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
	~ThrowAction();
private:
	void movingLeft();
	void movingRight();
	void standing();
	void Throw();
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
};
#endif
