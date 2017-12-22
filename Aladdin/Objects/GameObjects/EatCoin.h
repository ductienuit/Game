#ifndef _COIN_EAT_H_
#define _COIN_EAT_H_

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../../FrameWork/CollisionBody.h"
#include"../Score/InforAladdin.h"
#include "../BaseObject.h"

using namespace std;

class EatCoin : public BaseObject
{
public:
	EatCoin(int posX, int posY);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);
	~EatCoin();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Text* text;
};
#endif _COIN_EAT_H_