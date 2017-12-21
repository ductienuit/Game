#include "Coin.h"

Coin::Coin(int posX, int posY) :BaseObject(eID::COIN)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::COIN);
	this->setStatus(NORMAL);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	setScale(SCALECOIN);
	InIt();
}

void Coin::InIt()
{
	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::COIN, "coin_0", 2);
}

void Coin::Update(float deltatime)
{
	Vector2 newPosition = ViewPort::getInstance()->getPositionWorld();
	setPosition(newPosition.x + WINDOWS_WIDTH-150, newPosition.y - WINDOWS_HEIGHT + 30);

	_animations[_status]->Update(deltatime);
}

void Coin::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[_status]->Draw(spritehandle, viewport);
}

void Coin::Release()
{
	SAFE_DELETE(this->_sprite);
}

void Coin::UpdateStatus()
{
}

Coin::~Coin()
{
}