﻿#include "Knife.h"

Knife::Knife(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::KNIFE);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	_originPosition = Vector2(posX-120, posY+60);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * KNIFE_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
}

void Knife::InIt()
{

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Knife::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Knife::onCollisionEnd);

	_animations[THROW] = new Animation(_sprite, 0.1f);
	_animations[THROW]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);

}
void Knife::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void Knife::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void Knife::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Knife::onCollisionBegin(CollisionEventArg *)
{
}

void Knife::onCollisionEnd(CollisionEventArg *)
{
}

float Knife::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

IComponent* Knife::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

Knife::~Knife()
{
}

void Knife::movingLeft(float x, float y)
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-KNIFE_SPEED, -KNIFE_JUMP));
	x = x - 80;
	y = y + 60;
	this->setPosition(x, y);
}

void Knife::movingRight(float x, float y)
{
	_sprite->setScaleX(1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(KNIFE_SPEED, -KNIFE_JUMP));

	x = x + 80;
	y = y + 60;
	this->setPosition(x, y);
}
