#include "GuardShort.h"

GuardShort::GuardShort(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDSHORT);
	//_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDSHORT_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
}

void GuardShort::InIt()
{

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;
	
	knife = new Knife(eStatus::THROW, this->getPositionX(), this->getPositionY(), eDirection::NONE);
	knife->InIt();

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardShort::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardShort::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDSHORT, "guardsShort_Moving_0", 8);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDSHORT, "guardsShort_Moving_0", 8);

	_animations[ATTACK] = new Animation(_sprite, 0.3f);
	_animations[ATTACK]->addFrameRect(eID::GUARDSHORT, "guardsShort_attack_0", 5);

	_animations[DYING] = new Animation(_sprite, 0.15f);
	_animations[DYING]->addFrameRect(eID::GUARDSHORT, "guardsShort_dying_0", 7);

	_animations[FREE] = new Animation(_sprite, 0.2f);
	_animations[FREE]->addFrameRect(eID::GUARDSHORT, "guardsShort_free_0", 5);

	_animations[THROW] = new Animation(_sprite, 0.15f);
	_animations[THROW]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);

	//_sprite->drawBounding(false);
	_canThrow = true;

}

void GuardShort::Update(float deltatime)
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

void GuardShort::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
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

void GuardShort::onCollisionBegin(CollisionEventArg *)
{
}

void GuardShort::onCollisionEnd(CollisionEventArg *)
{
}

float GuardShort::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

float GuardShort::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() +(_divingSprite->getBounding().right- _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

#pragma region Test
	char str[100];
	sprintf(str, "khoang cach voi aladdin: %f", xAla - x);
	text->setText(str);
#pragma endregion


	return xAla - x;
}

void GuardShort::UpdateStatus(float dt)
{
	if (distanceBetweenAladdin() < 0)
	{
		float distance = -distanceBetweenAladdin();
		if (distance < 200 && distance > 25)
		{
			this->clearStatus();
			this->addStatus(eStatus::ATTACK);
			standing();
			knife->addStatus(eStatus::THROW);
			if(_animations[_status]->getIndex()==2)
				knife->Throw();
			return;
		}
		this->clearStatus();
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();
		if (distance < 25)
		{
			this->clearStatus();
			this->addStatus(eStatus::MOVING_RIGHT);
			movingRight();
		}
	}
	else if (distanceBetweenAladdin() > 0)
	{
		float distance = distanceBetweenAladdin();
		if (distance < 200 && distance > 25)
		{
			this->clearStatus();
			this->addStatus(eStatus::ATTACK);
			knife->addStatus(eStatus::THROW);
			standing();
			return;
		}
		this->clearStatus();
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();
		if (distance < 25)
		{
			this->clearStatus();
			this->addStatus(eStatus::MOVING_LEFT);
			movingLeft();
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

