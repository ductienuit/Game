#ifndef _HEALTH_H
#define _HEALTH_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../Score/InforAladdin.h"
#include"../GameObjects/Aladdin.h"
#include"../../FrameWork/ViewPort.h"

class Health :public BaseObject
{
public:
	Health(BaseObject* aladdin, int posX = 100, int posY = 100);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	~Health();
private:
	map<int, Animation*> _animations;
	int iStatus;
	Aladdin* _aladdin;   //Set status for aladdin
};
#endif _HEALTH_H