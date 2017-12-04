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
	this->setPosition(0, -500);
}

void BackGround::Update(float deltatime)
{
}

void BackGround::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle);
}

void BackGround::Release()
{
}
