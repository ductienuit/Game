#ifndef __QTREE_H__
#define __QTREE_H__

#include "define.h"
#include "../Objects/BaseObject.h"
#include"../pugixml-1.7/src/pugixml.hpp"
using namespace pugi;
class QuadTree
{
private:
	RECT _bound;
	INT64 _id;
	int _level;
	QuadTree* _parent;
	QuadTree* _childs[4];

	//vector<BaseObject*>  _listOject;
	vector<string> _listObject;
public:
	QuadTree(int id, int level, RECT bound, QuadTree* parent);
	void insertObject(BaseObject* baseobject);
	void insertObject(string name);
	RECT getBound();
	INT64 getId();
	int getLevel();
	QuadTree* getParent();
	void setParent(QuadTree* parent);
	QuadTree** getChilds();
	void setChilds(QuadTree* nodes[4]);
	bool isLeaf();


	vector<string> getAllObject();

	// Hàm này gây delay. Không dùng hàm này.
	vector<string> getlistObject(RECT bound);



	static void loadChild(xml_node& node, QuadTree* parent);
	static QuadTree* loadQuadTree(const string path);
	static QuadTree* initNode(xml_node& node);

	/*
	L?y object mà bound ?è lên
	@bound: hcn
	@botleft: b?ng true n?u hcn tính theo bot-left, false là top-left
	thêm ?? kh?i m?t công chuy?n bên ngoài
	*/
	vector<string> GetActiveObject(RECT bound, bool botleft = false);
	void fetchActiveObject(RECT bound);
	static vector<string> ActiveObject;
	~QuadTree();
};



#endif // !__QTREE_H__

