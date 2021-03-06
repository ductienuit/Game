#ifndef _CAMEL_H
#define _CAMEL_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../../FrameWork/CollisionBody.h"
#include "../BaseObject.h"
#include "BulletCamel.h"


class Camel :public BaseObject
{
public:
	Camel(int posX, int posY);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	RECT getBounding() override;
	~Camel();
private:
	BulletCamel *bulletCamel;
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Text* text;
};
#endif _CAMEL_H

