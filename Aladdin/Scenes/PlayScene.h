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
#include"../FrameWork/Manager/SoundManager.h"


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
#include"../Objects/GameObjects/EatHeart.h"


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

	//Trả về một đối tượng theo id
	//id để dịnh danh một đối tượng
	BaseObject* getObject(eID id);
private:
	//Quadtree
	QuadTree* _root;

	//Nếu object hết hạn sử dụng thì hủy đối tượng
	void destroyObject();   

	//Danh sach các đói tượng hoạt động rộng không thể đưa vào quadtree như Aladdin
	//vector<BaseObject*> _listObject;

	//Danh sách các đối tượng dùng để tạo trong quadtree
	map<string, BaseObject*> _mapObject;

	/*
	Danh sách các đối tượng nằm trong camera
	Mỗi vòng lặp sẽ truyền vào rect camera và trả về các object nằm trong*/
	vector<BaseObject*> _activeObject;

	/* 
	Danh sách những đối tượng được UpdateInput
	*/
	vector<IControlable*> _listControlObject;

	Aladdin* _aladdin;
	BaseObject* _weaponmanager;

	/*Danh sách các đối tượng va chạm mềm*/
	vector<BaseObject*> Bar;			//Thanh xà ngang
	vector<BaseObject*> Rope;			//Dây
	vector<BaseObject*> Solid;			//Đất
	vector<BaseObject*> Spring;			//Cục nhún
	vector<BaseObject*> Platform;		//Thanh gỗ
	vector<BaseObject*> CheckOn[4];

	//Main background
	BackGround* _background;
	//Front background
	BackGroundFront* _backgroundfront;
	//Sky background;

	//Chuyển đổi tọa độ word sang viewport
	static ViewPort* _viewport;

	Sprite* sprite;
	
	Animation* _animation;
	//map object
	ReadMapEditor* mMap;
	RECT* rect;
};

#endif // !__PLAY_SCENE_H__





