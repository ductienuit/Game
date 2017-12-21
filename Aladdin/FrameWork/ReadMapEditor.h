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
#include"../Objects/Enemies/KnifeThrower.h"
#include"../Objects/GameObjects/EatApple.h"
#include"../Objects/GameObjects/EatHeart.h"
#include"../Objects/GameObjects/Land.h"
#include"../Objects/GameObjects/Camel.h"
#include"../Objects/GameObjects/RestartPoint.h"
#include"../Objects/GameObjects/FallingPlatform.h"
#include"../Objects/GameObjects/Spring.h"
#include"../Objects/GameObjects/Boom.h"

#include"../Objects/GameObjects/EatCoin.h"


class ReadMapEditor
{
public:
	ReadMapEditor(const char* filepath,QuadTree* &_quadTree);
	~ReadMapEditor();
	Tmx::Map* maps;
	vector <GuardLu*> ListGuardLu;
	vector <GuardThin*> ListGuardThin;
	vector <GuardShort*> ListGuardShort;
	vector <Fire*> ListFire;
	vector <GuardFat*> ListGuardFat;
	vector <GuardThrowJar*> ListGuardThrowJar;
	vector <KnifeThrower*> ListKnifeThrower;
	vector <Land*> ListLand;
	vector <EatApple*> ListEatApple;
	vector <EatHeart*> ListEatHeart;
 	vector <Camel*> ListCamel;
	vector <EatCoin*> ListEatCoin;
	vector <BaseObject*> GetList;
	vector <RestartPoint*> ListRestartPoint;
	vector<FallingPlatform*> ListFallingPlatform;
	vector <Spring*> ListSpring;
	vector <Boom*> ListBoom;

	void ListObject(RECT *rect);
	QuadTree* _QuadTree;

	
	void UpDate(float detatime);
	bool isContain(BaseObject*object, RECT rect);
};
#endif __READMAPEDITOR_H__
