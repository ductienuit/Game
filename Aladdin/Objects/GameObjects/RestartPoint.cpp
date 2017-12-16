﻿#include "RestartPoint.h"
RestartPoint::RestartPoint(int posX, int posY) :BaseObject(eID::RESTARTPOINT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::RESTARTPOINT);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(NORMAL);
	setScale(SCALEAPPLE);
	this->setPosition(posX*SCALEFACTOR.x, posY*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void RestartPoint::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &RestartPoint::onCollisionBegin);

	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::RESTARTPOINT, "genie_restart_point_00", "genie_restart_point_00", NULL);

	_animations[BEHIT] = new Animation(_sprite, 0.12f);
	_animations[BEHIT]->addFrameRect(eID::RESTARTPOINT, "genie_restart_point_0", 10);

	_animations[FREE] = new Animation(_sprite, 0.12f);
	_animations[FREE]->addFrameRect(eID::RESTARTPOINT, "genie_restart_point_09", "genie_restart_point_09", "genie_restart_point_09", NULL);

	_canTurn = true;
}

void RestartPoint::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	if (_animations[BEHIT]->getIndex() >= 9)
	{
		_canTurn = false;
	}

}

void RestartPoint::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void RestartPoint::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void RestartPoint::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	
	 switch (objectID)
	{
	case eID::ALADDIN:
	{
		if (_canTurn)
		{
			setStatus(BEHIT);
		}
		else
		{
			setStatus(FREE);
		}
		break;
	}
	}

}

void RestartPoint::onCollisionEnd(CollisionEventArg *)
{
}

float RestartPoint::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision táo với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

RestartPoint::~RestartPoint()
{
}