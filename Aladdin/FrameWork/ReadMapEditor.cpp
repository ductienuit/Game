#include "ReadMapEditor.h"
extern 	vector<BaseObject*> Stair[2];


ReadMapEditor::ReadMapEditor(const char *filepath, QuadTree *& _quadTree)
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
		if (_objectGroup->GetName() == "guardshort")
		{

			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardShort* _guardshort = new GuardShort(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), NONE, 1000, 1000);

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


				GuardFat* _guardFat = new GuardFat(FREE, _object->GetX() , 688 - _object->GetY() - _object->GetHeight(), NONE);

				ListGuardFat.push_back(_guardFat);
				_QuadTree->InsertStaticObject(_guardFat);
			}
		}

		if (_objectGroup->GetName() == "guardthrowjar")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);


				GuardThrowJar* _guardThrowJar = new GuardThrowJar(FREE, _object->GetX() + _object->GetWidth() / 2, 688 - _object->GetY() - _object->GetHeight() / 2);

				ListGuardThrowJar.push_back(_guardThrowJar);
				_QuadTree->InsertStaticObject(_guardThrowJar);
			}
		}

		if (_objectGroup->GetName() == "knifethrower")
		{
			for (size_t j = 0; j < _objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object* _object = _objectGroup->GetObjects().at(j);

				KnifeThrower* _knifeThrower = new KnifeThrower(MOVING_LEFT, _object->GetX(), 688 - _object->GetY() - _object->GetHeight(), NONE);

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

				Land* _spring = new Land(_object->GetX(), 688 - _object->GetY(), _object->GetWidth(), _object->GetHeight(), NONE, SPRING);

				ListLand.push_back(_spring);
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
	}
}


ReadMapEditor::~ReadMapEditor()
{
}

void ReadMapEditor::ListObject(RECT * rect)
{
	GetList.clear();
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

}
//đệ quy sai
//vector<BaseObject*> ReadMapEditor::GetList(RECT * rect)
//{
//	kiem tra listguardshort
//	size_t x = ListGuardShort.size();
//	for (size_t i = 0; i < ListGuardShort.size(); i++)
//	{
//		kiem tra co trong rect camera khong
//		bool check1 = ListGuardShort[i]->getPositionX() > rect->left;
//		bool check2 = ListGuardShort[i]->getPositionX() < rect->right;
//		bool check3 = ListGuardShort[i]->getPositionY() < rect->top;
//		bool check4 = ListGuardShort[i]->getPositionY() > rect->bottom;
//
//		/*if (ListGuardShort[i]->getPositionX() > rect->left&&ListGuardShort[i]->getPositionX() < rect->right
//			&&ListGuardShort[i]->getPositionY() < rect->top&&ListGuardShort[i]->getPositionY() > rect->bottom)
//		{
//			GetList(rect).push_back(ListGuardShort[i]);
//		}*/
//
//		if (check1 && check2	&& check3 && check4)
//		{
//		GetList(rect).push_back(ListGuardShort[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListGuardLu.size(); i++)
//	{
//		if (ListGuardLu[i]->getPositionX() > rect->left&&ListGuardLu[i]->getPositionX() < rect->right
//			&&ListGuardLu[i]->getPositionY() < rect->top&&ListGuardLu[i]->getPositionY() > rect->bottom)
//		{
//			GetList(rect).push_back(ListGuardLu[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListGuardThin.size(); i++)
//	{
//		if (ListGuardThin[i]->getPositionX() > rect->left&&ListGuardThin[i]->getPositionX() < rect->right
//			&&ListGuardThin[i]->getPositionY() < rect->top&&ListGuardThin[i]->getPositionY() > rect->bottom)
//		{
//
//			GetList(rect).push_back(ListGuardThin[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListGuardFat.size(); i++)
//	{
//		if (ListGuardFat[i]->getPositionX() > rect->left&&ListGuardFat[i]->getPositionX() < rect->right
//			&&ListGuardFat[i]->getPositionY() < rect->top&&ListGuardFat[i]->getPositionY() > rect->bottom)
//		{
//
//			GetList(rect).push_back(ListGuardFat[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListGuardThrowJar.size(); i++)
//	{
//		if (ListGuardThrowJar[i]->getPositionX() > rect->left&&ListGuardThrowJar[i]->getPositionX() < rect->right
//			&&ListGuardThrowJar[i]->getPositionY() < rect->top&&ListGuardThrowJar[i]->getPositionY() > rect->bottom)
//		{
//
//			GetList(rect).push_back(ListGuardThrowJar[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListKnifeThrower.size(); i++)
//	{
//		if (ListKnifeThrower[i]->getPositionX() > rect->left&&ListKnifeThrower[i]->getPositionX() < rect->right
//			&&ListKnifeThrower[i]->getPositionY() < rect->top&&ListKnifeThrower[i]->getPositionY() > rect->bottom)
//		{
//
//			GetList(rect).push_back(ListKnifeThrower[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListFire.size(); i++)
//	{
//		if (ListFire[i]->getPositionX() > rect->left&&ListFire[i]->getPositionX() < rect->right
//			&&ListFire[i]->getPositionY() < rect->top&&ListFire[i]->getPositionY() > rect->bottom)
//		{
//
//			GetList(rect).push_back(ListFire[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListLand.size(); i++)
//	{
//		if (ListLand[i]->getPositionX() > rect->left&&ListLand[i]->getPositionX() < rect->right
//			&&ListLand[i]->getPositionY() < rect->top&&ListLand[i]->getPositionY() > rect->bottom)
//		{
//
//			GetList(rect).push_back(ListLand[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListEatApple.size(); i++)
//	{
//		if (ListEatApple[i]->getPositionX() > rect->left&&ListEatApple[i]->getPositionX() < rect->right
//			&&ListEatApple[i]->getPositionY() < rect->top&&ListEatApple[i]->getPositionY() > rect->bottom)
//		{
//
//			GetList(rect).push_back(ListEatApple[i]);
//		}
//	}
//
//	for (size_t i = 0; i < ListCamel.size(); i++)
//	{
//		if (ListCamel[i]->getPositionX() > rect->left&&ListCamel[i]->getPositionX() < rect->right
//			&&ListCamel[i]->getPositionY() < rect->top&&ListCamel[i]->getPositionY() > rect->bottom)
//		{
//
//			GetList(rect).push_back(ListCamel[i]);
//		}
//	}
//
//	return GetList(rect);
//}

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


