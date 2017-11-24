#include "GuardThin.h"

GuardThin::GuardThin(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDTHIN);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	_divingSprite->setFrameRect(0, 0, 17.0f, 15.0f);
	_divingSprite->setOrigin(Vector2(0.0f, 0.0f));
	Vector2 v(direction * GUARDTHIN_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX,posY,1.0f);
}

void GuardThin::InIt()
{
	//this->setHitpoint(GUARDTHIN_HITPOINT);
	//this->setScore(GUARDTHIN_SCORE);
	//this->_listComponent.insert(pair<string, IComponent*>("Gravity", new Gravity(Vector2(0, -ENEMY_GRAVITY), (Movement*)(this->getComponent("Movement")))));

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardThin::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardThin::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDTHIN,"guardthin_moving_0",8);

	/*_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDTHIN, "run_01", "run_02", "run_03", "run_04", "run_05", "run_06", NULL);

	_animations[DYING] = new Animation(_sprite, 0.15f);
	_animations[DYING]->addFrameRect(eID::GUARDTHIN, "die_01", NULL);*/
}

void GuardThin::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}


void GuardThin::Draw(LPD3DXSPRITE spritehandle, Viewport* viewport)
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

IComponent* GuardThin::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardThin::~GuardThin()
{
}
