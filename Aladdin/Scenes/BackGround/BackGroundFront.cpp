#include "BackGroundFront.h"



BackGroundFront::BackGroundFront()
{
}


BackGroundFront::~BackGroundFront()
{
}

void BackGroundFront::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BACKGROUNDFRONT);
	this->setOrigin(Vector2(0, 0));//Set top left dưới 0 0
	this->setPosition(0, 0);
}

void BackGroundFront::Update(float deltatime)
{
}

void BackGroundFront::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void BackGroundFront::Release()
{
}
