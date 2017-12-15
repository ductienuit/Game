#include "BulletCamel.h"

BulletCamel::BulletCamel(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BULLETCAMEL);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	_originPosition = Vector2(posX - 120, posY + 60);
	_currentPosition = Vector2(_originPosition.x, _originPosition.y);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * BULLETCAMEL_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	//setScale(SCALEAPPLE);
	text = new Text("Arial", "", 10, 25);
}

void BulletCamel::InIt()
{

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &BulletCamel::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &BulletCamel::onCollisionEnd);

	_animations[THROW] = new Animation(_sprite, 0.5f);
	_animations[THROW]->addFrameRect(eID::BULLETCAMEL, "bullet_camel_1", "bullet_camel_1", "bullet_camel_1", "bullet_camel_1", NULL);

}
void BulletCamel::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void BulletCamel::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void BulletCamel::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void BulletCamel::onCollisionBegin(CollisionEventArg *)
{
}

void BulletCamel::onCollisionEnd(CollisionEventArg *)
{
}

float BulletCamel::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

IComponent* BulletCamel::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

void BulletCamel::Shoot(float x, float y)
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(BULLETCAMEL_SPEED * 2, -BULLETCAMEL_JUMP));

	x = x + 100;
	y = y + 45;
	this->setPosition(x, y);
}

BulletCamel::~BulletCamel()
{
}