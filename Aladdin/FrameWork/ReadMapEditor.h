#ifndef __READMAPEDITOR_H__
#define __READMAPEDITOR_H__

#include"Resources\MapReader\Tmx.h"
#include"Objects\BaseObject.h"
#include"FrameWork\QuadTree.h"
#include"Objects\Enemies\GuardLu.h"
#include"Objects\Enemies\GuardShort.h"
#include"Objects\Enemies\GuardThin.h"

class ReadMapEditor
{
public:
	ReadMapEditor(const char* filepath,QuadTree* &_quadTree);
	~ReadMapEditor();
	Tmx::Map* maps;
	vector <GuardLu*> ListGuardLu;
	vector <GuardThin*> ListGuardThin;
	vector <GuardShort*> ListGuardShort;
	QuadTree* _QuadTree;

	vector <BaseObject*> GetList(RECT* rect);
	void UpDate(float detatime);
};
#endif __READMAPEDITOR_H__
