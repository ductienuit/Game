#pragma once
#ifndef _DEFEAT_SCENE_H_
#define _DEFEAT_SCENE_H_

#include"../FrameWork/Scene.h"
#include"../FrameWork/Manager/SpriteManager.h"
#include"../FrameWork/Manager/SceneManager.h"
#include"../FrameWork/debug.h"
#include"../FrameWork/Animation.h"
#include"../FrameWork/ViewPort.h"
#include"../Objects/GameObjects/Aladdin.h"
#include"../Objects/GameObjects/Monkey.h"

class IntroScene;
#include<time.h>
using namespace std;

USEGAME_FRAMEWORK

[event_receiver(native)]
class DefeatScene :public Scene
{
public:
	DefeatScene();
	~DefeatScene();

	bool InIt() override;
	void UpdateInput(float dt) override;
	void Update(float dt) override;
	void Draw(LPD3DXSPRITE spriteHandle) override;
	void Release() override;
private:
	Aladdin * _aladdin;
	Monkey* _monkey;
	static ViewPort* _viewport;
};

#endif // !_DEFEAT_SCENE_H_


