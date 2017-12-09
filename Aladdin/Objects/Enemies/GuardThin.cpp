#include "GuardThin.h"

GuardThin::GuardThin(eStatus status, int posX, int posY, eDirection direction):BaseEnemy(eID::GUARDTHIN)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDTHIN);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDTHIN_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX,posY,1.0f);

	_hitpoint = 2;//Số lần đánh
	_score = 10; //Số điểm được mỗi lần giết enermy
}

void GuardThin::InIt()
{
	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardThin::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardThin::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDTHIN, "guard_moving_0",8);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDTHIN, "guard_moving_0", 8);

	_animations[ATTACK] = new Animation(_sprite, 0.15f);
	_animations[ATTACK]->addFrameRect(eID::GUARDTHIN, "guardsThin_attack_0", 6);

	_animations[BEHIT] = new Animation(_sprite, 0.2f);
	_animations[BEHIT]->addFrameRect(eID::GUARDTHIN, "guards_being_attack_0", 9);

	_sprite->setOrigin(Vector2(0.5, 0));
	
}

void GuardThin::Update(float deltatime)
{
	this->UpdateStatus(deltatime);

	_animations[this->getStatus()]->Update(deltatime);

	float x = this->getPositionX();
	float y = this->getPositionY();
	//update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void GuardThin::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle,viewport);
}

void GuardThin::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void GuardThin::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		if (collision_event->_otherObject->isInStatus(ATTACK))
		{
			//mạng sống còn 1
			if (--_hitpoint <= 0)
			{
				this->setStatus(eStatus::BEHIT);
				//score+=10;
			}
			break;
		}
		else
			/*DK1:Aladdin đang không bị đánh
			  DK2 bức ảnh status Attack của guarthin hiện tại là 5*/
			if (collision_event->_otherObject->isInStatus(eStatus::BEHIT) == false 
				&&
				this->_animations[ATTACK]->getIndex() == 5)
		{
			//Set status aladdin bị đánh
			collision_event->_otherObject->setStatus(eStatus::BEHIT);
		}
		break;
	}
	default:
		break;
	}
}

void GuardThin::onCollisionEnd(CollisionEventArg *)
{
	//do nothing
}

float GuardThin::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt,true);
	return 0.0f;
}

float GuardThin::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX();
	float x = this->getPositionX();
	return xAla-x;
}

void GuardThin::UpdateStatus(float dt)
{
	if (isInStatus(BEHIT))
	{
		standing();
		if (_animations[BEHIT]->getIndex() == 8)
		{
			_animations[BEHIT]->setIndex(0);
			removeStatus(BEHIT);
			addStatus(MOVING_LEFT);
		}
		return;
	}
	//Aladdin đứng bên trái
	if (distanceBetweenAladdin() < 0)
	{
		float distance = -distanceBetweenAladdin();
		if (distance < 100)
		{
			this->clearStatus();
			this->addStatus(eStatus::ATTACK);
			standing();
			return;
		}
		this->clearStatus();
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();
	}
	else if (distanceBetweenAladdin() > 0)
	{
		float distance = distanceBetweenAladdin();
		if (distance < 50)
		{
			this->clearStatus();
			this->addStatus(eStatus::ATTACK);
			standing();
			return;
		}
		this->clearStatus();
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();
	}
}

IComponent* GuardThin::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardThin::~GuardThin()
{
}

void GuardThin::movingLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-GUARDTHIN_SPEED, move->getVelocity().y));
}

void GuardThin::movingRight()
{
	_sprite->setScaleX(1.6);

	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(GUARDTHIN_SPEED, move->getVelocity().y));
}

void GuardThin::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}
