#include "FallingPlatform.h"

FallingPlatform::FallingPlatform(int posX, int posY, eDirection direction):BaseObject(eID::FALLINGPLATFORM)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::FALLINGPLATFORM);
	_originPosition = Vector2(posX*SCALEFACTOR.x, (posY - 11)*SCALEFACTOR.y);
	setOrigin(ORIGINZERO);
	this->setPosition(posX*SCALEFACTOR.x, (posY-11)*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void FallingPlatform::InIt()
{
	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;
	_listComponent["Gravity"] = new Gravity(Vector2(0, -GRAVITY), movement);

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::SHALLOWED);

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &FallingPlatform::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &FallingPlatform::onCollisionEnd);

	_animations[NORMAL] = new Animation(_sprite, 0.05f);
	_animations[NORMAL]->addFrameRect(eID::FALLINGPLATFORM, "falling_platform_0", "falling_platform_0", "falling_platform_0", NULL);

	_animations[eStatus::DROP] = new Animation(_sprite, 0.05f);
	_animations[DROP]->addFrameRect(eID::FALLINGPLATFORM, "falling_platform_",9);

	_countTime = new StopWatch();
	_drop = false;
}

void FallingPlatform::Update(float deltatime)
{
	_animations[_status]->Update(deltatime);

	UpdateStatus();

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void FallingPlatform::UpdateStatus()
{
	if (_drop)
	{
		if(_countTime->isStopWatch(100))
			if (!isInStatus(DROP))
			{
				setStatus(DROP);				
			}
	}
	if (isInStatus(DROP))
	{
		falling();
		if (_animations[DROP]->getIndex() == 8)
		{
			_animations[DROP]->setIndex(0);
			setPosition(_originPosition);
			setStatus(NORMAL);
			stopFalling();
			_drop = false;
		}
	}
}

void FallingPlatform::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void FallingPlatform::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void FallingPlatform::onCollisionBegin(CollisionEventArg *collision_event)
{
}

void FallingPlatform::onCollisionEnd(CollisionEventArg *)
{
}

float FallingPlatform::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

IComponent* FallingPlatform::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

FallingPlatform::~FallingPlatform()
{
}

void FallingPlatform::falling()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, -FALLING_SPEED));
	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void FallingPlatform::stopFalling()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::SHALLOWED);
}

void FallingPlatform::startCount()
{
	_countTime->restart();
	_drop = true;
}


