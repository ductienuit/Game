#include "Apple.h"

Apple::Apple(int posX, int posY) :BaseObject(eID::APPLE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::APPLE);
	this->setStatus(NORMAL);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	setScale(SCALEAPPLE2);

	Vector2 newPosition = ViewPort::getInstance()->getPositionWorld();
	_countApple = new Alphabet(newPosition.x + WINDOWS_WIDTH - 35, newPosition.y - WINDOWS_HEIGHT + 33);
	_countApple->setString("15",true);
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

    //Cập nhật lại số táo
	int apple = InforAladdin::getInstance()->getApple();
	std::string s = std::to_string(apple);
	_countApple->setString(s, true);


	_countApple->Update(deltatime);
}

void Apple::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[_status]->Draw(spritehandle, viewport);
	_countApple->Draw(spritehandle, viewport);
}

void Apple::Release()
{
	_countApple->Release();
	SAFE_DELETE(_countApple);
	SAFE_DELETE(this->_sprite);
}

void Apple::UpdateStatus()
{
}

Apple::~Apple()
{
}