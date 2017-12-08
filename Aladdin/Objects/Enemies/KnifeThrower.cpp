#include "KnifeThrower.h"

KnifeThrower::KnifeThrower(eStatus status, int posX, int posY, eDirection direction)
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


	//_sprite->drawBounding(false);
	_canThrow = true;

}

void KnifeThrower::Update(float deltatime)
{
	this->UpdateStatus(deltatime);

	_animations[this->getStatus()]->Update(deltatime);
	knife->Update(deltatime);
	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void KnifeThrower::Draw(LPD3DXSPRITE spritehandle, Viewport* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
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

void KnifeThrower::onCollisionBegin(CollisionEventArg *)
{
}

void KnifeThrower::onCollisionEnd(CollisionEventArg *)
{
}

float KnifeThrower::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

float KnifeThrower::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

#pragma region Test
	char str[100];
	sprintf(str, "khoang cach voi aladdin: %f", xAla - x);
	text->setText(str);
#pragma endregion


	return xAla - x;
}

void KnifeThrower::UpdateStatus(float dt)
{
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
					knife->clearStatus();
					knife->addStatus(eStatus::THROW_LEFT_NEAR);
				}
				else
				{
					knife->clearStatus();
					knife->addStatus(eStatus::THROW_LEFT_FAR);
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
					knife->clearStatus();
					knife->addStatus(eStatus::THROW_RIGHT_NEAR);
				}
				else
				{
					knife->clearStatus();
					knife->addStatus(eStatus::THROW_RIGHT_FAR);
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

