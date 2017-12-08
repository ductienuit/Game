#include "SpriteManager.h"
USEGAME_FRAMEWORK

SpriteManager* SpriteManager::_instance = nullptr;
SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
	for (auto spr = _listSprite.begin(); spr != _listSprite.end(); ++spr)
	{
		spr->second->Release();		// release image
		delete spr->second;			// delete sprite
	}
	if (_listSprite.empty() == false)
		_listSprite.clear();		// remove all from MAP
}

SpriteManager * SpriteManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteManager();
	return _instance;
}

void SpriteManager::Release()
{
	delete _instance;
	_instance = nullptr;
}

void SpriteManager::LoadResource(LPD3DXSPRITE spriteHandle)
{
	/* if you have any image, load them with this format */
	// [psedue code]
	// sp = new SPRITE(...)
	// this->_listSprite.insert(pair<eID, Sprite*>(eID::ENUMOBJECT, sp));

	//Sprite* sp = new Sprite(spriteHandle, L"Flower.png", 4, 4);
	//this->_listSprite.insert(pair<eID, Sprite*>(eID::FLOWER, sp));

	Sprite* sp = NULL;
	sp = new Sprite(spriteHandle, "Resources//Images//AladdinAnimation.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ALADDIN, sp));
	this->LoadSpriteInfo(eID::ALADDIN, "Resources//Images//AladdinAnimation.txt");


	sp = new Sprite(spriteHandle, "Resources//Images//Guards.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::GUARDTHIN, sp));
	this->LoadSpriteInfo(eID::GUARDTHIN, "Resources//Images//GuardsAll.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Guards.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::GUARDSHORT, sp));
	this->LoadSpriteInfo(eID::GUARDSHORT, "Resources//Images//GuardsAll.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//CivilianEnemies.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::GUARDLU, sp));
	this->LoadSpriteInfo(eID::GUARDLU, "Resources//Images//CivilianEnemies.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Guards.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::KNIFE, sp));
	this->LoadSpriteInfo(eID::KNIFE, "Resources//Images//GuardsAll.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//background.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BACKGROUND, sp));
	this->LoadSpriteInfo(eID::BACKGROUND, "Resources//Images//background.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//backgroundfront.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BACKGROUNDFRONT, sp));
	this->LoadSpriteInfo(eID::BACKGROUNDFRONT, "Resources//Images//backgroundfront.txt");

	//red-line

	sp = new Sprite(spriteHandle, "Resources//Images//red-line.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::LAND, sp));
	this->LoadSpriteInfo(eID::BACKGROUND, "Resources//Images//red-line.txt");


	sp = new Sprite(spriteHandle, "Resources//Images//CivilianEnemies.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::GUARDLU, sp));
	this->LoadSpriteInfo(eID::GUARDLU, "Resources//Images//CivilianEnemies.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//CivilianEnemies.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::KNIFETHROWER, sp));
	this->LoadSpriteInfo(eID::KNIFETHROWER, "Resources//Images//CivilianEnemies.txt");
	
	// code thêm trong file SpriteManager.cpp
	sp = new Sprite(spriteHandle, "Resources//Images//CivilianEnemies.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::JAR, sp));
	this->LoadSpriteInfo(eID::JAR, "Resources//Images//CivilianEnemies.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//CivilianEnemies.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::THROWJAR, sp));
	this->LoadSpriteInfo(eID::THROWJAR, "Resources//Images//CivilianEnemies.txt");
}

Sprite * SpriteManager::getSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	return it;			// get the version of Sprite
}


RECT SpriteManager::getSourceRect(eID id, string name)
{
	return _sourceRectList[id][name];
}

void SpriteManager::LoadSpriteInfo(eID id, const char * fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			RECT rect;
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d", &name, &rect.left, &rect.top, &rect.right, &rect.bottom);

			_sourceRectList[id][name] = rect;
		}
	}

	fclose(file);
}

void SpriteManager::ReleaseSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	delete it;							// delete the sprite only, dont relase image
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}

void SpriteManager::ReleaseTexture(eID id)
{
	Sprite *spr = this->_listSprite.find(id)->second;
	spr->Release();						// release image
	delete spr;
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
