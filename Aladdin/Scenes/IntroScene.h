#pragma once
#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__
#include"../FrameWork/Scene.h"
#include"../FrameWork/Manager/SpriteManager.h"
#include"../FrameWork/Manager/SceneManager.h"
#include"../FrameWork/debug.h"
#include"../FrameWork/Animation.h"
#include"../FrameWork/Manager/SoundManager.h"
#include"../Objects/BaseObject.h"
#include "../FrameWork/define.h"
#include"../FrameWork/ViewPort.h"

#include<time.h>

#include"../Objects/GameObjects/Aladdin.h"
#include "BackGround/BackgroundMenu.h"
#include"../Objects/Score/Alphabet.h"
#include"../Objects/Score/Choose.h"

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

	void setViewPort(ViewPort* viewport);
private:
	Choose* _choose;
	Alphabet* _strScene1;
	Alphabet* _strSceneBoss;
	BackgroundMenu* _menuBackground;
	/*Chuyển đổi tọa độ word sang viewport*/
	static ViewPort* _viewport;
	
};

#endif // !__INTRO_SCENE_H__





