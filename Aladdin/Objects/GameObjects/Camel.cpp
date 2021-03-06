﻿#include "Camel.h"

Camel::Camel(int posX, int posY) :BaseObject(eID::CAMEL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::CAMEL);
	//_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	this->setStatus(NORMAL);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Camel::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	bulletCamel = new BulletCamel(eStatus::THROW, this->getPositionX(), this->getPositionY() + 500);
	bulletCamel->InIt();

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Camel::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Camel::onCollisionEnd);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::CAMEL, "camel_0", "camel_0",NULL);

	_animations[eStatus::BEHIT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::BEHIT]->addFrameRect(eID::CAMEL, "camel_", 7);
}

void Camel::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);
	bulletCamel->Update(deltatime);
	
	UpdateStatus();

	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		
		it->second->Update(deltatime);
	}
	bulletCamel->checkCollision(this, deltatime);
}

void Camel::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_sprite->UpdatePosition();
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	bulletCamel->Draw(spritehandle, viewport);
}

void Camel::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
	bulletCamel->Release();
}

void Camel::UpdateStatus()
{
	if (_animations[BEHIT]->getIndex() == 4)
	{
		bulletCamel->Shoot(this->getPositionX() + 140, this->getPositionY());
	}

	if (_animations[BEHIT]->getIndex() >= 6)
	{
		_animations[BEHIT]->setIndex(0);
		setStatus(NORMAL);
	}
}

void Camel::onCollisionBegin(CollisionEventArg *collision_event)
{
	//eID objectID = collision_event->_otherObject->getId();
	//switch (objectID)
	//{
	//	case eID::ALADDIN:
	//	{
	//		if (collision_event->_otherObject->isInStatus(eStatus::JUMPING))
	//		{
	//			this->setStatus(BEHIT);
	//			collision_event->_otherObject->setStatus(eStatus::JUMPING);			
	//		}
	//		break;
	//	}
	//}
}

void Camel::onCollisionEnd(CollisionEventArg *)
{
}

float Camel::checkCollision(BaseObject *object, float dt)
{
	return 0.0f;
}

RECT Camel::getBounding()
{
	RECT rect = BaseObject::getBounding();
	rect.right -= 90;
	rect.top -=50;

	return rect;
}

Camel::~Camel()
{
}
