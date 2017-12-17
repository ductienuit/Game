#include "Sky.h"


Sky::Sky() :BaseObject(eID::SKY)
{
}

Sky::~Sky()
{
}

void Sky::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::SKY);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALEMAP);
	this->setPosition(0, 0);
}

void Sky::Update(float deltatime)
{
}

void Sky::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void Sky::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}
