#include "AppleThrow.h"
extern vector<BaseObject*> listActive;

AppleThrow::AppleThrow(int posX, int posY,bool isLeft):BaseObject(eID::APPLETHROW)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::APPLETHROW);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	_originPosition = Vector2(posX, posY+100);

	Vector2 v(0, 0);
	Vector2 a(0, 0);

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;
	_listComponent["Gravity"] = new Gravity(Vector2(0, -APPLE_GRAVITY), movement);

	setScale(SCALEONE);
	this->setStatus(THROW);
	text = new Text("Arial", "", 10, 25);
	_isLeft = isLeft;
	if (isLeft)
		setPosition(posX - 15, posY+100);
	else
		setPosition(posX + 15, posY+100);
	InIt();
}

void AppleThrow::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &AppleThrow::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &AppleThrow::onCollisionEnd);

	_animations[THROW] = new Animation(_sprite, 0.05f);
	_animations[THROW]->addFrameRect(eID::APPLETHROW, "apple_",4);

	_animations[DYING] = new Animation(_sprite, 0.05f);
	_animations[DYING]->addFrameRect(eID::APPLETHROW, "apple_destroy_",5);
}

void AppleThrow::Update(float deltatime)
{

	switch (this->getStatus())
	{
	case DESTROY:
		return;
	case THROW:
	{
		float x = this->getPositionX();
		float y = this->getPositionY();

		if (_isLeft)
		{
			movingLeft();
		}
		else
			movingRight();
		break;
	}
	case DYING:
	{
		standing();
		if (_animations[DYING]->getIndex() >= 4)
		{
			_animations[DYING]->setIndex(0);
			this->setStatus(DESTROY);
			return;
		}
		break;
	}
	break;
	}

	_animations[_status]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void AppleThrow::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[_status]->Draw(spritehandle, viewport);
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

void AppleThrow::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID temp = collision_event->_otherObject->getId();

	standing();
	if (temp == LAND || temp ==CAMEL || temp==FALLINGPLATFORM)
	{
		if(!isInStatus(DESTROY))
			setStatus(DYING);
		return;
	}
	collision_event->_otherObject->setStatus(DYING);

}

void AppleThrow::onCollisionEnd(CollisionEventArg *)
{
}

float AppleThrow::checkCollision(BaseObject *object, float dt)
{
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	if (isInStatus(DYING) || isInStatus(DESTROY))
		return 0.0f;
	for each(auto object in listActive)
	{
		eID temp = object->getId();
		float yapple = getPositionY();
		float yobject = object->getPositionY();
		if (yobject > yapple)
			continue;
		if (temp == APPLEEAT || temp == COINEAT || temp == HEARTEAT || temp == RESTARTPOINT ||
			temp == ALADDIN || object->getStatus() == DESTROY || temp == FIRE ||temp==BOOM)
			continue;

		if (collisionBody->checkCollision(object, dt, true))
			break;
	}
	return 0.0f;
}

IComponent* AppleThrow::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

AppleThrow::~AppleThrow()
{
}

void AppleThrow::movingLeft()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-APPLE_SPEED, move->getVelocity().y));
}

void AppleThrow::movingRight()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(APPLE_SPEED, move->getVelocity().y));
}

void AppleThrow::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}
