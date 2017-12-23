#include "PeddlerShop.h"

PeddlerShop::PeddlerShop(int posX, int posY) :BaseObject(eID::PEDDLERSHOP)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::PEDDLERSHOP);
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);

	this->setStatus(FREE);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void PeddlerShop::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	peddler = new Peddler(this->getPositionX(), this->getPositionY() + 500);
	peddler->InIt();

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &PeddlerShop::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &PeddlerShop::onCollisionEnd);

	_animations[eStatus::NORMAL1] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL1]->addFrameRect(eID::PEDDLERSHOP, "peddler_shop_29", "peddler_shop_29", NULL);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::PEDDLERSHOP, "peddler_shop_00", "peddler_shop_00", "peddler_shop_00", "peddler_shop_00", "peddler_shop_00", "peddler_shop_00", "peddler_shop_01", "peddler_shop_02", "peddler_shop_03", "peddler_shop_04", "peddler_shop_05", "peddler_shop_06", "peddler_shop_07", "peddler_shop_08", "peddler_shop_09", "peddler_shop_10",
		"peddler_shop_11", "peddler_shop_12", "peddler_shop_13", "peddler_shop_14", "peddler_shop_15", "peddler_shop_16", "peddler_shop_17", "peddler_shop_18", "peddler_shop_19", "peddler_shop_20",
		"peddler_shop_21", "peddler_shop_22", "peddler_shop_23", "peddler_shop_24", "peddler_shop_25", "peddler_shop_26", "peddler_shop_27", "peddler_shop_28", "peddler_shop_29", NULL);

	_animations[eStatus::FREE] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FREE]->addFrameRect(eID::PEDDLERSHOP, "peddler_00", "peddler_01", "peddler_02", "peddler_03", "peddler_04", "peddler_05", "peddler_06", "peddler_07", "peddler_08", "peddler_09", "peddler_10",
		"peddler_11", "peddler_12", "peddler_13", NULL);
}

void PeddlerShop::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);
	peddler->Update(deltatime);

	UpdateStatus();

	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{

		it->second->Update(deltatime);
	}
}

void PeddlerShop::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_sprite->UpdatePosition();
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	peddler->Draw(spritehandle, viewport);
}

void PeddlerShop::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
	peddler->Release();
}

void PeddlerShop::UpdateStatus()
{
	if (-distanceBetweenAladdin() < 50)
	{
		canDisappear = false;
		setStatus(NORMAL);
		if (_animations[NORMAL]->getIndex() == 28)
		{
			peddler->setPosition(this->getPositionX() + 145, this->getPositionY());
		}

		if (_animations[NORMAL]->getIndex() >= 29)
		{
			setStatus(NORMAL1);
		}
	}
	else
	{
		if (canDisappear)
		{
			setStatus(FREE);
		}
	}

	if (_animations[NORMAL]->getIndex() < 25 || this->isInStatus(FREE))
	{
		peddler->setPosition(this->getPositionX(), this->getPositionY() + 500);
	}
}

void PeddlerShop::onCollisionBegin(CollisionEventArg *collision_event)
{
}

void PeddlerShop::onCollisionEnd(CollisionEventArg *)
{
}

float PeddlerShop::checkCollision(BaseObject *object, float dt)
{
	return 0.0f;
}

RECT PeddlerShop::getBounding()
{
	RECT rect = BaseObject::getBounding();
	rect.right -= 200;
	rect.top -= 100;

	return rect;
}

float PeddlerShop::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();
	return xAla - x;
}

PeddlerShop::~PeddlerShop()
{
}
