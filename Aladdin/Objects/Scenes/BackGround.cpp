#include "BackGround.h"


BackGround::BackGround():BaseObject(eID::BACKGROUND)
{
}

BackGround::~BackGround()
{
}

void BackGround::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BACKGROUND);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ALADDIN, "standing_0"));
	this->setPosition(0, 0, 0);
}

void BackGround::Update(float deltatime)
{
}

void BackGround::Draw(LPD3DXSPRITE spriteHandle, Viewport *viewport)
{
	_sprite->Render(spriteHandle);
}

void BackGround::Release()
{
}
