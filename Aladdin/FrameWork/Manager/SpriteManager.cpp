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

	Sprite* sp = NULL;
	sp = new Sprite(spriteHandle, "Resources//Images//AladdinAnimation.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ALADDIN, sp));
	this->LoadSpriteInfo(eID::ALADDIN, "Resources//Images//AladdinAnimation.txt");

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

	sp = new Sprite(spriteHandle, "Resources//Images//AladdinAnimation.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::APPLETHROW, sp));
	this->LoadSpriteInfo(eID::APPLETHROW, "Resources//Images//AladdinAnimation.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//background.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BACKGROUND, sp));
	this->LoadSpriteInfo(eID::BACKGROUND, "Resources//Images//background.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//backgroundfront.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BACKGROUNDFRONT, sp));
	this->LoadSpriteInfo(eID::BACKGROUNDFRONT, "Resources//Images//backgroundfront.txt");


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
	this->_listSprite.insert(pair<eID, Sprite*>(eID::GUARDTHROWJAR, sp));
	this->LoadSpriteInfo(eID::GUARDTHROWJAR, "Resources//Images//CivilianEnemies.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//flame_strip9_15_54.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::FIRE, sp));
	this->LoadSpriteInfo(eID::FIRE, "Resources//Images//flame_strip9_15_54.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//fallingplatform.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::FALLINGPLATFORM, sp));
	this->LoadSpriteInfo(eID::FALLINGPLATFORM, "Resources//Images//fallingplatform.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Guards.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::GUARDFAT, sp));
	this->LoadSpriteInfo(eID::GUARDFAT, "Resources//Images//GuardsAll.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//BulletCamel.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BULLETCAMEL, sp));
	this->LoadSpriteInfo(eID::BULLETCAMEL, "Resources//Images//BulletCamel.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Camel.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::CAMEL, sp));
	this->LoadSpriteInfo(eID::CAMEL, "Resources//Images//Camel.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Items.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::APPLEEAT, sp));
	this->LoadSpriteInfo(eID::APPLEEAT, "Resources//Images//Items.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Items.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::COINEAT, sp));
	this->LoadSpriteInfo(eID::COINEAT, "Resources//Images//Items.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Items.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::RESTARTPOINT, sp));
	this->LoadSpriteInfo(eID::RESTARTPOINT, "Resources//Images//Items.txt");
	

	sp = new Sprite(spriteHandle, "Resources//Images//EatHeart.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::HEARTEAT, sp));
	this->LoadSpriteInfo(eID::HEARTEAT, "Resources//Images//EatHeart.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Spring.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::SPRING, sp));
	this->LoadSpriteInfo(eID::SPRING, "Resources//Images//Spring.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//alluneed.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::HEALTH, sp));
	this->LoadSpriteInfo(eID::HEALTH, "Resources//Images//health.txt");
}

Sprite * SpriteManager::getSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	if (id == ALADDIN)
		return it;
	return new Sprite(*it);				// get the version of Sprite
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
