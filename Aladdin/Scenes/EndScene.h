#pragma once
#ifndef __END_SCENE_H__
#define __END_SCENE_H__
/*Phần chưa làm
+ Quadtree
+ text
+ help
+ Danh sách đối tượng nằm trong vùng active.
+ Map
*/
#include"../FrameWork/Scene.h"
#include"../FrameWork/Manager/SpriteManager.h"
#include"../FrameWork/Manager/SceneManager.h"
#include"../FrameWork/debug.h"
#include"../FrameWork/Animation.h"
#include"../FrameWork/ViewPort.h"
#include"../Scenes/EndSceneBackground.h"
#include"../Objects/GameObjects/Aladdin.h"
#include"../Objects/Enemies/Monkey.h"
#include<time.h>
using namespace std;

USEGAME_FRAMEWORK

[event_receiver(native)]
class EndScene :public Scene
{
public:
	EndScene();
	~EndScene();

	bool InIt() override;
	void UpdateInput(float dt) override;
	void Update(float dt) override;
	void Draw(LPD3DXSPRITE spriteHandle) override;
	void Release() override;
private:
	Aladdin * _aladdin;
	Monkey * _monkey;
	Land * _land;
	EndSceneBackground * _endSceneBackground;
	static ViewPort* _viewport;
};

#endif // !__END_SCENE_H__


