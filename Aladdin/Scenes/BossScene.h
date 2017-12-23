#pragma once
#ifndef __BOSS_SCENE_H__
#define __BOSS_SCENE_H__
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
#include"../Objects/Enemies/Fire.h"

#include"../Objects/Score/Health.h"
#include"../Objects/Score/InforAladdin.h"
#include"../Objects/Score/Life.h"
#include"../Objects/Score/Coin.h"
#include"../Objects/Score/Apple.h"
#include"../Objects/Score/Alphabet.h"



#include<time.h>

#include"BackGroundBoss.h"
#include"BackGroundBossFront.h"
using namespace std;
#define SIZEMAPBOSS	D3DXVECTOR2(1504*1.2,691*1.2)


USEGAME_FRAMEWORK

[event_receiver(native)]
class BossScene :public Scene
{
public:
	BossScene();
	~BossScene();

	bool InIt() override;
	void UpdateInput(float dt) override;
	void Update(float dt) override;
	void Draw(LPD3DXSPRITE spriteHandle) override;
	void Release() override;


	void UpdateViewport(BaseObject* aladdin);
private:
	//Quadtree
	QuadTree*				 _root;
	//Danh sách các đối tượng dùng để tạo trong quadtree
	map<string, BaseObject*> _mapObject;
	
	/*Danh sách các đối tượng nằm trong camera
	Mỗi vòng lặp sẽ truyền vào rect camera và trả về các object nằm trong*/
	vector<BaseObject*>		 _activeObject;
	Aladdin*				 _aladdin;
	InforAladdin*			 _scoreAla;

	//Main background
	BackGroundBoss*				 _back;
	//Front background
	BackGroundBossFront*		 _front;
	vector<BaseObject*>		_listScore;

	//Chuyển đổi tọa độ word sang viewport
	static ViewPort* _viewport;

	Animation* _animation;
	//map object
	ReadMapEditor* mMap;
	RECT* rect;
};

#endif // !__BOSS_SCENE_H__





