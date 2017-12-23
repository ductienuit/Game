﻿#include "ReadMapEditor.h"
extern 	vector<BaseObject*> Stair[2];
extern vector<BaseObject*> listApple;
vector<BaseObject*> listFireActive;
vector<BaseObject*> listActive;
map<int, int> distanceThrowJar;
map<int, MaxMin> distanceGuardThin;


struct MaxMin;
ReadMapEditor::ReadMapEditor(const char *filepath, QuadTree *& _quadTree)
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
	distanceGuardThin[0] = MaxMin(136, 60);
	distanceGuardThin[1] = MaxMin(9, 98);
	#pragma endregion

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


				GuardShort* _guardshort = new GuardShort(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), NONE, 50, 50);

				ListGuardShort.push_back(_guardshort);
				_QuadTree->InsertStaticObject(_guardshort);
			}
		}

		if (_objectGroup->GetName() == "guardthin")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardThin* _guardthin = new GuardThin(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), NONE);

				ListGuardThin.push_back(_guardthin);
				_QuadTree->InsertStaticObject(_guardthin);
			}
		}

		if (_objectGroup->GetName() == "guardlu")
		{

			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardLu* _guardlu = new GuardLu(FREE, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), NONE);

				ListGuardLu.push_back(_guardlu);
				_QuadTree->InsertStaticObject(_guardlu);
			}
		}

		if (_objectGroup->GetName() == "fire")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				Fire* _fire = new Fire(BEHIT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), NONE);

				ListFire.push_back(_fire);
				_QuadTree->InsertStaticObject(_fire);
			}
		}

		if (_objectGroup->GetName() == "guardbig")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardFat* _guardFat = new GuardFat(FREE, _object->GetX() , 688 - _object->GetY() - _object->GetHeight(), NONE, 50, 50);

				ListGuardFat.push_back(_guardFat);
				_QuadTree->InsertStaticObject(_guardFat);
			}
		}

		if (_objectGroup->GetName() == "guardthrowjar")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardThrowJar* _guardThrowJar = new GuardThrowJar(FREE, _object->GetX()+16, 688 - _object->GetY() - _object->GetHeight(),distanceThrowJar[(int)(j)]);

				ListGuardThrowJar.push_back(_guardThrowJar);
				_QuadTree->InsertStaticObject(_guardThrowJar);
			}
		}

		if (_objectGroup->GetName() == "knifethrower")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				GuardKnifeThrower* _knifeThrower = new GuardKnifeThrower(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), NONE);

				ListKnifeThrower.push_back(_knifeThrower);
				_QuadTree->InsertStaticObject(_knifeThrower);
			}
		}

		if (_objectGroup->GetName() == "stair")
		{
				for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
				{
					Tmx::Object* _object = _objectGroup->GetObjects().at(j);

					Land* _stair = new Land(_object->GetX(),688-_object->GetY()- _object->GetHeight(),_object->GetWidth(),_object->GetHeight(),NONE ,STAIR);

					ListLand.push_back(_stair);
					_QuadTree->InsertStaticObject(_stair);
				}
		}

		if (_objectGroup->GetName() == "stair1")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _stair = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, STAIR);

				Stair[0].push_back(_stair);
				_QuadTree->InsertStaticObject(_stair);
			}
		}

		if (_objectGroup->GetName() == "stair2")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _stair = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, STAIR);

				Stair[1].push_back(_stair);
				_QuadTree->InsertStaticObject(_stair);
			}
		}

		if (_objectGroup->GetName() == "wall")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _wall = new Land(_object->GetX(), 688 - _object->GetY()- _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, WALL);

				ListLand.push_back(_wall);
				_QuadTree->InsertStaticObject(_wall);
			}
		}

		if (_objectGroup->GetName() == "fallingplatform")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				FallingPlatform* _flatform = new FallingPlatform(_object->GetX(), 688 - _object->GetY()- _object->GetHeight(),NONE);
				ListFallingPlatform.push_back(_flatform);
				_QuadTree->InsertStaticObject(_flatform);
			}
		}

		if (_objectGroup->GetName() == "rope")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _rope = new Land(_object->GetX(), 688 - _object->GetY()- _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, ROPE);
				ListLand.push_back(_rope);
				_QuadTree->InsertStaticObject(_rope);
			}
		}

		if (_objectGroup->GetName() == "stop")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _stop = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, STOP);
				ListLand.push_back(_stop);
				_QuadTree->InsertStaticObject(_stop);
			}
		}

		if (_objectGroup->GetName() == "bar")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _bar = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, BAR);

				ListLand.push_back(_bar);
				_QuadTree->InsertStaticObject(_bar);
			}
		}

		if (_objectGroup->GetName() == "spring")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Spring* _spring = new Spring(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());

				ListSpring.push_back(_spring);
				_QuadTree->InsertStaticObject(_spring);
			}
		}

		if (_objectGroup->GetName() == "solid")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				Land* _solid = new Land(_object->GetX(), 688 - _object->GetY() - _object->GetHeight(), _object->GetWidth(), _object->GetHeight(), NONE, SOLID);

				ListLand.push_back(_solid);
				_QuadTree->InsertStaticObject(_solid);
			}
		}

		if (_objectGroup->GetName() == "apple")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				EatApple* _apple = new EatApple( _object->GetX() , 688 - _object->GetY() - _object->GetHeight());

				ListEatApple.push_back(_apple);
				_QuadTree->InsertStaticObject(_apple);
			}
		}


		if (_objectGroup->GetName() == "heart")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				EatHeart* _heart = new EatHeart(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());

				ListEatHeart.push_back(_heart);
				_QuadTree->InsertStaticObject(_heart);
			}
		}


		if (_objectGroup->GetName() == "coin")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);
				EatCoin* _coin = new EatCoin(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());
				ListEatCoin.push_back(_coin);
				_QuadTree->InsertStaticObject(_coin);
			}
		}

		if (_objectGroup->GetName() == "camel")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				Camel* _camel = new Camel(_object->GetX(), 688 - _object->GetY()-_object->GetHeight());

				ListCamel.push_back(_camel);
				_QuadTree->InsertStaticObject(_camel);
			}
		}

		if (_objectGroup->GetName() == "restartpoint")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				RestartPoint* _restart = new RestartPoint(_object->GetX(), 688 - _object->GetY() - _object->GetHeight());

				ListRestartPoint.push_back(_restart);
				_QuadTree->InsertStaticObject(_restart);
			}
		}

		if (_objectGroup->GetName() == "boom")
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
			GetList.push_back(ListGuardShort[i]);
		}
	}

	for (size_t i = 0; i < ListGuardLu.size(); i++)
	{
		if (isContain(ListGuardLu[i], *rect))
		{
			GetList.push_back(ListGuardLu[i]);
		}
	}

	for (size_t i = 0; i < ListGuardThin.size(); i++)
	{
		if (isContain(ListGuardThin[i], *rect))
		{

			GetList.push_back(ListGuardThin[i]);
		}
	}

	for (size_t i = 0; i < ListGuardFat.size(); i++)
	{
		if (isContain(ListGuardFat[i], *rect))
		{

			GetList.push_back(ListGuardFat[i]);
		}
	}

	for (size_t i = 0; i < ListGuardThrowJar.size(); i++)
	{
		if (isContain(ListGuardThrowJar[i], *rect))
		{

			GetList.push_back(ListGuardThrowJar[i]);
		}
	}

	for (size_t i = 0; i < ListKnifeThrower.size(); i++)
	{
		if (isContain(ListKnifeThrower[i], *rect))
		{

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
			GetList.push_back(ListEatApple[i]);
		}
	}

	for (size_t i = 0; i < ListEatCoin.size(); i++)
	{
		if (isContain(ListEatCoin[i], *rect))
		{
			GetList.push_back(ListEatCoin[i]);
		}
	}

	for (size_t i = 0; i < ListBoom.size(); i++)
	{
		if (isContain(ListBoom[i], *rect))
		{

			GetList.push_back(ListBoom[i]);
		}
	}

	for (size_t i = 0; i < ListEatHeart.size(); i++)
	{
		if (isContain(ListEatHeart[i], *rect))
		{

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
	for (size_t i = 0; i < listApple.size(); i++)
	{
		RECT apple = listApple[i]->getBounding();
		RECT temp = *rect;
		temp.top = apple.bottom;

		if (!isContain(listApple[i], temp))
		{
			listApple[i]->Release();
			delete listApple[i];
			listApple.erase(listApple.begin() + i);
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


struct MaxMin
{
	MaxMin(float max, float min)
	{
		_min = min*1.6f;
		_max = max*1.6f;
	}
	float _max;
	float _min;
};