#include "GuardThin.h"

GuardThin::GuardThin(eStatus status, int posX, int posY, eDirection direction, int minMove, int maxMove) :BaseEnemy(eID::GUARDTHIN)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDTHIN);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDTHIN_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	_minMove = getPositionX() - minMove;
	_maxMove = getPositionX() + maxMove;
	InIt();
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
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDTHIN, "guard_moving_0", 8);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDTHIN, "guard_moving_0", 8);

	_animations[ATTACK] = new Animation(_sprite, 0.15f);
	_animations[ATTACK]->addFrameRect(eID::GUARDTHIN, "guardsThin_attack_0", 6);

	_animations[BEHIT] = new Animation(_sprite, 0.2f);
	_animations[BEHIT]->addFrameRect(eID::GUARDTHIN, "guards_being_attack_0", 9);

	_animations[DYING] = new Animation(_sprite, 0.1f);
	_animations[DYING]->addFrameRect(eID::GUARDTHIN, "destroy_enermy_00_0", 10);

	_animations[FREE] = new Animation(_sprite, 0.2f);
	_animations[FREE]->addFrameRect(eID::GUARDTHIN, "free_0", "free_0", NULL);

	_sprite->setOrigin(Vector2(0.5, 0));

	_hitpoint = 4;//Số lần đánh
	_score = 10; //Số điểm được mỗi lần giết enermy


}

void GuardThin::Update(float deltatime)
{
	
	_animations[this->getStatus()]->Update(deltatime);

	this->UpdateStatus(deltatime);

	//update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		
		it->second->Update(deltatime);
	}
}


void GuardThin::UpdateStatus(float dt)
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	switch (this->getStatus())
	{
	case eStatus::DESTROY:
		return;
	case eStatus::BEHIT:
	{
		standing();
		if (_animations[BEHIT]->getIndex() == 7)
		{
			_animations[BEHIT]->setIndex(0);
			removeStatus(BEHIT);
			setStatus(ATTACK);

				if (_hitpoint <= 0)
				{
					InforAladdin::getInstance()->plusScore(10);
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

	/*if (distanceBetweenAladdin().y > 0)
	return;*/
	this->clearStatus();
	if (_minMove < this->getPositionX() && this->getPositionX() < _maxMove)
	{
		if (distanceBetweenAladdin().x < 0)
		{
			float distance = -distanceBetweenAladdin().x;
			if (distance > 200)
			{
				this->setStatus(eStatus::FREE);
				standing();
			}
			else if (50 < distance && distance < 200)
			{
				this->addStatus(eStatus::MOVING_LEFT);
				movingLeft();
			}
			else if (distance <= 50)
			{
				_sprite->setScaleX(-1.6);
				this->setStatus(eStatus::ATTACK);
				standing();
			}
		}
		else if (distanceBetweenAladdin().x > 0)
		{
			float distance = distanceBetweenAladdin().x;
			if (distance > 300)
			{

				this->setStatus(eStatus::FREE);
				standing();
			}
			else if (50 < distance && distance < 300)
			{
				this->addStatus(eStatus::MOVING_RIGHT);
				movingRight();
			}
			else if (distance <= 50)
			{
				_sprite->setScaleX(1.6);
				this->setStatus(eStatus::ATTACK);
				standing();
			}
		}
	}
	else if ((_minMove > this->getPositionX()) && xAla < _minMove)
	{
		this->addStatus(eStatus::FREE);
		standing();
	}
	else if (distanceBetweenAladdin().x > 0 && xAla > _minMove && this->getPositionX() < _maxMove)
	{
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();
	}
	else if ((this->getPositionX() > _maxMove) && xAla > _maxMove)
	{
		this->addStatus(eStatus::FREE);
		standing();
	}
	else if (distanceBetweenAladdin().x < 0 && xAla < _maxMove)
	{
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();
	}
	else if (_minMove < this->getPositionX() < _maxMove)
	{
		this->setStatus(eStatus::FREE);
		standing();
	}
}

void GuardThin::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
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
				if (_hitpoint == 0)
				{
					setStatus(DYING);
					return;
				}
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
				  DK2 bức ảnh status Attack của guarthin hiện tại là 5*/
				if (collision_event->_otherObject->isInStatus(eStatus::BEHIT) == false 
					&&
					this->_animations[ATTACK]->getIndex() == 5)
			{

					//âm thanh
					SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);

					//Lưu trạng thái trước khi hết bị đánh set lại cái trạng thái cũ
				collision_event->_otherObject->savePreStatus();
				//Set status aladdin bị đánh
				collision_event->_otherObject->setStatus(eStatus::BEHIT);
				InforAladdin::getInstance()->plusHealth(-10);
			}
		break;
	}
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
	collisionBody->checkCollision(object, dt, true);

	return 0.0f;

}

RECT GuardThin::getBounding()
{
	RECT r = BaseObject::getBounding();
	//if (isInStatus(FREE))
	//{

	//	float distancex = abs(r.right - r.left) / 3.0f;
	//	r.left = r.left + distancex;
	//	r.right = r.right - distancex;
	//}
	return r;
}


Vector2 GuardThin::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

	float yAla = _divingSprite->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x, yAla - y);
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
