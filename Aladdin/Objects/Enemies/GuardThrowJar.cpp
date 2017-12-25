#include "GuardThrowJar.h"

GuardThrowJar::GuardThrowJar(eStatus status, int posX, int posY, int distancebroken, BaseObject* aladdin) :BaseEnemy(eID::GUARDTHROWJAR)
{
	_distancebroken = distancebroken;
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDTHROWJAR);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_aladdin = aladdin;

	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	text = new Text("Arial", "", 10, 25);

	//new Jar(eStatus::DROP, posX, posY, eDirection::BOTTOM);

	_score = 10;
	InIt();
}

void GuardThrowJar::InIt()
{
	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardThrowJar::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardThrowJar::onCollisionEnd);

	_animations[FREE] = new Animation(_sprite, 0.2f);
	_animations[FREE]->addFrameRect(eID::GUARDTHROWJAR, "throwjar_12", "throwjar_12", NULL);

	_animations[THROW] = new Animation(_sprite, 0.13f);
	_animations[THROW]->addFrameRect(eID::GUARDTHROWJAR, "throwjar_", 10);

	_animations[DYING] = new Animation(_sprite, 0.1f);
	_animations[DYING]->addFrameRect(eID::GUARDTHROWJAR, "destroy_enermy_", 10);

	_sprite->drawBounding(false);
	_canDrop = true;
}

void GuardThrowJar::Update(float deltatime)
{
	eStatus temp = this->getStatus();
	_animations[temp]->Update(deltatime);

	this->UpdateStatus(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}

	//Jar là cái lu
	for (int i = 0; i < _listJar.size(); i++)
	{
		_listJar[i]->Update(deltatime);
	}
}

void GuardThrowJar::UpdateStatus(float dt)
{
	switch (this->getStatus())
	{
		case eStatus::DESTROY:
			return;
		case eStatus::DYING:
		{
			standing();
			if (_animations[DYING]->getIndex() == 9)
			{
				_animations[DYING]->setIndex(0);
				//SOUNDDDDDD
				SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
				//Nhạc khi object bị destroy
				this->setStatus(DESTROY);
				//score+=10;
			}
			return;
		}
	}

	if (distanceBetweenAladdin().y > 0)
		return;
	float distance = -distanceBetweenAladdin().x;

	if (distance <= 80)
	{
		this->setStatus(eStatus::THROW);
		if (_animations[_status]->getIndex() == 6)
		{
			_animations[this->getStatus()]->setIndex(0);
			setStatus(FREE);
			_listJar.push_back(new Jar(eStatus::DROP, this->getPositionX(), this->getPositionY(),_distancebroken));
		}
		return;
	}
	else if (distance > 80)
	{
		if (isInStatus(THROW) && _animations[this->getStatus()]->getIndex() >= 9)
		{
			_animations[this->getStatus()]->setIndex(0);
			removeStatus(eStatus::THROW);
			this->addStatus(FREE);
		}
		return;
	}
	this->clearStatus();
	this->addStatus(FREE);
	return;
}

void GuardThrowJar::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	for (int i = 0; i < _listJar.size(); i++)
	{
		if (_listJar[i]->isInStatus(DESTROY))
		{
			_listJar[i]->Release();
			delete _listJar[i];
			_listJar.erase(_listJar.begin() + i);
		}
		else
			_listJar[i]->Draw(spritehandle, viewport);
	}
}

void GuardThrowJar::Release()
{
	for (int i = 0; i < _listJar.size(); i++)
	{
		_listJar[i]->Release();
		delete _listJar[i];
	}
	_listJar.clear();

	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void GuardThrowJar::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		if (collision_event->_otherObject->isInStatus(ATTACK))
		{
			//mạng sống còn 1 và bức ảnh ATTACK của aladdin bằng 1
			if (collision_event->_otherObject->getIndex() == 3)
			{
				this->setStatus(eStatus::DYING);
			}
			break;
		}
		break;
	}
	default:
		break;
	}
}

void GuardThrowJar::onCollisionEnd(CollisionEventArg *)
{
}

float GuardThrowJar::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	//Check collision enermy(this) với aladdin(object)
	/*Ưu tiên check GuardThrowJar trước, sau đó đến Jar*/
	if (!collisionBody->checkCollision(object, dt, true))
	{
		for (int i = 0; i < _listJar.size(); i++)
		{
			_listJar[i]->checkCollision(object, dt);
		}
	}
	return 0.0f;
}

Vector2 GuardThrowJar::distanceBetweenAladdin()
{
	float xAla = _aladdin->getPositionX() + (_aladdin->getBounding().right - _aladdin->getBounding().left) / 2;
	float x = this->getPositionX();

	float yAla = _aladdin->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x,yAla-y);
}

IComponent* GuardThrowJar::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardThrowJar::~GuardThrowJar()
{
}

void GuardThrowJar::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}
