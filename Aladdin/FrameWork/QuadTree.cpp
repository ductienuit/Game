#include "QuadTree.h"

int QuadTree::MAX_LEVEL = 5;
int QuadTree::MAX_OBJECT_IN_REGION = 5;
std::vector<BaseObject*> QuadTree::mListDynamicGameObject;

QuadTree::QuadTree(RECT bound, int level)
{
	this->mBound = bound;
	this->mLevel = level;
}

QuadTree::~QuadTree()
{
	this->Clear();
}

bool QuadTree::IsContain(BaseObject * gameObject)
{
	RECT bound = gameObject->getBounding();
	return !(bound.right < mBound.left ||
		bound.bottom < mBound.top ||
		bound.left > mBound.right ||
		bound.top > mBound.bottom);
}

void QuadTree::InsertStaticObject(BaseObject * gameObject)
{
	//Insert entity into corresponding nodes
	if (mNodes)
	{
		if (mNodes[0]->IsContain(gameObject))
			mNodes[0]->InsertStaticObject(gameObject);
		if (mNodes[1]->IsContain(gameObject))
			mNodes[1]->InsertStaticObject(gameObject);
		if (mNodes[2]->IsContain(gameObject))
			mNodes[2]->InsertStaticObject(gameObject);
		if (mNodes[3]->IsContain(gameObject))
			mNodes[3]->InsertStaticObject(gameObject);

		return; // Return here to ignore rest.
	}

	//Insert entity into current quadtree
	if (this->IsContain(gameObject))
		mListStaticGameObject.push_back(gameObject);

	//Split and move all objects in list into it’s corresponding nodes
	if (mListStaticGameObject.size() > MAX_OBJECT_IN_REGION && mLevel < MAX_LEVEL)
	{
		this->Split();

		while (!mListStaticGameObject.empty())
		{
			if (mNodes[0]->IsContain(mListStaticGameObject.back()))
				mNodes[0]->InsertStaticObject(mListStaticGameObject.back());
			if (mNodes[1]->IsContain(mListStaticGameObject.back()))
				mNodes[1]->InsertStaticObject(mListStaticGameObject.back());
			if (mNodes[2]->IsContain(mListStaticGameObject.back()))
				mNodes[2]->InsertStaticObject(mListStaticGameObject.back());
			if (mNodes[3]->IsContain(mListStaticGameObject.back()))
				mNodes[3]->InsertStaticObject(mListStaticGameObject.back());

			mListStaticGameObject.pop_back();
		}
	}
}

void QuadTree::InsertDynamicObject(BaseObject * gameObject)
{
	mListDynamicGameObject.push_back(gameObject);
}

void QuadTree::Retrieve(std::vector<BaseObject*>& return_objects_list, BaseObject * gameObject)
{
	if (mNodes)
	{
		if (mNodes[0]->IsContain(gameObject))
			mNodes[0]->Retrieve(return_objects_list, gameObject);
		if (mNodes[1]->IsContain(gameObject))
			mNodes[1]->Retrieve(return_objects_list, gameObject);
		if (mNodes[2]->IsContain(gameObject))
			mNodes[2]->Retrieve(return_objects_list, gameObject);
		if (mNodes[3]->IsContain(gameObject))
			mNodes[3]->Retrieve(return_objects_list, gameObject);

		//TODO: remove duplicate
		/*std::sort(return_objects_list.begin(), return_objects_list.end());
		auto last = std::unique(return_objects_list.begin(), return_objects_list.end());
		return_objects_list.erase(last, return_objects_list.end());*/

		//return; // Return here to ignore rest.
	}

	//Add all entities in current region into return_objects_list
	if (this->IsContain(gameObject))
	{
		//find static objects
		for (auto i = mListStaticGameObject.begin(); i != mListStaticGameObject.end(); i++)
		{
			if (gameObject != *i)
				return_objects_list.push_back(*i);
		}

		//add moving objects
		for (auto i = mListDynamicGameObject.begin(); i != mListDynamicGameObject.end(); i++)
		{
			if (gameObject != *i)
				return_objects_list.push_back(*i);
		}
	}
}

void QuadTree::Clear()
{
	if (mNodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (mNodes[i])
			{
				mNodes[i]->Clear();
				delete mNodes[i];
				mNodes[i] = NULL;
			}
		}
		delete[] mNodes;
	}

	mListStaticGameObject.clear();
}

void QuadTree::Split()
{
	//split current node into 4 nodes
	mNodes = new QuadTree*[4];

	int width = (mBound.right - mBound.left) / 2;
	int height = (mBound.bottom - mBound.top) / 2;

	RECT childRect;

	//top left
	childRect.left = mBound.left;
	childRect.right = mBound.left + width;
	childRect.top = mBound.top;
	childRect.bottom = mBound.top + height;
	mNodes[0] = new QuadTree(childRect, mLevel + 1);

	//top right
	childRect.right = mBound.right;
	childRect.left = mBound.right - width;
	childRect.top = mBound.top;
	childRect.bottom = mBound.top + height;
	mNodes[1] = new QuadTree(childRect, mLevel + 1);

	//bottom left
	childRect.left = mBound.left;
	childRect.right = mBound.left + width;
	childRect.bottom = mBound.bottom;
	childRect.top = mBound.bottom - height;
	mNodes[2] = new QuadTree(childRect, mLevel + 1);

	//bottom right
	childRect.right = mBound.right;
	childRect.left = mBound.right - width;
	childRect.bottom = mBound.bottom;
	childRect.top = mBound.bottom - height;
	mNodes[3] = new QuadTree(childRect, mLevel + 1);
}



