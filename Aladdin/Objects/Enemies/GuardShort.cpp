#include "GuardShort.h"

GuardShort::GuardShort(eStatus status, int posX, int posY, eDirection direction, int minMove, int maxMove) :BaseEnemy(eID::GUARDSHORT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDSHORT);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDSHORT_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	_minMove = 300; //- minMove;
	_maxMove = 300; //+ maxMove;
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void GuardShort::InIt()
{
	knife = new KnifeShort(eStatus::NORMAL, getPositionX(), getPositionY(), eDirection::NONE);
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

	_animations[DYING] = new Animation(_sprite, 0.2f);
	_animations[DYING]->addFrameRect(eID::GUARDSHORT, "destroy_enermy_", 10);

	_canThrow = false;
	_hitpoint = 2;// Chú ý 2 lần đánh chứ không phải 3
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
				if (collision_event->_otherObject->getIndex() == 4 && _hitpoint >= 1)
				{
					_hitpoint = 0;
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
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

	float yAla = _divingSprite->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x, yAla - y);
}

void GuardShort::UpdateStatus(float dt)
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
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
		if (distance.x > _minMove)
		{
			setStatus(FREE);
		}
		else if(distance.x < 320 && distance.x > 200)
		{
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
		if (distance.x > _minMove)
		{
			setStatus(FREE);
		}
		else if (distance.x < 320 && distance.x > 200)
		{
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

