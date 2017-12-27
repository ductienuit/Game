#ifndef __READMAPEDITOR_H__
#define __READMAPEDITOR_H__

#include"../Resources/MapReader/Tmx.h"
#include"../Objects/BaseObject.h"
#include"../FrameWork/QuadTree.h"
#include"../Objects/Enemies/GuardLu.h"
#include"../Objects/Enemies/GuardShort.h"
#include"../Objects/Enemies/GuardThin.h"
#include"../Objects/Enemies/GuardThrowJar.h"
#include"../Objects/Enemies/Fire.h"
#include"../Objects/Enemies/GuardFat.h"
#include"../Objects/Enemies/GuardKnifeThrower.h"
#include"../Objects/GameObjects/EatApple.h"
#include"../Objects/GameObjects/EatHeart.h"
#include"../Objects/GameObjects/Land.h"
#include"../Objects/GameObjects/Camel.h"
#include"../Objects/GameObjects/RestartPoint.h"
#include"../Objects/GameObjects/FallingPlatform.h"
#include"../Objects/GameObjects/Spring.h"
#include"../Objects/GameObjects/Boom.h"
#include"../Objects/GameObjects/EatCoin.h"
#include"../Objects/GameObjects/Peddler.h"
#include"../Objects/GameObjects/PeddlerShop.h"
#include"../FrameWork/StopWatch.h"


class ReadMapEditor
{
public:
	ReadMapEditor(BaseObject* aladdin, const char* filepath, QuadTree* &_quadTree);
	ReadMapEditor(BaseObject* aladdin, const char* filepath, QuadTree* &_quadTree, bool isBossScene);
	~ReadMapEditor();
	Tmx::Map* maps;
	vector <BaseObject*>     GetList;

	vector <BaseObject*>	 ListBoom;
	vector <BaseObject*>	 ListGuardLu;
	vector <BaseObject*>	 ListGuardThin;
	vector <BaseObject*>	 ListGuardShort;
	vector <BaseObject*>	 ListFire;
	vector <BaseObject*>	 ListGuardFat;
	vector <BaseObject*>     ListGuardThrowJar;
	vector <BaseObject*>     ListKnifeThrower;
	vector <BaseObject*>	 ListLand;
	vector <BaseObject*>	 ListEatApple;
	vector <BaseObject*>	 ListEatHeart;
 	vector <BaseObject*>	 ListCamel;
	vector <BaseObject*>	 ListEatCoin;
	vector <BaseObject*>	 ListRestartPoint;
	vector <BaseObject*>	 ListFallingPlatform;
	vector <BaseObject*>	 ListSpring;
	vector <BaseObject*>	 ListPeddlerShop;

	//GetList for Scene 1
	void ListObject(RECT *rect);
	//GetList for Scene Boss
	void ListObject(RECT *rect, bool isVersion2);
	QuadTree* _QuadTree;
	StopWatch* _frequentAppleBoss;
	
	void UpDate(float detatime);
	bool isContain(BaseObject*object, RECT rect);
};
#endif __READMAPEDITOR_H__
