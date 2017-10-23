#include "SpriteManager.h"
USEGAME_FRAMEWORK

SpriteManager* SpriteManager::_instance = nullptr;
SpriteManager::SpriteManager()
{
}


void SpriteManager::ReleaseTexture(eID id)
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
}

Sprite * SpriteManager::getSprite(eID id)
{
	return nullptr;
}

RECT SpriteManager::getSourceRect(eID id, string name)
{
	return RECT();
}

void SpriteManager::LoadSpriteInfo(eID id, const char * fileInfoPath)
{
}

void SpriteManager::ReleaseSprite(eID id)
{
}
