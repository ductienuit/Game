#include "GuardThin.h"

GuardThin::GuardThin(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDTHIN);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDTHIN_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX,posY,1.0f);
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

	_sprite->setOrigin(Vector2(0.5, 0));
	
}

void GuardThin::Update(float deltatime)
{
	this->UpdateStatus(deltatime);

	_animations[this->getStatus()]->Update(deltatime);

	float x = this->getPositionX();
	float y = this->getPositionY();
	//update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	//for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	//{
	//	it->second->Update(deltatime);
	//}
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

void GuardThin::onCollisionBegin(CollisionEventArg *)
{
}

void GuardThin::onCollisionEnd(CollisionEventArg *)
{
}

float GuardThin::checkCollision(BaseObject *, float)
{
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
