#include "ReadMapEditor.h"



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
	for (size_t i = 0; i < maps->GetNumObjectGroups(); i++)
	{
		 const Tmx::ObjectGroup *_objectGroup = maps->GetObjectGroup(i);
		
		 for(size_t j=0;j<_objectGroup->GetNumObjects();j++)
		 {
			 Tmx::Object* _object = _objectGroup->GetObjects().at(j);

			 if (_object->GetName() == "guardshort")
			 {
				GuardShort* _guardshort = new GuardShort(NORMAL, _object->GetX()+_object->GetWidth()/2, 688 - _object->GetY() - _object->GetHeight() / 2,NONE);
				ListGuardShort.push_back(_guardshort);
				_QuadTree->InsertStaticObject(_guardshort);
			 }

			 if (_object->GetName() == "guardthin")
			 {
				 GuardThin* _guardthin = new GuardThin(NORMAL, _object->GetX() + _object->GetWidth() / 2, 688 - _object->GetY() - _object->GetHeight() / 2, NONE);
				 ListGuardThin.push_back(_guardthin);
				 _QuadTree->InsertStaticObject(_guardthin);
			 }

			 if (_object->GetName() == "guardlu")
			 {
				 GuardLu* _guardlu = new GuardLu(NORMAL, _object->GetX() + _object->GetWidth() / 2, 688 - _object->GetY() - _object->GetHeight() / 2, NONE);
				 ListGuardLu.push_back(_guardlu);
				 _QuadTree->InsertStaticObject(_guardlu);
			 }

		 }
	}
}

ReadMapEditor::~ReadMapEditor()
{
}

vector<BaseObject*> ReadMapEditor::GetList(RECT * rect)
{
	//kiem tra listguardshort
	for (size_t i = 0; i < ListGuardShort.size(); i++)
	{
		//kiem tra co trong rect camera khong
		if (ListGuardShort[i]->getPositionX() > rect->left&&ListGuardShort[i]->getPositionX() < rect->right
			&&ListGuardShort[i]->getPositionY() < rect->top&&ListGuardShort[i]->getPositionY() > rect->bottom)
		{
			//kiem tra da ve chua
		/*	if (ListGuardShort[i]->getStatus() != eStatus::DESTROY)
			{
				delete ListGuardShort[i];
				ListGuardShort.erase(ListGuardShort.begin() + i);
				i--;
				continue;
			}*/

			GetList(rect).push_back(ListGuardShort[i]);
		}
	}

	for (size_t i = 0; i < ListGuardLu.size(); i++)
	{
		if (ListGuardLu[i]->getPositionX() > rect->left&&ListGuardLu[i]->getPositionX() < rect->right
			&&ListGuardLu[i]->getPositionY() < rect->top&&ListGuardLu[i]->getPositionY() > rect->bottom)
		{
			//kiem tra list guardLu da co trong rect
		/*	if (ListGuardLu[i]->getStatus() != eStatus::DESTROY)
			{
				delete ListGuardLu[i];
				ListGuardLu.erase(ListGuardLu.begin() + i);
				i--;
				continue;
			}*/
			GetList(rect).push_back(ListGuardLu[i]);
		}
	}

	for (size_t i = 0; i < ListGuardThin.size(); i++)
	{
		if (ListGuardThin[i]->getPositionX() > rect->left&&ListGuardThin[i]->getPositionX() < rect->right
			&&ListGuardThin[i]->getPositionY() < rect->top&&ListGuardThin[i]->getPositionY() > rect->bottom)
		{
		/*	if (ListGuardThin[i]->getStatus() != eStatus::DESTROY)
			{
				delete ListGuardThin[i];
				ListGuardThin.erase(ListGuardThin.begin() + i);
				i--;
				continue;
			}*/
			GetList(rect).push_back(ListGuardThin[i]);
		}
	}

	return vector<BaseObject*>();
}

void ReadMapEditor::UpDate(float detatime)
{

}

