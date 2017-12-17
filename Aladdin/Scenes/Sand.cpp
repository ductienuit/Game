#include "Sand.h"


Sand::Sand() :BaseObject(eID::SAND)
{
	InIt();
}

Sand::~Sand()
{
}

void Sand::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::SAND);
	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::SAND, "sand_0", "sand_1", NULL);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALEMAP);
	this->setPosition(0, 0);
}

void Sand::Update(float deltatime)
{
}

void Sand::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void Sand::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}
