#pragma once
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__
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
#include"../FrameWork/QuadTree.h"
#include"../FrameWork/ReadMapEditor.h"

#include"../Objects/GameObjects/Aladdin.h"
#include"../Objects/GameObjects/Land.h"
#include"../Objects/Enemies/GuardThin.h"
#include"../Objects/Enemies/GuardShort.h"
#include"../Objects/Enemies/GuardLu.h"
#include"../Objects/Enemies/KnifeThrower.h"
#include"../Objects/Enemies/Knife.h"
#include"../Objects/Enemies/Jar.h"
#include"../Objects/Enemies/GuardThrowJar.h"
#include"../Objects/Enemies/Fire.h"
#include"../Objects/GameObjects/FallingPlatform.h"
#include"../Objects/Enemies/GuardFat.h"
#include"../Objects/GameObjects/Camel.h"
#include"../Objects/GameObjects/EatApple.h"
#include"../Objects/GameObjects/RestartPoint.h"
#include"../Objects/GameObjects/EatCoin.h"
#include"../Objects/GameObjects/Spring.h"
#include"../Objects/GameObjects/EatHeart.h"

#include"../Objects/Score/Health.h"
#include"../Objects/Score/InforAladdin.h"
#include"../Objects/Score/Life.h"
#include"../Objects/Score/Coin.h"



#include<time.h>

#include"BackGround.h"
#include"BackGroundFront.h"
using namespace std;

USEGAME_FRAMEWORK

[event_receiver(native)]
class PlayScene:public Scene
{
public:
	PlayScene();
	~PlayScene();

	bool InIt() override;
	void UpdateInput(float dt) override;
	void Update(float dt) override;
	void Draw(LPD3DXSPRITE spriteHandle) override;
	void Release() override;

	void setViewPort(ViewPort* viewport);
	void UpdateViewport(BaseObject* aladdin);
private:
	//Quadtree
	QuadTree*				 _root;
	//Danh sách các đối tượng dùng để tạo trong quadtree
	map<string, BaseObject*> _mapObject;
	/*
	Danh sách các đối tượng nằm trong camera
	Mỗi vòng lặp sẽ truyền vào rect camera và trả về các object nằm trong*/
	vector<BaseObject*>		 _activeObject;
	Aladdin*				 _aladdin;
	InforAladdin*			 _scoreAla;
	BaseObject*				 _weaponmanager;
	vector<BaseObject*>		 CheckOn[4];

	//Main background
	BackGround*				 _background;
	//Front background
	BackGroundFront*		 _backgroundfront;
	vector<BaseObject*>		_listScore;

	//Chuyển đổi tọa độ word sang viewport
	static ViewPort* _viewport;

	Sprite* sprite;

	Animation* _animation;
	//map object
	ReadMapEditor* mMap;
	RECT* rect;
};

#endif // !__PLAY_SCENE_H__





