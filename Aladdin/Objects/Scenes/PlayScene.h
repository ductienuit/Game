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
#include"../../FrameWork/Scene.h"
#include"../../FrameWork/Manager/SpriteManager.h"
#include"../../FrameWork/Manager/SceneManager.h"
#include"../../FrameWork/debug.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/Camera.h"
#include"../GameObjects/Objects/Aladdin.h"
#include"../GameObjects/Objects/Land.h"
#include"../Enemies/GuardThin.h"
#include"../Enemies/GuardShort.h"
#include"../Enemies/Knife.h"
#include"BackGround.h"
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
	void destroyObject();   //Nếu object hết hạn sử dụng thì hủy đối tượng
	BackGround* background;
	Camera* camera;

	//Danh sach các đói tượng hoạt động rộng không thể đưa vào quadtree như Aladdin
	vector<BaseObject*> _listObject;

	//Danh sách các đối tượng dùng để tạo trong quadtree
	map<string, BaseObject*> _mapObject;

	Aladdin* _aladdin;
	BaseObject* _weaponmanager;

	BaseObject* testLand;

	vector<BaseObject*> Bar;
	vector<BaseObject*> Rope;
	vector<BaseObject*> Solid;
	vector<BaseObject*> Spring;
	vector<BaseObject*> Platform;

	static ViewPort* _viewport;
	Sprite* sprite;
	vector<BaseObject*> _listobject;
	vector<IControlable*> _listControlObject;
	Animation* _animation;
};

#endif // !__PLAY_SCENE_H__





