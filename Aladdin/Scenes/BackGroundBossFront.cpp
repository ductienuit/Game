#include "BackGroundBossFront.h".


BackGroundBossFront::BackGroundBossFront() :BaseObject(eID::BACKGROUNDBOSS)
{
}

BackGroundBossFront::~BackGroundBossFront()
{
}

void BackGroundBossFront::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BACKGROUNDBOSS);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALEBOSSFRONT);
	this->setPosition(0, 0);
}

void BackGroundBossFront::Update(float deltatime)
{

}

void BackGroundBossFront::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void BackGroundBossFront::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}

