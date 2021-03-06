﻿#include "KnifeShort.h"
extern vector<BaseObject*> listApple;


KnifeShort::KnifeShort(eStatus status, int posX, int posY)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::KNIFE);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	_originPosition = Vector2(posX, posY);

	Vector2 v(0 * KNIFE_SHORT_SPEED, 0);
	Vector2 a(0, 0);

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;
	_listComponent["Gravity"] = new Gravity(Vector2(0, -KNIFE_SHORT_GRAVITY), movement);


	this->setStatus(status);
	this->setPosition(posX, -posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
	_isLeft = true;
	InIt();
}

void KnifeShort::InIt()
{

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &KnifeShort::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &KnifeShort::onCollisionEnd);

	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::KNIFE, "donothing",NULL);


	_animations[THROW] = new Animation(_sprite, 0.1f);
	_animations[THROW]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);

}

void KnifeShort::Update(float deltatime)
{
	switch (_status)
	{
		case NORMAL:
		{
			return;
		}
		case THROW:
		{
			if (_isLeft)
			{
				movingLeft();
			}
			else
				movingRight();
		}
	}

	_animations[this->getStatus()]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void KnifeShort::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void KnifeShort::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void KnifeShort::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::APPLETHROW:
	{
		if (_isLeft)
			_isLeft = false;
		else _isLeft = true;
		collision_event->_otherObject->setStatus(DYING);
		break;
	}
	case eID::ALADDIN:
	{
		if (collision_event->_otherObject->isInStatus(eStatus::ATTACK))
		{
			if(_isLeft)
				_isLeft = false;
			else _isLeft = true;
			break;
		}
		else {
			#pragma region Kiểm tra điều kiện aladdin bị trừ máu
			bool isBeAttack = !collision_event->_otherObject->isInStatus(eStatus::BEHIT) && !collision_event->_otherObject->isFlashing();
			/*DK1:Aladdin đang không bị đánh*/
			if (isBeAttack)
			{
				bool isStanding =  collision_event->_otherObject->isInStatus(NORMAL1) || collision_event->_otherObject->isInStatus(FREE);
				InforAladdin::getInstance()->plusHealth(-10);
				if (isStanding)
				{
					//Set status aladdin bị đánh
					collision_event->_otherObject->setStatus(eStatus::BEHIT);
					SoundManager::getInstance()->PlaySound("Resources/Audio/AladdinHurt.wav", 0);
				}
				else
				{
					//Set status aladdin bị đánh
					collision_event->_otherObject->StartFlash();
					SoundManager::getInstance()->PlaySound("Resources/Audio/AladdinHurt.wav", 0);
				}
			}
			#pragma endregion
		}
		break;
	}
	default:
		break;
	}
}

void KnifeShort::onCollisionEnd(CollisionEventArg *)
{
}

float KnifeShort::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision enermy(this) với aladdin(object)
	if (collisionBody->checkCollision(object, dt, true))
		return 0.0f;


	//Apple vs Knife
	for each(auto apple in listApple)
	{
		if (collisionBody->checkCollision(apple, dt, true))
			return 0.0f;
	}

	return 0.0f;
}

IComponent* KnifeShort::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

KnifeShort::~KnifeShort()
{
}

void KnifeShort::Restart(float x, float y, bool isleft)
{
	_isLeft = isleft;
	if (isleft)
		setPosition(x - 15, y);
	else
		setPosition(x + 15, y);
	setStatus(THROW);
}

void KnifeShort::movingLeft()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-KNIFE_SHORT_SPEED, KNIFE_SHORT_JUMP));
	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void KnifeShort::movingRight()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(KNIFE_SHORT_SPEED, KNIFE_SHORT_JUMP));
	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}
