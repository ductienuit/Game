#include "Health.h"

Health::Health(BaseObject* aladdin, int posX, int posY) :BaseObject(eID::HEALTH)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::HEALTH);
	_aladdin = (Aladdin*)aladdin;
	this->setStatus(NORMAL);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	setScale(SCALEHEALTH);
	InIt();
}

void Health::InIt()
{
	iStatus = InforAladdin::getInstance()->getHealth();

	_animations[120] = new Animation(_sprite, 0.1f);
	_animations[120]->addFrameRect(eID::HEALTH, "health_8_0", 4);

	_animations[110] = new Animation(_sprite, 0.1f);
	_animations[110]->addFrameRect(eID::HEALTH, "health_8_0", 4);

	_animations[100] = new Animation(_sprite, 0.1f);
	_animations[100]->addFrameRect(eID::HEALTH, "health_7_0", 4);

	_animations[90] = new Animation(_sprite, 0.1f);
	_animations[90]->addFrameRect(eID::HEALTH, "health_7_0",4);

	_animations[80] = new Animation(_sprite, 0.1f);
	_animations[80]->addFrameRect(eID::HEALTH, "health_6_0", 4); 

	_animations[70] = new Animation(_sprite, 0.1f);
	_animations[70]->addFrameRect(eID::HEALTH, "health_6_0", 4);

	_animations[60] = new Animation(_sprite, 0.1f);
	_animations[60]->addFrameRect(eID::HEALTH, "health_5_0", 4);

	_animations[50] = new Animation(_sprite, 0.1f);
	_animations[50]->addFrameRect(eID::HEALTH, "health_4_0", 4);

	_animations[40] = new Animation(_sprite, 0.1f);
	_animations[40]->addFrameRect(eID::HEALTH, "health_3_0", 4);

	_animations[30] = new Animation(_sprite, 0.1f);
	_animations[30]->addFrameRect(eID::HEALTH, "health_2_0", 4);

	_animations[20] = new Animation(_sprite, 0.1f);
	_animations[20]->addFrameRect(eID::HEALTH, "health_1_0", 4);

	_animations[10] = new Animation(_sprite, 0.1f);
	_animations[10]->addFrameRect(eID::HEALTH, "health_0_00", "health_0_00",NULL);

	_animations[0] = new Animation(_sprite, 0.1f);
	_animations[0]->addFrameRect(eID::HEALTH, "health_0_00", "health_0_00", NULL);
}

void Health::Update(float deltatime)
{
	Vector2 newPosition = ViewPort::getInstance()->getPositionWorld();
	setPosition(newPosition.x, newPosition.y - 50);

	iStatus = InforAladdin::getInstance()->getHealth();
	if (iStatus <= 0)
	{
		if (InforAladdin::getInstance()->getLife() <= 0)
		{
			//chuyen scene
			return;
		}
		else
		{
			InforAladdin::getInstance()->plusLife(-1);
			InforAladdin::getInstance()->setHealth(120);
			_aladdin->Revival();
		}
	}

	_animations[iStatus]->Update(deltatime);

}

void Health::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[iStatus]->Draw(spritehandle, viewport);
}

void Health::Release()
{
	SAFE_DELETE(this->_sprite);
}

void Health::UpdateStatus()
{
}

Health::~Health()
{
}