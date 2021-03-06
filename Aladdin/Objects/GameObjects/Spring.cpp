﻿#include "Spring.h"

Spring::Spring(int posX, int posY) :BaseObject(eID::SPRING)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::SPRING);
	_sprite->setFrameRect(0, 0, 16.0f, 16.0f);

	this->setStatus(NORMAL);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	setScale(SCALEONE);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Spring::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Spring::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Spring::onCollisionEnd);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::SPRING, "Spring_0", "Spring_0", NULL);

	_animations[eStatus::BEHIT] = new Animation(_sprite, 0.05f);
	_animations[eStatus::BEHIT]->addFrameRect(eID::SPRING, "Spring_", 9);
}

void Spring::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	UpdateStatus();

	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void Spring::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_sprite->UpdatePosition();
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void Spring::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Spring::UpdateStatus()
{
	if (_animations[BEHIT]->getIndex() == 8)
	{
		_animations[BEHIT]->setIndex(0);
		this->setStatus(NORMAL);
	}
}

void Spring::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
		case eID::ALADDIN:
		{
			this->setStatus(BEHIT);
			//collision_event->_otherObject->setStatus(eStatus::JUMPING);			
			break;
		}
	}
}

void Spring::onCollisionEnd(CollisionEventArg *)
{
}

float Spring::checkCollision(BaseObject *object, float dt)
{
	return 0.0f;
}

RECT Spring::getBounding()
{
	RECT rect = BaseObject::getBounding();
	rect.top -= 40;

	return rect;
} 
Spring::~Spring()
{
}