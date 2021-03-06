﻿#include "GuardShort.h"

GuardShort::GuardShort(eStatus status, int posX, int posY, BaseObject* aladdin, int minMove, int maxMove) :BaseEnemy(eID::GUARDSHORT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDSHORT);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	_aladdin = aladdin;
	Vector2 v(0 * GUARDSHORT_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	_originPosition = Vector2(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y);
	_minMove =  minMove;
	_maxMove =  maxMove;
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void GuardShort::InIt()
{
	knife = new KnifeShort(eStatus::NORMAL, getPositionX(), getPositionY());
	knife->InIt();

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardShort::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardShort::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDSHORT, "guardsShort_Moving_0", 8);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDSHORT, "guardsShort_Moving_0", 8);

	_animations[THROW] = new Animation(_sprite, 0.2f);
	_animations[THROW]->addFrameRect(eID::GUARDSHORT, "guardsShort_attack_",5);

	_animations[FREE] = new Animation(_sprite, 0.2f);
	_animations[FREE]->addFrameRect(eID::GUARDSHORT, "guardsShort_free_0", 5);

	_animations[BEHIT] = new Animation(_sprite, 0.15f);
	_animations[BEHIT]->addFrameRect(eID::GUARDSHORT, "guardsShort_dying_0", 7);

	_animations[DYING] = new Animation(_sprite, 0.1f);
	_animations[DYING]->addFrameRect(eID::GUARDSHORT, "destroy_enermy_00_0", 10);

	_canThrow = false;
	_hitpoint = 4;// Chú ý 2 lần đánh chứ không phải 3
	_score = 10; //Số điểm được mỗi lần giết enermy

}

void GuardShort::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);



	this->UpdateStatus(deltatime);
	knife->Update(deltatime);
	
	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void GuardShort::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);

	knife->Draw(spritehandle, viewport);
}

void GuardShort::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
	knife->Release();
}

void GuardShort::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
		case eID::ALADDIN:
		{
			if (collision_event->_otherObject->isInStatus(ATTACK))
			{
				//mạng sống còn 1 và bức ảnh ATTACK của aladdin bằng 1
				if (collision_event->_otherObject->getIndex() == 2 && _hitpoint >= 1)
				{
					_hitpoint = 0;
					//SOUNDDDDDD
					//Nhạc khi object bị destroy
					SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
					this->setStatus(eStatus::DYING);
				}
				break;
				
			}
			break;
		}
	}
}

void GuardShort::onCollisionEnd(CollisionEventArg *)
{
}

float GuardShort::checkCollision(BaseObject *object, float dt)
{
	if (isInStatus(DYING))
		return 0.0f;
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	//Check collision enermy(this) với aladdin(object)
	/*Ưu tiên check GuardShort trước, sau đó đến knife*/
	if (!collisionBody->checkCollision(object, dt, true))
		knife->checkCollision(object, dt);
	return 0.0f;
}

Vector2 GuardShort::distanceBetweenAladdin()
{
	float xAla = _aladdin->getPositionX();
	float x = this->getPositionX();

	float yAla = _aladdin->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x, yAla - y);
}

void GuardShort::UpdateStatus(float dt)
{
	float xAla = _aladdin->getPositionX() + (_aladdin->getBounding().right - _aladdin->getBounding().left) / 2;
	switch (this->getStatus())
	{
		case eStatus::DESTROY:
			return;
		case eStatus::BEHIT:
		{
			standing();
			if (_animations[BEHIT]->getIndex() == 6)
			{
				_animations[BEHIT]->setIndex(0);
				removeStatus(BEHIT);
				addStatus(MOVING_LEFT);

				if (_hitpoint <= 0)
				{
					//score+=10;
					this->setStatus(DYING);
				}
			}
			return;
		}
		case eStatus::DYING:
		{
			if (_animations[DYING]->getIndex() == 9)
			{
				_animations[DYING]->setIndex(0);
				this->setStatus(DESTROY);
			}
			return;
		}
		case eStatus::FREE:
		{
			standing();
			break;
		}
		case eStatus::THROW:
		{
			standing();

			if (_animations[THROW]->getIndex() == 3)
			{
				knife->Restart(getPositionX(), getPositionY() + 60, (getScale().x < 0));
				_animations[this->getStatus()]->NextFrame();
				////âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/ObjectThrow.wav", 0);
			}
			break;
		}
		case eStatus::MOVING_LEFT:
		{
			movingLeft();
			break;
		}
		case eStatus::MOVING_RIGHT:
		{
			movingRight();
			break;
		}
	}
	Vector2 distance = distanceBetweenAladdin();
	float x = getPositionX();
	float y = getPositionY();


	//Aladdin bên trái enermy
	if (distance.x <= 0)
	{
		distance.x = (-1)*distance.x;

		if(distance.x < 320 && distance.x > 200)
		{
			if (_originPosition.x - _minMove > x)
			{
				setStatus(FREE);
				return;
			}
			setStatus(MOVING_LEFT);
			setScaleX(-SCALECHARACTER.x);
		}
		else if (distance.x < 200 && distance.x>=0)
		{
			setStatus(THROW);
			setScaleX(-SCALECHARACTER.x);

		}
	}
	//Aladdin bên phải enermy
	else if (distance.x > 0)
	{
		 if (distance.x < 320 && distance.x > 200)
		{
			if (_originPosition.x + _maxMove < x)
			{
				setStatus(FREE);
				return;
			}
			setStatus(MOVING_RIGHT);
			setScaleX(SCALECHARACTER.x);
		}
		else if (distance.x < 200 && distance.x >= 0)
		{
			setStatus(THROW);
			setScaleX(SCALECHARACTER.x);
		}
	}

}

IComponent* GuardShort::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardShort::~GuardShort()
{
}

void GuardShort::movingLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-GUARDSHORT_SPEED, move->getVelocity().y));
}

void GuardShort::movingRight()
{
	_sprite->setScaleX(1.6);

	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(GUARDSHORT_SPEED, move->getVelocity().y));
}

void GuardShort::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}

