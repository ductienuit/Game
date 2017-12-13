#ifndef __QTREE_H__
#define __QTREE_H__

#include "define.h"
#include "../Objects/BaseObject.h"
#include"../pugixml-1.7/src/pugixml.hpp"
using namespace pugi;

class QuadTree
{
public:
	QuadTree(RECT bound, int level = 1);
	~QuadTree();
	void Clear();
	void InsertStaticObject(BaseObject *gameObject);
	static void InsertDynamicObject(BaseObject *gameObject);
	void Retrieve(std::vector<BaseObject*> &gameObjectsOut, BaseObject *gameObject);

protected:
	static int MAX_OBJECT_IN_REGION;
	static int MAX_LEVEL;

	RECT		mBound;
	int			mLevel;
	QuadTree **	mNodes;
	std::vector<BaseObject*>		mListStaticGameObject;
	static std::vector<BaseObject*> mListDynamicGameObject;

	bool IsContain(BaseObject *gameObject);
	void Split();
};



#endif // !__QTREE_H__

