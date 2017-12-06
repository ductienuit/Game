#include "QuadTree.h"

// Thần phần static phải khởi tạo lại ở file.cpp.
vector<string> QuadTree::ActiveObject;

QuadTree::QuadTree(int id, int level, RECT bound, QuadTree* parent)
{
	this->_id = id;
	this->_level = level;
	this->_bound = bound;
	this->_parent = parent;
	for (int i = 0; i < 4; i++)
	{
		_childs[i] = NULL;
	}
}

void QuadTree::insertObject(BaseObject* baseobject)
{
	//this->_listOject.push_back(baseobject);
}

void QuadTree::insertObject(string objectname)
{
	this->_listObject.push_back(objectname);
}

RECT QuadTree::getBound()
{
	return _bound;
}
INT64 QuadTree::getId()
{
	return _id;
}
int QuadTree::getLevel()
{
	return _level;
}
QuadTree* QuadTree::getParent()
{
	return _parent;
}
void QuadTree::setParent(QuadTree* parent)
{
	this->_parent = parent;
}
vector<string> QuadTree::getAllObject()
{
	return	_listObject;
}

bool QuadTree::isLeaf()
{
	if (this->_childs[0] == NULL)
		return true;
	return false;
}

// Sử dụng hàm này sẽ gây delay lớn, vì biến cục bộ vector<string> rs khi return được huỷ/cấp phát/copy nhiều lần.
// KHÔNG DÙNG HÀM NÀY.
vector<string> QuadTree::getlistObject(RECT bound)
{
	// Muốn demo thì xoá exception.
	throw new exception("Không dùng hàm này. Chỉ dùng để minh hoạ");
	vector<string> rs;
	if (isContains(this->_bound, bound) || isIntersectd(this->_bound, bound) || isContains(bound, this->_bound))
	{
		if (this->isLeaf() == true)
		{

			// Cơ bản là add hết list vào list kết quả.
			// Nhưng mỗi node trong quadtree có thể chứa các đối tương của node khác.
			// Vậy ta cần loại bỏ các object này.
			//
			//rs.insert(rs.end(), this->_listOject.begin(), this->_listOject.end());

			for (string obj : _listObject)
			{
				auto it = std::find(rs.begin(), rs.end(), obj);

				// it != rs.end() tức là không tìm thấy it trong rs, tức là không có phần tử nào trùng.
				// it._Ptr == nullptr tức là rs không có phần tử nào. (rs.size() = 0)
				if (it == rs.end() || it._Ptr == nullptr)
				{
					rs.push_back(obj);
				}
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				vector<string> temp = _childs[i]->getlistObject(bound);
				for (string obj : temp)
				{
					std::vector<string>::iterator it = std::find(rs.begin(), rs.end(), obj);
					if (it == rs.end() || it._Ptr == nullptr)
					{
						rs.push_back(obj);
					}
				}
				//rs.insert(rs.end(), temp.begin(), temp.end());
			}
		}
	}
	return rs;
}


void QuadTree::fetchActiveObject(RECT bound)
{
	if (isContains(this->_bound, bound) || isIntersectd(this->_bound, bound) || isContains(bound, this->_bound))
	{
		if (this->isLeaf() == true)
		{
			for (string obj : _listObject)
			{
				auto it = std::find(ActiveObject.begin(), ActiveObject.end(), obj);
				if (it == ActiveObject.end() || it._Ptr == nullptr)
				{
					ActiveObject.push_back(obj);
				}
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				_childs[i]->fetchActiveObject(bound);
			}
		}
	}
}

vector<string> QuadTree::GetActiveObject(RECT bound, bool botleft)
{
	if (botleft)
	{
		// đổi từ bot-left sang top-left
		bound.bottom = WINDOWS_HEIGHT - bound.bottom;
		bound.top = WINDOWS_HEIGHT - bound.top;
	}

	QuadTree::ActiveObject.clear();
	this->fetchActiveObject(bound);
	return QuadTree::ActiveObject;
}


QuadTree* QuadTree::loadQuadTree(const string path)
{
#pragma region
	QuadTree* node = nullptr;
	pugi::xml_document doc;

	// Mở file và đọc
	xml_parse_result result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return nullptr;
	}
#pragma endregion
	pugi::xml_node rootxml = doc.first_child();
	node = initNode(rootxml);
	loadChild(rootxml, node);
	return node;
}

QuadTree* QuadTree::initNode(xml_node& node)
{
	RECT bound;
	int id = node.attribute("Id").as_int();
	int level = node.attribute("Level").as_int();
	bound.top = node.attribute("Y").as_int();
	bound.left = node.attribute("X").as_int();
	bound.right = bound.left + node.attribute("Width").as_int();
	bound.bottom = bound.top + node.attribute("Height").as_int();
	QuadTree* qnode = new QuadTree(id, level, bound, NULL);
	return qnode;
}
void QuadTree::loadChild(pugi::xml_node& node, QuadTree* parent)
{
	QuadTree* child[4] = { NULL };
	auto childnodes = node.children();
	string nodename;
	int childindex = 0;
	for each (xml_node childnode in childnodes)
	{

		nodename = childnode.name();
		if (nodename == "Objects")
		{
			string text = childnode.text().as_string();
			auto objectnames = splitString(text, ' ');
			for each (string name in objectnames)
			{
				//auto obj = listobject[name];
				//if (obj == NULL)
				//	continue;
				//parent->insertObject(obj);
				parent->insertObject(name);
			}
		}
		else if (nodename == "QuadTree")
		{
			QuadTree* qnode = initNode(childnode);
			qnode->setParent(parent);
			loadChild(childnode, qnode);
			child[childindex] = qnode;
			childindex++;
		}
	}
	parent->setChilds(child);
}

QuadTree** QuadTree::getChilds()
{
	return _childs;
}

void QuadTree::setChilds(QuadTree* nodes[4])
{
	for (int i = 0; i < 4; i++)
	{
		this->_childs[i] = nodes[i];
	}
}
QuadTree::~QuadTree()
{
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(_childs[i]);
	}
}
