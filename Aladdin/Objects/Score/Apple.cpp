#include "Apple.h"

Apple::Apple(int posX, int posY) :BaseObject(eID::APPLE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::APPLE);
	this->setStatus(NORMAL);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	setScale(SCALEAPPLE2);
	InIt();
}

void Apple::InIt()
{
	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::APPLE, "eat_apple_0", "eat_apple_0",NULL);
}

void Apple::Update(float deltatime)
{
	Vector2 newPosition = ViewPort::getInstance()->getPositionWorld();
	setPosition(newPosition.x + WINDOWS_WIDTH - 70, newPosition.y - WINDOWS_HEIGHT + 30);

	_animations[_status]->Update(deltatime);
}

void Apple::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[_status]->Draw(spritehandle, viewport);
}

void Apple::Release()
{
	SAFE_DELETE(this->_sprite);
}

void Apple::UpdateStatus()
{
}

Apple::~Apple()
{
}