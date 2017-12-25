#include "BackgroundBossBack.h"

BackGroundBossBack::BackGroundBossBack(int posX, int posY) :BaseObject(eID::BACKGROUNDBOSSBACK)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BACKGROUNDBOSSBACK);
	this->setStatus(NORMAL);
	this->setPosition(posX, posY, 1.0f);
	this->setOrigin(ORIGINZERO);
	setScale(SCALEONE);
	//SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli.wav", 1);
}

void BackGroundBossBack::InIt()
{	
}

void BackGroundBossBack::Update(float deltatime)
{
	Vector2 newPosition = ViewPort::getInstance()->getPositionWorld();
	setPosition(newPosition.x , newPosition.y - WINDOWS_HEIGHT);

}

void BackGroundBossBack::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_sprite->Render(spritehandle, viewport);
}

void BackGroundBossBack::Release()
{
	SAFE_DELETE(this->_sprite);
}


BackGroundBossBack::~BackGroundBossBack()
{
}