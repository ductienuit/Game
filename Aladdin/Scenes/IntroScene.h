#pragma once
#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__
#include"../FrameWork/Scene.h"
#include"../FrameWork/Manager/SpriteManager.h"
#include"../FrameWork/Manager/SceneManager.h"
#include"../FrameWork/debug.h"
#include"../FrameWork/Animation.h"

#include<time.h>


using namespace std;

USEGAME_FRAMEWORK

[event_receiver(native)]
class IntroScene :public Scene
{
public:
	IntroScene();
	~IntroScene();

	bool InIt() override;
	void UpdateInput(float dt) override;
	void Update(float dt) override;
	void Draw(LPD3DXSPRITE spriteHandle) override;
	void Release() override;
private:
};

#endif // !__INTRO_SCENE_H__





