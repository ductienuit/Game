#include "GuardThrowJar.h"

GuardThrowJar::GuardThrowJar(eStatus status, int posX, int posY) :BaseEnemy(eID::GUARDTHROWJAR)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDTHROWJAR);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);

	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);

	jar = new Jar(eStatus::DROP, posX, posY, eDirection::BOTTOM);

	_score = 10;
	InIt();
}

void GuardThrowJar::InIt()
{
	jar->InIt();

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardThrowJar::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardThrowJar::onCollisionEnd);

	_animations[FREE] = new Animation(_sprite, 0.2f);
	_animations[FREE]->addFrameRect(eID::GUARDTHROWJAR, "GuardThrowJar_0", "GuardThrowJar_0", NULL);

	_animations[THROW] = new Animation(_sprite, 0.08f);
	_animations[THROW]->addFrameRect(eID::GUARDTHROWJAR, "GuardThrowJar_", 10);

	_animations[DYING] = new Animation(_sprite, 0.1f);
	_animations[DYING]->addFrameRect(eID::GUARDTHROWJAR, "destroy_enermy_", 10);

	_sprite->drawBounding(false);
	_canDrop = true;
}

void GuardThrowJar::Update(float deltatime)
{
	eStatus temp = this->getStatus();
	_animations[temp]->Update(deltatime);

	this->UpdateStatus(deltatime);

	//Jar là cái lu
	jar->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void GuardThrowJar::UpdateStatus(float dt)
{
	switch (this->getStatus())
	{
		case eStatus::DESTROY:
			return;
		case eStatus::DYING:
		{
			standing();
			if (_animations[DYING]->getIndex() == 9)
			{
				_animations[DYING]->setIndex(0);
				this->setStatus(DESTROY);
				//score+=10;
			}
			return;
		}
	}





	if (distanceBetweenAladdin().y > 0)
		return;
	if (distanceBetweenAladdin() < 0)
	{
		float distance = -distanceBetweenAladdin().x;

		if (distance <= 80)
		{
			this->clearStatus();
			this->addStatus(eStatus::THROW);
			jar->addStatus(eStatus::DROP);
			if (_animations[_status]->getIndex() == 6)
			{
				jar->Drop();
			}
			return;
		}
		else if (distance > 80)
		{
			jar->addStatus(eStatus::DROP);
			if (_animations[_status]->getIndex() == 6)
			{
				jar->Drop();
			}
			if (isInStatus(THROW) && _animations[this->getStatus()]->getIndex() >= 9)
			{
				_animations[this->getStatus()]->setIndex(0);
				removeStatus(eStatus::THROW);
				this->addStatus(FREE);
			}
			return;
		}
		this->clearStatus();
		this->addStatus(FREE);
		return;
	}
	//-----------------------------------------------------------------------------
	else if (distanceBetweenAladdin() > 0)
	{
		float distance = distanceBetweenAladdin().x;
		if (distance <= 80)
		{
			this->clearStatus();
			this->addStatus(eStatus::THROW);
			jar->addStatus(eStatus::DROP);
			if (_animations[_status]->getIndex() == 6)
			{
				jar->Drop();
			}
			return;
		}
		else if (distance > 80)
		{
			jar->addStatus(eStatus::DROP);
			if (_animations[_status]->getIndex() == 6)
			{
				jar->Drop();
			}
			if (isInStatus(THROW) && _animations[this->getStatus()]->getIndex() >= 9)
			{

				_animations[this->getStatus()]->setIndex(0);
				removeStatus(eStatus::THROW);
				this->addStatus(FREE);
			}
			return;
		}
		this->clearStatus();
		this->addStatus(FREE);
		return;
	}
}

void GuardThrowJar::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
	jar->Draw(spritehandle, viewport);
}

void GuardThrowJar::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
	jar->Release();
}

void GuardThrowJar::onCollisionBegin(CollisionEventArg *collision_event)
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

void GuardThrowJar::onCollisionEnd(CollisionEventArg *)
{
}

float GuardThrowJar::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	//Check collision enermy(this) với aladdin(object)
	/*Ưu tiên check GuardThrowJar trước, sau đó đến Jar*/
	if(!collisionBody->checkCollision(object, dt, true))
		jar->checkCollision(object, dt);
	return 0.0f;
}

Vector2 GuardThrowJar::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

	float yAla = _divingSprite->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x,yAla-y);
}

IComponent* GuardThrowJar::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardThrowJar::~GuardThrowJar()
{
}

void GuardThrowJar::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}
