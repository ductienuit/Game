#include "Life.h"

Life::Life(int posX, int posY) :BaseObject(eID::LIFE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::LIFE);
	this->setStatus(NORMAL);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	setScale(SCALELIFE);
	InIt();
}

void Life::InIt()
{
	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::LIFE, "life_0", 3);
}

void Life::Update(float deltatime)
{
	Vector2 newPosition = ViewPort::getInstance()->getPositionWorld();
	setPosition(newPosition.x+20, newPosition.y - WINDOWS_HEIGHT+50);

	_animations[_status]->Update(deltatime);

}

void Life::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[_status]->Draw(spritehandle, viewport);
}

void Life::Release()
{
	SAFE_DELETE(this->_sprite);
}

void Life::UpdateStatus()
{
}

Life::~Life()
{
}