#pragma once
#ifndef _CHOOSE_H_
#define _CHOOSE_H_

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../../FrameWork/CollisionBody.h"
#include "../../FrameWork/InputController.h"
#include "../Score/InforAladdin.h"
#include "../BaseObject.h"

#include "../../Scenes/PlayScene.h"
#include"../../Scenes/BossScene.h"

using namespace std;

class Choose : public BaseObject
{
public:
	Choose(int posX, int posY);
	void InIt() override;;
	void UpdateInput(float dt);
	void Update(float deltatime) override;;
	void Draw(LPD3DXSPRITE, ViewPort*) override;;
	void Release() override;

	~Choose();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;

};
#endif //_CHOOSE_H_