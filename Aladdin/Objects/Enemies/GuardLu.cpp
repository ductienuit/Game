#include "GuardLu.h"

GuardLu::GuardLu(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDLU);


	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDLU_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
}

void GuardLu::InIt()
{

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardLu::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardLu::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDLU, "guardsLu_Moving_", 12);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDLU, "guardsLu_Moving_", 12);

	_animations[ATTACK] = new Animation(_sprite, 0.3f);
	_animations[ATTACK]->addFrameRect(eID::GUARDLU, "guardsLu_Attack_", 4);

	_animations[FREE] = new Animation(_sprite, 0.2f);
	_animations[FREE]->addFrameRect(eID::GUARDLU, "guardsLu_Being_", 6);

	//_sprite->drawBounding(false);

}

void GuardLu::Update(float deltatime)
{
	this->UpdateStatus(deltatime);

	_animations[this->getStatus()]->Update(deltatime);
	// update component ?? sau cùng ?? s?a bên trên sau ?ó nó c?p nh?t ?úng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void GuardLu::Draw(LPD3DXSPRITE spritehandle, Viewport* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void GuardLu::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void GuardLu::onCollisionBegin(CollisionEventArg *)
{
}

void GuardLu::onCollisionEnd(CollisionEventArg *)
{
}

float GuardLu::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

float GuardLu::distanceBetweenAladdin()
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

void GuardLu::UpdateStatus(float dt)
{
	if (distanceBetweenAladdin() < 0)
	{
		float distance = -distanceBetweenAladdin();
		if (distance < 25 && distance > 2.5)
		{
			this->clearStatus();
			this->addStatus(eStatus::ATTACK);
			standing();
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
		if (distance < 70 && distance > 10)
		{
			this->clearStatus();
			this->addStatus(eStatus::ATTACK);
			standing();
			return;
		}
		this->clearStatus();
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();
		if (distance < 50)
		{
			this->clearStatus();
			this->addStatus(eStatus::MOVING_LEFT);
			movingLeft();
		}
	}
}

IComponent* GuardLu::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardLu::~GuardLu()
{
}

void GuardLu::movingLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-GUARDLU_SPEED, move->getVelocity().y));
}

void GuardLu::movingRight()
{
	_sprite->setScaleX(1.6);

	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(GUARDLU_SPEED, move->getVelocity().y));
}

void GuardLu::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}

