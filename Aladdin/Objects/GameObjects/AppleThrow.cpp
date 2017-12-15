#include "AppleThrow.h"

AppleThrow::AppleThrow(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::APPLETHROW);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	_originPosition = Vector2(posX - 120, posY + 60);
	_currentPosition = Vector2(_originPosition.x, _originPosition.y);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * APPLETHROW_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	setScale(SCALEAPPLE);
	text = new Text("Arial", "", 10, 25);
}

void AppleThrow::InIt()
{

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &AppleThrow::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &AppleThrow::onCollisionEnd);

	_animations[THROW] = new Animation(_sprite, 0.5f);
	_animations[THROW]->addFrameRect(eID::APPLETHROW, "apple_00", "apple_00", "apple_00", NULL);

	_animations[THROW_LEFT] = new Animation(_sprite, 0.5f);
	_animations[THROW_LEFT]->addFrameRect(eID::APPLETHROW, "apple_00", "apple_00", "apple_00", NULL);

	_animations[THROW_RIGHT] = new Animation(_sprite, 0.5f);
	_animations[THROW_RIGHT]->addFrameRect(eID::APPLETHROW, "apple_00", "apple_00", "apple_00", NULL);

}
void AppleThrow::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	switch (this->getStatus())
	{
	case THROW_RIGHT:
		throwRight();
		break;
	case THROW_LEFT:
		throwLeft();
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

void AppleThrow::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void AppleThrow::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void AppleThrow::onCollisionBegin(CollisionEventArg *)
{
}

void AppleThrow::onCollisionEnd(CollisionEventArg *)
{
}

float AppleThrow::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

IComponent* AppleThrow::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

AppleThrow::~AppleThrow()
{
}

void AppleThrow::movingLeft(float x, float y)
{
	this->setStatus(eStatus::THROW_LEFT);
	count = 0;
	_currentPosition.x = x - 60;
	_currentPosition.y = y + 90;
}

void AppleThrow::movingRight(float x, float y)
{
	this->setStatus(eStatus::THROW_RIGHT);
	count = 0;
	_currentPosition.x = x + 60;
	_currentPosition.y = y + 90;
}

void AppleThrow::throwLeft()
{
	if (count < 25)
	{
		_currentPosition.x -= 4;
		_currentPosition.y += 2;
	}
	else
	{
		_currentPosition.x -= 8;
		_currentPosition.y -= 4;
	};
	count++;
	this->setPosition(_currentPosition.x, _currentPosition.y);
}

void AppleThrow::throwRight()
{
	if (count < 25)
	{
		_currentPosition.x += 4;
		_currentPosition.y += 2;
	}
	else
	{
		_currentPosition.x += 8;
		_currentPosition.y -= 4;
	};
	count++;
	this->setPosition(_currentPosition.x, _currentPosition.y);
}
