#include "GuardFat.h"

GuardFat::GuardFat(eStatus status, int posX, int posY, eDirection direction) :BaseEnemy(eID::GUARDFAT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDFAT);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDFAT_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	InIt();
}

void GuardFat::InIt()
{

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardFat::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardFat::onCollisionEnd);

	_animations[FREE] = new Animation(_sprite, 0.15f);
	_animations[FREE]->addFrameRect(eID::GUARDFAT, "guardsFat_Near_0", 6);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDFAT, "guardsFat_Moving_0", 8);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDFAT, "guardsFat_Moving_0", 8);

	_animations[ATTACK] = new Animation(_sprite, 0.15f);
	_animations[ATTACK]->addFrameRect(eID::GUARDFAT, "guardsFat_AttackTwo_0", 5);

	_animations[SITTING_DOWN| ATTACK] = new Animation(_sprite, 0.15f);
	_animations[SITTING_DOWN | ATTACK]->addFrameRect(eID::GUARDFAT, "guardsFat_AttackOne_0", 6);

	_animations[BEHIT] = new Animation(_sprite, 0.1f);
	_animations[BEHIT]->addFrameRect(eID::GUARDFAT, "guardsFat_beingAttack_0", 6);

	_animations[DYING] = new Animation(_sprite, 0.1f);
	_animations[DYING]->addFrameRect(eID::GUARDFAT, "destroy_enermy_", 10);

	_sprite->setOrigin(Vector2(0.5, 0));

	_hitpoint = 4;//Số lần đánh
	_score = 10; //Số điểm được mỗi lần giết enermy


}

void GuardFat::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	this->UpdateStatus(deltatime);

	//update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void GuardFat::UpdateStatus(float dt)
{
	switch (this->getStatus())
	{
	case eStatus::DESTROY:
		return;
	case eStatus::BEHIT:
	{
		standing();
		if (_animations[BEHIT]->getIndex() == 5)
		{
			_animations[BEHIT]->setIndex(0);
			removeStatus(BEHIT);
			setStatus(ATTACK);

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
	}

	if (distanceBetweenAladdin().y > 0)
		return;
	//Aladdin đứng bên trái
	if (distanceBetweenAladdin().x <= 0)
	{
		float distance = -distanceBetweenAladdin().x;
		if (distance < 100)
		{
			_sprite->setScaleX(-1.6);
			this->setStatus(eStatus::ATTACK);
			standing();
			return;
		}
		else if (distance >= 100 && distance < 400)
		{
			this->setStatus(eStatus::MOVING_LEFT);
			movingLeft();
			return;
		}
		this->setStatus(eStatus::FREE);
		standing();
		return;
	}
	else /*if (distanceBetweenAladdin().x > 0)*/
	{
		float distance = distanceBetweenAladdin().x;
		if (distance < 100)
		{
			_sprite->setScaleX(1.6);
			this->setStatus(eStatus::ATTACK);
			standing();
			return;
		}
		else if (distance >= 100 && distance < 400)
		{
			this->setStatus(eStatus::MOVING_RIGHT);
			movingRight();
			return;
		}
		this->setStatus(eStatus::FREE);
		standing();
		return;
	}
}

void GuardFat::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void GuardFat::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void GuardFat::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
		case eID::ALADDIN:
		{
			if (collision_event->_otherObject->isInStatus(SITTING_DOWN) && this->isInStatus(DYING) && isInStatus(DESTROY))
			{
				this->setStatus(eStatus(SITTING_DOWN | ATTACK));
			}
			if (collision_event->_otherObject->isInStatus(ATTACK))
			{
				//mạng sống còn 1 và bức ảnh ATTACK của aladdin bằng 1
				if (collision_event->_otherObject->getIndex() == 1 && _hitpoint >= 1)
				{
					_hitpoint -= 1;
					this->setStatus(eStatus::BEHIT);
				}
				break;
			}
			else
				/*DK1:Aladdin đang không bị đánh
				DK2 bức ảnh status Attack của guardFat hiện tại là 4*/
				if (collision_event->_otherObject->isInStatus(eStatus::BEHIT) == false
					&&
					this->_animations[ATTACK]->getIndex() == 4)
				{
					//Set status aladdin bị đánh
					collision_event->_otherObject->setStatus(eStatus::BEHIT);
				}
			break;
		}
	}
}

void GuardFat::onCollisionEnd(CollisionEventArg *)
{
	//do nothing
}

float GuardFat::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

Vector2 GuardFat::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

	float yAla = _divingSprite->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x, yAla - y);
}

IComponent* GuardFat::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardFat::~GuardFat()
{
}

void GuardFat::movingLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-GUARDFAT_SPEED, move->getVelocity().y));
}

void GuardFat::movingRight()
{
	_sprite->setScaleX(1.6);

	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(GUARDFAT_SPEED, move->getVelocity().y));
}

void GuardFat::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}
