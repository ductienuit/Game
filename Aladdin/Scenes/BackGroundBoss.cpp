#include "BackGroundBoss.h".


BackGroundBoss::BackGroundBoss() :BaseObject(eID::BACKGROUNDBOSS)
{
}

BackGroundBoss::~BackGroundBoss()
{
}

void BackGroundBoss::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BACKGROUNDBOSS);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALEBOSSFRONT);
	this->setPosition(0, 0);
}

void BackGroundBoss::Update(float deltatime)
{

}

void BackGroundBoss::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void BackGroundBoss::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}

