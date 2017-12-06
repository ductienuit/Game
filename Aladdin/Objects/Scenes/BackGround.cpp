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
	this->setOrigin(Vector2(0,0));//Set top left dưới 0 0
	this->setPosition(0, 0);
}

void BackGround::Update(float deltatime)
{

}

void BackGround::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle,viewport);
}

void BackGround::Release()
{
}


