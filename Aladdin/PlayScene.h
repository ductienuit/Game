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

#include"../Aladdin/FrameWork/Scene.h"
#include"../Aladdin/FrameWork/Manager/SpriteManager.h"
#include"../Aladdin/FrameWork/Manager/SceneManager.h"
#include"../Aladdin/FrameWork/debug.h"
#include"../Aladdin/FrameWork/Animation.h"

#include"../Aladdin/Objects/GameObjects/Aladdin.h"

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

	void setViewport(Viewport* viewport);
	static Viewport* getViewport();

	//Trả về một đối tượng theo id
	//id để dịnh danh một đối tượng
	BaseObject* getObject(eID id);

	//Lấy đối tượng Aladdin
	Aladdin* getAladdin();
private:
	void destroyObject();   //Nếu object hết hạn sử dụng thì hủy đối tượng

	//Danh sach các đói tượng hoạt động rộng không thể đưa vào quadtree như Aladdin
	vector<BaseObject*> _listObject;

	//Danh sách các đối tượng dùng để tạo trong quadtree
	map<string, BaseObject*> _mapObject;

	BaseObject* _aladdin;
	BaseObject* _weaponmanager;
	void UpdateViewport(BaseObject* objTracker);






	static Viewport* _viewport;
	Sprite* sprite;
	vector<BaseObject*> _listobject;
	vector<IControlable*> _listControlObject;
	Animation* _animation;
};

#endif // !__PLAY_SCENE_H__





