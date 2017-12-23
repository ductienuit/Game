#include "Knife.h"
extern vector<BaseObject*> listApple;

Knife::Knife(eStatus status, int posX, int posY, eDirection direction) :BaseEnemy(eID::KNIFE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::KNIFE);
	//_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	_originPosition = Vector2(posX, posY + 100);
	_currentPosition = Vector2(_originPosition.x, _originPosition.y);

	Vector2 v(direction * KNIFE_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Knife::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Knife::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Knife::onCollisionEnd);

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

}

void Knife::Update(float deltatime)
{
	if (isInStatus(DESTROY))
		return;
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
	if (isInStatus(DESTROY))
		return;
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

void Knife::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::APPLETHROW:
	{
		switch (this->getStatus())
		{
		case THROW_LEFT_NEAR:
			setStatus(THROW_RIGHT_NEAR);
			break;
		case THROW_LEFT_FAR:
			setStatus(THROW_RIGHT_NEAR);
			break;
		case THROW_RIGHT_NEAR:
			setStatus(THROW_LEFT_NEAR);
			break;
		case THROW_RIGHT_FAR:
			setStatus(THROW_LEFT_NEAR);
			break;
		default:
			break;
		}

		collision_event->_otherObject->setStatus(DYING);
		return;
	}
	case eID::ALADDIN:
	{
		if (collision_event->_otherObject->isInStatus(eStatus::ATTACK))
		{
			switch (this->getStatus())
			{
			case THROW_LEFT_NEAR:
				setStatus(THROW_RIGHT_NEAR);
				break;
			case THROW_LEFT_FAR:
				setStatus(THROW_RIGHT_NEAR);
				break;
			case THROW_RIGHT_NEAR:
				setStatus(THROW_LEFT_NEAR);
				break;
			case THROW_RIGHT_FAR:
				setStatus(THROW_LEFT_NEAR);
				break;
			default:
				break;
			}
			return;
		}
		/*DK1:Aladdin đang không bị đánh*/
		if (collision_event->_otherObject->isInStatus(eStatus::BEHIT) == false && !isInStatus(DESTROY))
		{

			//Lưu trạng thái trước khi hết bị đánh set lại cái trạng thái cũ
			collision_event->_otherObject->savePreStatus();
			//Set status aladdin bị đánh
			collision_event->_otherObject->setStatus(eStatus::BEHIT);
			InforAladdin::getInstance()->plusHealth(-10);
		}
		break;
	}
	default:
		break;
	}
}

void Knife::onCollisionEnd(CollisionEventArg *)
{
}

float Knife::checkCollision(BaseObject *object, float dt)
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

IComponent* Knife::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

Knife::~Knife()
{
}

void Knife::ThrowLeftFar()
{
	if (count < 70)
	{
		if (count < 30)
		{
			_currentPosition.x -= 5;
			_currentPosition.y += 10;
		}
		else
		{
			_currentPosition.x -= 7;
			_currentPosition.y -= 10;
		};
		count++;
		this->setPosition(_currentPosition.x, _currentPosition.y);
	}
	else
	{
		_currentPosition = _originPosition;
		count = 0;
		this->setPosition(_originPosition.x, _originPosition.y);
	}
}

void Knife::ThrowRightFar()
{
	if(count < 70)
	{
		if (count < 30)
		{
			_currentPosition.x += 5;
			_currentPosition.y += 10;
		}
		else
		{
			_currentPosition.x += 7;
			_currentPosition.y -= 10;
		};
		count++;
		this->setPosition(_currentPosition.x, _currentPosition.y);
	}
	else
	{
		_currentPosition = _originPosition;
		count = 0;
		this->setPosition(_originPosition.x, _originPosition.y);
	}
}

bool Knife::canChangeThrowDirection()
{
	if (count == 0)
		return true;
	return false;
}

void Knife::ThrowLeftNear()
{
	if (count < 50)
	{
		_currentPosition.x -= 7;
		_currentPosition.y -= 3;
		this->setPosition(_currentPosition.x, _currentPosition.y);
		count++;
	}
	else
	{
		_currentPosition = _originPosition;
		this->setPosition(_originPosition.x, _originPosition.y);
		count = 0;
	}
}

void Knife::ThrowRightNear()
{
	if (count < 50)
	{
		_currentPosition.x += 7;
		_currentPosition.y -= 3;
		this->setPosition(_currentPosition.x, _currentPosition.y);
		count++;
	}
	else
	{
		_currentPosition = _originPosition;
		this->setPosition(_originPosition.x, _originPosition.y);
		count = 0;
	}
}