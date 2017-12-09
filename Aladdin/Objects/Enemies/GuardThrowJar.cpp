#include "GuardThrowJar.h"

ThrowJar::ThrowJar(eStatus status, int posX, int posY) :BaseEnemy(eID::THROWJAR)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::THROWJAR);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	/*Vector2 v(direction * THROWJAR_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));*/
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
}

void ThrowJar::InIt()
{

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	jar = new Jar(eStatus::DROP, this->getPositionX(), this->getPositionY(), eDirection::BOTTOM);
	jar->InIt();

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &ThrowJar::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &ThrowJar::onCollisionEnd);

	_animations[FREE] = new Animation(_sprite, 0.2f);
	_animations[FREE]->addFrameRect(eID::THROWJAR, "lulu", "lulu", NULL);

	_animations[THROW] = new Animation(_sprite, 0.15f);
	_animations[THROW]->addFrameRect(eID::THROWJAR, "lulu_0", 10);

	_animations[DROP] = new Animation(_sprite, 0.1f);
	_animations[DROP]->addFrameRect(eID::JAR, "lu_roi_", 6);

	_animations[DROP | DESTROY] = new Animation(_sprite, 0.1f);
	_animations[DROP | DESTROY]->addFrameRect(eID::JAR, "lu_be_", 8);

	_animations[DESTROY] = new Animation(_sprite, 0.1f);
	_animations[DESTROY]->addFrameRect(eID::JAR, "lu_be_", 8);


	//_sprite->drawBounding(false);
	_canDrop = true;
}

void ThrowJar::Update(float deltatime)
{
	this->UpdateStatus(deltatime);

	eStatus xL = this->getStatus();
	_animations[/*this->getStatus()*/xL]->Update(deltatime);
	jar->Update(deltatime);
	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void ThrowJar::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
	jar->Draw(spritehandle, viewport);
}

void ThrowJar::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
	jar->Release();
}

void ThrowJar::onCollisionBegin(CollisionEventArg *)
{
}

void ThrowJar::onCollisionEnd(CollisionEventArg *)
{
}

float ThrowJar::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

Vector2 ThrowJar::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

	float yAla = _divingSprite->getPositionY();
	float y = this->getPositionY();
#pragma region Test
	/*char str[100];
	sprintf(str, "khoang cach voi aladdin: %f", xAla - x);
	text->setText(str);*/
#pragma endregion


	return Vector2(xAla - x,yAla-y);
}

void ThrowJar::UpdateStatus(float dt)
{
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
				/*	if (jar->PositionY() <= 140 && jar->PositionY() >= 100)
				{
				jar->clearStatus();
				jar->addStatus(eStatus::DESTROY);
				jar->standing();
				}*/
			}
			return;
		}
		else if (distance > 80)
		{
			jar->addStatus(eStatus::DROP);
			if (_animations[_status]->getIndex() == 6)
			{
				jar->Drop();
				/*	if (jar->PositionY() <= 140 && jar->PositionY() >= 100)
				{
				jar->clearStatus();
				jar->addStatus(eStatus::DESTROY);
				jar->standing();
				}*/
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
				/*if (jar->PositionY() <= 140 && jar->PositionY() >= 100)
				{
				jar->clearStatus();
				jar->addStatus(eStatus::DESTROY);
				jar->standing();
				}*/
			}
			return;
		}
		else if (distance > 80)
		{
			jar->addStatus(eStatus::DROP);
			if (_animations[_status]->getIndex() == 6)
			{
				jar->Drop();
				/*	if (jar->PositionY() <= 140 && jar->PositionY() >= 100)
				{
				jar->clearStatus();
				jar->addStatus(eStatus::DESTROY);
				jar->standing();
				}*/
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

IComponent* ThrowJar::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

ThrowJar::~ThrowJar()
{
}


void ThrowJar::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}
