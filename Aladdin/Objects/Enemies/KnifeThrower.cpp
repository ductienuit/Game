#include "KnifeThrower.h"

KnifeThrower::KnifeThrower(eStatus status, int posX, int posY, eDirection direction) :BaseEnemy(eID::KNIFETHROWER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::KNIFETHROWER);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * KNIFETHROWER_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void KnifeThrower::InIt()
{
	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	knife = new Knife(eStatus::THROW_LEFT_FAR, this->getPositionX(), this->getPositionY(), eDirection::NONE);
	knife->InIt();

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &KnifeThrower::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &KnifeThrower::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[MOVING_LEFT]->addFrameRect(eID::KNIFETHROWER, "knifeThrowers_attack_0", 10);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::KNIFETHROWER, "knifeThrowers_attack_0", 10);

	_animations[DYING] = new Animation(_sprite, 0.05f);
	_animations[DYING]->addFrameRect(eID::GUARDLU, "destroy_enermy_", 10);

	_sprite->drawBounding(false);
	_canThrow = true;

	_hitpoint = 2;// 1 lần đánh
	_score = 10; //Số điểm được mỗi lần giết enermy
}

void KnifeThrower::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);
	knife->Update(deltatime);

	this->UpdateStatus(deltatime);	

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void KnifeThrower::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	knife->Draw(spritehandle, viewport);
}

void KnifeThrower::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
	knife->Release();
}

void KnifeThrower::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		if (collision_event->_otherObject->isInStatus(ATTACK))
		{
			//mạng sống còn 1 và bức ảnh ATTACK của aladdin bằng 1
			if (collision_event->_otherObject->getIndex() == 3)
			{
				this->setStatus(eStatus::DYING);
			}
			break;
		}
		break;
	}
	default:
		break;
	}
}

void KnifeThrower::onCollisionEnd(CollisionEventArg *)
{
}

float KnifeThrower::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	//Check collision enermy(this) với aladdin(object)
	/*Ưu tiên check KnifeThrower trước, sau đó đến knife*/
	if (!collisionBody->checkCollision(object, dt, true))
		knife->checkCollision(object, dt);
	return 0.0f;
}

float KnifeThrower::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();
	return xAla - x;
}

void KnifeThrower::UpdateStatus(float dt)
{
	switch (this->getStatus())
	{
	case eStatus::DESTROY:
		return;
	case eStatus::DYING:
	{
		if (_animations[DYING]->getIndex() == 9)
		{
			_animations[DYING]->setIndex(0);
			this->setStatus(DESTROY);
			//score+=10;
		}
		return;
	}
	}


	if (distanceBetweenAladdin() < 0)
	{
		this->clearStatus();
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();

		if (-distanceBetweenAladdin() < 350)
		{
			if (knife->canChangeThrowDirection())
			{
				if (-distanceBetweenAladdin() < 300)
				{
					knife->setStatus(eStatus::THROW_LEFT_NEAR);
				}
				else
				{
					knife->setStatus(eStatus::THROW_LEFT_FAR);
				}
			}
			return;
		}
	}
	else
	{
		this->clearStatus();
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();

		if (distanceBetweenAladdin() < 350)
		{
			if (knife->canChangeThrowDirection())
			{
				if (distanceBetweenAladdin() < 300)
				{
					knife->setStatus(eStatus::THROW_RIGHT_NEAR);
				}
				else
				{
					knife->setStatus(eStatus::THROW_RIGHT_FAR);
				}
			}
			return;
		}
	}
}

IComponent* KnifeThrower::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

KnifeThrower::~KnifeThrower()
{
}

void KnifeThrower::movingLeft()
{
	_sprite->setScaleX(-1.6);
}

void KnifeThrower::movingRight()
{
	_sprite->setScaleX(1.6);
}

