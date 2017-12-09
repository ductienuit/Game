#include "Knife.h"

Knife::Knife(eStatus status, int posX, int posY, eDirection direction) :BaseEnemy(eID::KNIFE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::KNIFE);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	_originPosition = Vector2(posX, posY + 100);
	_currentPosition = Vector2(_originPosition.x, _originPosition.y);

	//_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * KNIFE_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
}

void Knife::InIt()
{
	//auto move = (Movement*)this->_listComponent["Movement"];
	//move->setVelocity(Vector2(move->getVelocity().x, KNIFE_JUMP));

	//auto gravity = new Gravity(Vector2(0, -KNIFE_GRAVITY), move);
	//gravity->setStatus(eGravityStatus::FALLING__DOWN);
	//_listComponent["Gravity"] = gravity;

	/*auto movement = new Movement(Vector2(9.8, 9.8), Vector2(20, 10), _sprite);
	_listComponent["Movement"] = movement;

	auto gravity = new Gravity(Vector2(0,-KNIFE_GRAVITY),movement);
	gravity->setStatus(eGravityStatus::FALLING__DOWN);*/
	//_listComponent["Gravity"] = gravity;

	/*auto sinmovement = new SinMovement(Vector2(300, 0), 1.5, _sprite);*/

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Knife::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Knife::onCollisionEnd);

	_animations[THROW] = new Animation(_sprite, 0.1f);
	_animations[THROW]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);


	_animations[THROW_LEFT_NEAR] = new Animation(_sprite, 0.1f);
	_animations[THROW_LEFT_NEAR]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);

	_animations[THROW_RIGHT_NEAR] = new Animation(_sprite, 0.1f);
	_animations[THROW_RIGHT_NEAR]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);
	
	_animations[THROW_LEFT_FAR] = new Animation(_sprite, 0.1f);
	_animations[THROW_LEFT_FAR]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);

	_animations[THROW_RIGHT_FAR] = new Animation(_sprite, 0.1f);
	_animations[THROW_RIGHT_FAR]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);
	//_sprite->drawBounding(false);
	//_sprite->setOrigin(Vector2(0, 0));

}
void Knife::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	
	switch (this->getStatus())
	{
	case THROW_LEFT_NEAR:
		ThrowLeftNear();
		break;
	case THROW_LEFT_FAR:
		ThrowLeftFar();
		break;
	case THROW_RIGHT_NEAR:
		ThrowRightNear();
		break;
	case THROW_RIGHT_FAR:
		ThrowRightFar();
		break;
	default:
		break;
	}
	

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


void Knife::ThrowLeftFar()
{
	if (_animations[_status]->getIndex() != 6)
	{
		if (_animations[_status]->getIndex() < 3)
		{
			_currentPosition.x -= 15;
			_currentPosition.y += 20;
		}
		else
		{
			_currentPosition.x -= 15;
			_currentPosition.y -= 20;
		}
		this->setPosition(_currentPosition.x, _currentPosition.y);
	}
	else
	{
		_currentPosition = _originPosition;
		this->setPosition(_originPosition.x, _originPosition.y);
	}
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

void Knife::ThrowRightFar()
{
	if (_animations[_status]->getIndex() != 6)
	{
		if (_animations[_status]->getIndex() < 3)
		{
			_currentPosition.x += 15;
			_currentPosition.y += 20;
		}
		else
		{
			_currentPosition.x += 15;
			_currentPosition.y -= 20;
		};
		this->setPosition(_currentPosition.x, _currentPosition.y);
	}
	else
	{
		_currentPosition = _originPosition;
		this->setPosition(_originPosition.x, _originPosition.y);
	}
}

bool Knife::canChangeThrowDirection()
{
	if (_animations[_status]->getIndex() == 6)
		return true;
	return false;
}

void Knife::ThrowLeftNear()
{
	if (_animations[_status]->getIndex() != 6)
	{
		_currentPosition.x -= 15;
		_currentPosition.y -= 10;
		this->setPosition(_currentPosition.x, _currentPosition.y);
	}
	else
	{
		_currentPosition = _originPosition;
		this->setPosition(_originPosition.x, _originPosition.y);
	}
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

void Knife::ThrowRightNear()
{
	if (_animations[_status]->getIndex() != 6)
	{
		_currentPosition.x += 15;
		_currentPosition.y -= 10;
		this->setPosition(_currentPosition.x, _currentPosition.y);
	}
	else
	{
		_currentPosition = _originPosition;
		this->setPosition(_originPosition.x, _originPosition.y);
	}
}

float Knife::distanceBetweenAladdin()
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
