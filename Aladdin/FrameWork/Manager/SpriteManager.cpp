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

	sp = new Sprite(spriteHandle, "Resources//Images//Apple.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::APPLETHROW, sp));
	this->LoadSpriteInfo(eID::APPLETHROW, "Resources//Images//Apple.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//background.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BACKGROUND, sp));
	this->LoadSpriteInfo(eID::BACKGROUND, "Resources//Images//background.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//backgroundfront.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BACKGROUNDFRONT, sp));
	this->LoadSpriteInfo(eID::BACKGROUNDFRONT, "Resources//Images//backgroundfront.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//MenuBackGround.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::MENUBACKGROUND, sp));
	this->LoadSpriteInfo(eID::MENUBACKGROUND, "Resources//Images//menubackground.txt");

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

	sp = new Sprite(spriteHandle, "Resources//Images//AladdinAnimation.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::LIFE, sp));
	this->LoadSpriteInfo(eID::LIFE, "Resources//Images//life.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//AladdinAnimation.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::COIN, sp));
	this->LoadSpriteInfo(eID::COIN, "Resources//Images//Coin.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Boom.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BOOM, sp));
	this->LoadSpriteInfo(eID::BOOM, "Resources//Images//Boom.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Items.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::APPLE, sp));
	this->LoadSpriteInfo(eID::APPLE, "Resources//Images//Items.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//alphabet.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::LETTER, sp));
	this->LoadSpriteInfo(eID::LETTER, "Resources//Images//alphabet.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//alphabet.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ALPHABET, sp));
	this->LoadSpriteInfo(eID::ALPHABET, "Resources//Images//alphabet.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Items.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::CHOOSE, sp));
	this->LoadSpriteInfo(eID::CHOOSE, "Resources//Images//Items.txt");


	sp = new Sprite(spriteHandle, "Resources//Images//Boss//pillars.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BACKGROUNDBOSSBACK, sp));
	this->LoadSpriteInfo(eID::BACKGROUNDBOSSBACK, "Resources//Images//Boss//pillars.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Boss//palace_back.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BACKGROUNDBOSSFRONT, sp));
	this->LoadSpriteInfo(eID::BACKGROUNDBOSSFRONT, "Resources//Images//Boss//palace_back.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Boss//Boss.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BOSS, sp));
	this->LoadSpriteInfo(eID::BOSS, "Resources//Images//Boss//Boss.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Boss//enemy_explosion.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::STRIP_BOSS, sp));
	this->LoadSpriteInfo(eID::STRIP_BOSS, "Resources//Images//Boss//bossstrip.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Boss//spell_strip7_15_11.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::STRIP_ALADDIN, sp));
	this->LoadSpriteInfo(eID::STRIP_ALADDIN, "Resources//Images//Boss//spell_strip7_15_11.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Boss//spell_strip7_15_11.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::STAR, sp));
	this->LoadSpriteInfo(eID::STAR, "Resources//Images//Boss//spell_strip7_15_11.txt");

	sp = new Sprite(spriteHandle, "Resources//Images//Boss//movingflame_strip8.png");
	this->_listSprite.insert(pair<eID, Sprite*>(eID::FIRE_BOSS, sp));
	this->LoadSpriteInfo(eID::FIRE_BOSS, "Resources//Images//Boss//movingflame_strip8.txt");
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
