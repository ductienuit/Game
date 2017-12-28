#ifndef _PEDDLER_SHOP_H
#define _PEDDLER_SHOP_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../../FrameWork/CollisionBody.h"
#include "../BaseObject.h"
#include "../GameObjects/Peddler.h"
#include "../Score/InforAladdin.h"
#include"../../FrameWork/ViewPort.h"
#include"../Score/Alphabet.h"
#include<string.h>


class PeddlerShop :public BaseObject
{
public:
	PeddlerShop(int posX, int posY, BaseObject* aladdin);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	float distanceBetweenAladdin();

	RECT getBounding() override;
	~PeddlerShop();
private:
	Peddler* peddler;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Text* text;
	BaseObject* _aladdin;
	bool canDisappear = true;
	bool canBuyItem = true;
	Alphabet* _buyNotification;
	Vector2 newPosition;
};
#endif _PEDDLER_SHOP_H