#ifndef _FIRE_H
#define _FIRE_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../Score/InforAladdin.h"
#include "BaseEnemy.h"
#include<math.h>
using namespace std;

class Fire : public BaseEnemy
{
public:
	//for level 1
	Fire(eStatus, int , int, eDirection direction);
	//for scene boss
	Fire(eStatus, int, int, Vector2);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	IComponent* getComponent(string componentName);

	RECT getBounding() override;
	Text* text;
	~Fire();
private:

	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
};
#endif
