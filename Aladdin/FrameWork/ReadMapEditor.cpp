﻿#include "ReadMapEditor.h"
extern 	vector<BaseObject*> listStair[2];

vector<BaseObject*> listFireActive;
vector<BaseObject*> listActive;
extern vector<BaseObject*> listFireUnderBossVer2;


typedef struct maxmin MaxMin;

map<int, int> distanceThrowJar;
map<int, MaxMin> distanceGuardThin;
map<int, MaxMin> distanceGuardFat;
map<int, MaxMin> distanceGuardLu;
map<int, MaxMin> distanceGuardShort;

struct maxmin
{
	maxmin() {}
	maxmin(float left ,float right)
	{
		_left = left*1.6f;
		_right = right*1.6f;
	}
	float _left;
	float _right;
};

ReadMapEditor::ReadMapEditor(BaseObject* aladdin, const char *filepath, QuadTree *& _quadTree)
{
	#pragma region DistanceBrokenJar
	distanceThrowJar[0] = 148 * 1.92;
	distanceThrowJar[1] = 116 * 1.92;
	distanceThrowJar[2] = 88 * 1.92;
	distanceThrowJar[3] = 88 * 1.92;
	distanceThrowJar[4] = 102 * 1.92;
	distanceThrowJar[5] = 102 * 1.92;
	distanceThrowJar[6] = 102 * 1.92;
	distanceThrowJar[7] = 97 * 1.92;
	distanceThrowJar[8] = 98 * 1.92;
	distanceThrowJar[9] = 106 * 1.92;
#pragma endregion

	#pragma region DistanceGuardThin
	distanceGuardThin[0] = MaxMin(60, 136);
	distanceGuardThin[1] = MaxMin(98, 9);
	#pragma endregion

	#pragma region DistanceGuardFat
	distanceGuardFat[0] = MaxMin(0, 0);
	distanceGuardFat[1] = MaxMin(218, 267);
	distanceGuardFat[2] = MaxMin(50, 102);
	distanceGuardFat[3] = MaxMin(391, 0);
	distanceGuardFat[4] = MaxMin(33, 40);
	distanceGuardFat[5] = MaxMin(88, 42);
	distanceGuardFat[6] = MaxMin(25, 82);
	distanceGuardFat[7] = MaxMin(146, 155);
#pragma endregion

	#pragma region DistanceGuardLu
	distanceGuardLu[0] = MaxMin(0, 182);

#pragma endregion

	#pragma region DistanceGuardShort
	distanceGuardShort[0] = MaxMin(243, 84);
	distanceGuardShort[1] = MaxMin(214 ,150);
	distanceGuardShort[2] = MaxMin(75, 100);
	distanceGuardShort[3] = MaxMin(216, 149);
	distanceGuardShort[4] = MaxMin(247, 276);
	distanceGuardShort[5] = MaxMin(121, 84);
	distanceGuardShort[6] = MaxMin(10, 48);
	distanceGuardShort[7] = MaxMin(161, 451);
	distanceGuardShort[8] = MaxMin(146, 52);
	distanceGuardShort[9] = MaxMin(234, 84);
	distanceGuardShort[10] = MaxMin(32, 12);
#pragma endregion

	////Nếu object khác. Thì tạo list cho object đó
	//distanceGuardLu
	//	distanceGuardFat ....... OKKKKKKKKKKKKKKK
	/*Tạo distance toàn bộ object có yêu cầu nhập maxmin*/

	GetList.clear();
	maps = new Tmx::Map();
	maps->ParseFile(filepath);
	RECT rect;
	rect.left = 0;
	rect.right = maps->GetWidth();
	rect.bottom = maps->GetHeight();
	rect.top = 0;
	_quadTree = new QuadTree(rect, 1);
	_QuadTree = _quadTree;
	int x = maps->GetNumObjectGroups();
	for (size_t i = 0; i < maps->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *_objectGroup = maps->GetObjectGroup(i);
		if (_objectGroup->GetName() == "guardshort")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardShort* _guardshort = new GuardShort(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), aladdin, distanceGuardShort[j]._left, distanceGuardShort[j]._right);

				ListGuardShort.push_back(_guardshort);
				_QuadTree->InsertStaticObject(_guardshort);
			}
		}

		else if (_objectGroup->GetName() == "facesmile")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				FaceSmile* _face = new FaceSmile(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());

				ListFaceSmile.push_back(_face);
				_QuadTree->InsertStaticObject(_face);
			}
		}

		else if (_objectGroup->GetName() == "guardthin")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardThin* _guardthin = new GuardThin(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), aladdin, distanceGuardThin[j]._left, distanceGuardThin[j]._right);

				ListGuardThin.push_back(_guardthin);
				_QuadTree->InsertStaticObject(_guardthin);
			}
		}

		else if (_objectGroup->GetName() == "guardlu")
		{

			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardLu* _guardlu = new GuardLu(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), aladdin, distanceGuardLu[j]._left, distanceGuardLu[j]._right);

				ListGuardLu.push_back(_guardlu);
				_QuadTree->InsertStaticObject(_guardlu);
			}
		}

		else if (_objectGroup->GetName() == "fire")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				Fire* _fire = new Fire(BEHIT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(),NONE);

				ListFire.push_back(_fire);
				_QuadTree->InsertStaticObject(_fire);
			}
		}

		else if (_objectGroup->GetName() == "guardbig")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardFat* _guardFat = new GuardFat(FREE, _object->GetX() , 688 - _object->GetY() - _object->GetHeight(), aladdin, distanceGuardFat[j]._left, distanceGuardFat[j]._right);

				ListGuardFat.push_back(_guardFat);
				_QuadTree->InsertStaticObject(_guardFat);
			}
		}

		else if (_objectGroup->GetName() == "guardthrowjar")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardThrowJar* _guardThrowJar = new GuardThrowJar(FREE, _object->GetX()+16, 688 - _object->GetY() - _object->GetHeight(),distanceThrowJar[(int)(j)], aladdin);

				ListGuardThrowJar.push_back(_guardThrowJar);
				_QuadTree->InsertStaticObject(_guardThrowJar);
			}
		}

		else if (_objectGroup->GetName() == "knifethrower")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				GuardKnifeThrower* _knifeThrower = new GuardKnifeThrower(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), aladdin);

				ListKnifeThrower.push_back(_knifeThrower);
				_QuadTree->InsertStaticObject(_knifeThrower);
			}
		}

		else if (_objectGroup->GetName() == "stair")
		{
				for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* _object = _objectGroup->GetObjects().at(j);

					Land* _stair = new Land(_object->GetX(),688-_object->GetY()- _object->GetHeight(),_object->GetWidth(),_object->GetHeight(),NONE ,STAIR);

					ListLand.push_back(_stair);
					_QuadTree->InsertStaticObject(_stair);
				}
		}

		else if (_objectGroup->GetName() == "stair1")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _stair = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, STAIR);

				listStair[0].push_back(_stair);
				_QuadTree->InsertStaticObject(_stair);
			}
		}

		else if (_objectGroup->GetName() == "stair2")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _stair = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, STAIR);

				listStair[1].push_back(_stair);
				_QuadTree->InsertStaticObject(_stair);
			}
		}

		else if (_objectGroup->GetName() == "wall")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _wall = new Land(_object->GetX(), 688 - _object->GetY()- _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, WALL);

				ListLand.push_back(_wall);
				_QuadTree->InsertStaticObject(_wall);
			}
		}

		else if (_objectGroup->GetName() == "fallingplatform")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				FallingPlatform* _flatform = new FallingPlatform(_object->GetX(), 688 - _object->GetY()- _object->GetHeight(),NONE);
				ListFallingPlatform.push_back(_flatform);
				_QuadTree->InsertStaticObject(_flatform);
			}
		}

		else if (_objectGroup->GetName() == "rope")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _rope = new Land(_object->GetX(), 688 - _object->GetY()- _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, ROPE);
				ListLand.push_back(_rope);
				_QuadTree->InsertStaticObject(_rope);
			}
		}

		else if (_objectGroup->GetName() == "stop")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _stop = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, STOP);
				ListLand.push_back(_stop);
				_QuadTree->InsertStaticObject(_stop);
			}
		}

		else if (_objectGroup->GetName() == "bar")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _bar = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, BAR);

				ListLand.push_back(_bar);
				_QuadTree->InsertStaticObject(_bar);
			}
		}

		else if (_objectGroup->GetName() == "spring")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Spring* _spring = new Spring(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());

				ListSpring.push_back(_spring);
				_QuadTree->InsertStaticObject(_spring);
			}
		}

		else if (_objectGroup->GetName() == "solid")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _solid = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, SOLID);

				ListLand.push_back(_solid);
				_QuadTree->InsertStaticObject(_solid);
			}
		}

		else if (_objectGroup->GetName() == "apple")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				EatApple* _apple = new EatApple( _object->GetX() , 688 - _object->GetY() - _object->GetHeight());

				ListEatApple.push_back(_apple);
				_QuadTree->InsertStaticObject(_apple);
			}
		}
		
		else if (_objectGroup->GetName() == "heart")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				EatHeart* _heart = new EatHeart(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());

				ListEatHeart.push_back(_heart);
				_QuadTree->InsertStaticObject(_heart);
			}
		}

		else if (_objectGroup->GetName() == "coin")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);
				EatCoin* _coin = new EatCoin(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());
				ListEatCoin.push_back(_coin);
				_QuadTree->InsertStaticObject(_coin);
			}
		}

		else if (_objectGroup->GetName() == "camel")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				Camel* _camel = new Camel(_object->GetX(), 688 - _object->GetY()-_object->GetHeight());

				ListCamel.push_back(_camel);
				_QuadTree->InsertStaticObject(_camel);
			}
		}

		else if (_objectGroup->GetName() == "peddlershop")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				PeddlerShop* _peddlershop = new PeddlerShop(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(),aladdin);

				ListPeddlerShop.push_back(_peddlershop);
				_QuadTree->InsertStaticObject(_peddlershop);
			}
		}

		else if (_objectGroup->GetName() == "restartpoint")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				RestartPoint* _restart = new RestartPoint(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());

				ListRestartPoint.push_back(_restart);
				_QuadTree->InsertStaticObject(_restart);
			}
		}

		else if (_objectGroup->GetName() == "boom")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);
				Boom* _boom = new Boom(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());
				ListBoom.push_back(_boom);
				_QuadTree->InsertStaticObject(_boom);
			}
		}
	}
}

ReadMapEditor::ReadMapEditor(BaseObject* aladdin, const char * filepath, QuadTree *& _quadTree, bool isBossScene)
{
	maps = new Tmx::Map();
	maps->ParseFile(filepath);
	RECT rect;
	rect.left = 0;
	rect.right = maps->GetWidth();
	rect.bottom = maps->GetHeight();
	rect.top = 0;
	_quadTree = new QuadTree(rect, 1);
	_QuadTree = _quadTree;
	int x = maps->GetNumObjectGroups();
	for (size_t i = 0; i < maps->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *_objectGroup = maps->GetObjectGroup(i);

		if (_objectGroup->GetName() == "apple")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				EatApple* _apple = new EatApple(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(),true);

				ListEatApple.push_back(_apple);
				_QuadTree->InsertStaticObject(_apple);
			}
		}

		else if (_objectGroup->GetName() == "fire")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				Fire* _fire = new Fire(BEHIT, _object->GetX(), 691 - _object->GetY() - _object->GetHeight(),SCALEBOSSFRONT);

				ListFire.push_back(_fire);
				_QuadTree->InsertStaticObject(_fire);
			}
		}

		else if (_objectGroup->GetName() == "wall")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _wall = new Land(_object->GetX(), 691 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), WALL, SCALEBOSSFRONT);

				ListLand.push_back(_wall);
				_QuadTree->InsertStaticObject(_wall);
			}
		}

		else if (_objectGroup->GetName() == "solid")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _solid = new Land(_object->GetX(), 691 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), SOLID,SCALEBOSSFRONT);

				ListLand.push_back(_solid);
				_QuadTree->InsertStaticObject(_solid);
			}
		}

		else if (_objectGroup->GetName() == "fireinboss")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				Fire* _fire = new Fire(BEHIT, _object->GetX(), 691 - _object->GetY() - _object->GetHeight(), SCALEBOSSFRONT);

				ListFireUnderBoss.push_back(_fire);
				_QuadTree->InsertStaticObject(_fire);
			}
		}
	}
	_frequentAppleBoss = new StopWatch();
}

ReadMapEditor::~ReadMapEditor()
{
}

void ReadMapEditor::ListObject(RECT * rect)
{
	GetList.clear();
	listFireActive.clear();
	for (size_t i = 0; i < ListGuardShort.size(); i++)
	{
		if (isContain(ListGuardShort[i], *rect))
		{
			if (ListGuardShort[i]->isInStatus(DESTROY))
			{
				ListGuardShort[i]->Release();
				delete  ListGuardShort[i];
				ListGuardShort.erase(ListGuardShort.begin() + i);
			}
			else
				GetList.push_back(ListGuardShort[i]);			
		}
	}

	for (size_t i = 0; i < ListGuardLu.size(); i++)
	{
		if (isContain(ListGuardLu[i], *rect))
		{
			if (ListGuardLu[i]->isInStatus(DESTROY))
			{
				ListGuardLu[i]->Release();
				delete  ListGuardLu[i];
				ListGuardLu.erase(ListGuardLu.begin() + i);
			}
			else
				GetList.push_back(ListGuardLu[i]);
		}

	}

	for (size_t i = 0; i < ListGuardThin.size(); i++)
	{
		if (isContain(ListGuardThin[i], *rect))
		{
			if (ListGuardThin[i]->isInStatus(DESTROY))
			{
				ListGuardThin[i]->Release();
				delete  ListGuardThin[i];
				ListGuardThin.erase(ListGuardThin.begin() + i);
			}
			else
				GetList.push_back(ListGuardThin[i]);
		}
	}

	for (size_t i = 0; i < ListGuardFat.size(); i++)
	{
		if (isContain(ListGuardFat[i], *rect))
		{
			if (ListGuardFat[i]->isInStatus(DESTROY))
			{
				ListGuardFat[i]->Release();
				delete  ListGuardFat[i];
				ListGuardFat.erase(ListGuardFat.begin() + i);
			}
			else
				GetList.push_back(ListGuardFat[i]);
		}
	}

	for (size_t i = 0; i < ListGuardThrowJar.size(); i++)
	{
		if (isContain(ListGuardThrowJar[i], *rect))
		{
			if (ListGuardThrowJar[i]->isInStatus(DESTROY))
			{
				ListGuardThrowJar[i]->Release();
				delete  ListGuardThrowJar[i];
				ListGuardThrowJar.erase(ListGuardThrowJar.begin() + i);
			}
			else
				GetList.push_back(ListGuardThrowJar[i]);
		}
	}

	for (size_t i = 0; i < ListKnifeThrower.size(); i++)
	{
		if (isContain(ListKnifeThrower[i], *rect))
		{
			if (ListKnifeThrower[i]->isInStatus(DESTROY))
			{
				ListKnifeThrower[i]->Release();
				delete  ListKnifeThrower[i];
				ListKnifeThrower.erase(ListKnifeThrower.begin() + i);
			}
			else
				GetList.push_back(ListKnifeThrower[i]);
		}
	}

	for (size_t i = 0; i < ListFire.size(); i++)
	{
		if (isContain(ListFire[i], *rect))
		{
			listFireActive.push_back(ListFire[i]);
			GetList.push_back(ListFire[i]);
		}
	}

	for (size_t i = 0; i < ListLand.size(); i++)
	{
		if (isContain(ListLand[i], *rect))
		{
			GetList.push_back(ListLand[i]);
		}		
	}

	for (size_t i = 0; i < ListEatApple.size(); i++)
	{
		if (isContain(ListEatApple[i], *rect))
		{
			if (ListEatApple[i]->isInStatus(DESTROY))
			{
				ListEatApple[i]->Release();
				delete  ListEatApple[i];
				ListEatApple.erase(ListEatApple.begin() + i);
			}
			else
				GetList.push_back(ListEatApple[i]);
		}
	}

	for (size_t i = 0; i < ListFaceSmile.size(); i++)
	{
		if (isContain(ListFaceSmile[i], *rect))
		{
			if (ListFaceSmile[i]->isInStatus(DESTROY))
			{
				ListFaceSmile[i]->Release();
				delete  ListFaceSmile[i];
				ListFaceSmile.erase(ListFaceSmile.begin() + i);
			}
			else
				GetList.push_back(ListFaceSmile[i]);
		}
	}

	for (size_t i = 0; i < ListEatCoin.size(); i++)
	{
		if (isContain(ListEatCoin[i], *rect))
		{
			if (ListEatCoin[i]->isInStatus(DESTROY))
			{
				ListEatCoin[i]->Release();
				delete  ListEatCoin[i];
				ListEatCoin.erase(ListEatCoin.begin() + i);
			}
			else
				GetList.push_back(ListEatCoin[i]);
		}
	}

	for (size_t i = 0; i < ListBoom.size(); i++)
	{
		if (isContain(ListBoom[i], *rect))
		{
			if (ListBoom[i]->isInStatus(DESTROY))
			{
				ListBoom[i]->Release();
				delete  ListBoom[i];
				ListBoom.erase(ListBoom.begin() + i);
			}
			else
				GetList.push_back(ListBoom[i]);
		}
	}

	for (size_t i = 0; i < ListEatHeart.size(); i++)
	{
		if (isContain(ListEatHeart[i], *rect))
		{
			if (ListEatHeart[i]->isInStatus(DESTROY))
			{
				ListEatHeart[i]->Release();
				delete  ListEatHeart[i];
				ListEatHeart.erase(ListEatHeart.begin() + i);
			}
			else
				GetList.push_back(ListEatHeart[i]);
		}
	}


	for (size_t i = 0; i < ListCamel.size(); i++)
	{
		if (isContain(ListCamel[i], *rect))
		{
			GetList.push_back(ListCamel[i]);
		}
	}

	for (size_t i = 0; i < ListPeddlerShop.size(); i++)
	{
		if (isContain(ListPeddlerShop[i], *rect))
		{
			GetList.push_back(ListPeddlerShop[i]);
		}
	}

	for (size_t i = 0; i < ListRestartPoint.size(); i++)
	{
		if (isContain(ListRestartPoint[i], *rect))
		{
			GetList.push_back(ListRestartPoint[i]);
		}
	}

	for each(auto i in ListFallingPlatform)
	{
		if (isContain(i, *rect))
		{

			GetList.push_back(i);
		}
	}


	for (size_t i = 0; i < ListSpring.size(); i++)
	{
		if (isContain(ListSpring[i], *rect))
		{

			GetList.push_back(ListSpring[i]);
		}
	}
	listActive = GetList;
}

void ReadMapEditor::ListObject(RECT * rect, bool isVersion2)
{
	GetList.clear();
	listFireActive.clear();
	listFireUnderBossVer2.clear();

	if (isVersion2)
	{
		for (size_t i = 0; i < ListFireUnderBoss.size(); i++)
		{
			if (isContain(ListFireUnderBoss[i], *rect))
			{
				listFireUnderBossVer2.push_back(ListFireUnderBoss[i]);
				GetList.push_back(ListFireUnderBoss[i]);
			}
		}
		for (size_t i = 0; i < ListFire.size(); i++)
		{
			if (isContain(ListFire[i], *rect))
			{
				listFireActive.push_back(ListFire[i]);
				GetList.push_back(ListFire[i]);
			}
		}
		if (_frequentAppleBoss->isStopWatch(6000))
		{
			for (size_t i = 0; i < ListEatApple.size(); i++)
				if (isContain(ListEatApple[i], *rect))
				{
					ListEatApple[i]->setStatus(NORMAL);
					GetList.push_back(ListEatApple[i]);
					_frequentAppleBoss->restart();
				}
		}
		else
		{
			for (size_t i = 0; i < ListEatApple.size(); i++)
				if (isContain(ListEatApple[i], *rect))
				{
					GetList.push_back(ListEatApple[i]);
				}
		}
	}

	for (size_t i = 0; i < ListLand.size(); i++)
	{
		if (isContain(ListLand[i], *rect))
		{
			GetList.push_back(ListLand[i]);
		}
	}

	listActive = GetList;
}

void ReadMapEditor::UpDate(float detatime)
{

}

bool ReadMapEditor::isContain(BaseObject*object, RECT rect1)
{
	/*25/11 Đức Tiến đã sửa*/
	RECT rect2 = object->getBounding();
	swap(rect2.top, rect2.bottom);
	return !(rect2.left > rect1.right || rect2.right < rect1.left || rect2.top > rect1.bottom || rect2.bottom < rect1.top);
}


