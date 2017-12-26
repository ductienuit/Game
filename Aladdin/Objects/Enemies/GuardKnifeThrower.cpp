#include "GuardKnifeThrower.h"

GuardKnifeThrower::GuardKnifeThrower(eStatus status, int posX, int posY, BaseObject* aladdin) :BaseEnemy(eID::KNIFETHROWER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::KNIFETHROWER);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	_aladdin = aladdin;
	Vector2 v(0 * KNIFETHROWER_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void GuardKnifeThrower::InIt()
{
	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	knife = new Knife(eStatus::THROW_LEFT_FAR, this->getPositionX(), this->getPositionY(), eDirection::NONE);
	knife->InIt();

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardKnifeThrower::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardKnifeThrower::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.11f);
	_animations[MOVING_LEFT]->addFrameRect(eID::KNIFETHROWER, "knifeThrowers_attack_0", 10);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.11f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::KNIFETHROWER, "knifeThrowers_attack_0", 10);

	_animations[DYING] = new Animation(_sprite, 0.05f);
	_animations[DYING]->addFrameRect(eID::GUARDLU, "destroy_enermy_", 10);

	_sprite->drawBounding(false);
	_canThrow = true;

	_hitpoint = 2;// 1 lần đánh
	_score = 10; //Số điểm được mỗi lần giết enermy
}

void GuardKnifeThrower::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);
	knife->Update(deltatime);

	this->UpdateStatus(deltatime);	

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{

		it->second->Update(deltatime);
	}
}

void GuardKnifeThrower::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	knife->Draw(spritehandle, viewport);
}

void GuardKnifeThrower::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
	knife->Release();
}

void GuardKnifeThrower::onCollisionBegin(CollisionEventArg *collision_event)
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
				//InforAladdin::getInstance()->plusScore(10);
				//SOUNDDDDDD
				SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
			}
			break;
		}
		break;
	}
	default:
		break;
	}
}

void GuardKnifeThrower::onCollisionEnd(CollisionEventArg *)
{
}

float GuardKnifeThrower::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	if (isInStatus(DYING))
	{
		return 0.0f;
	}
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	//Check collision enermy(this) với aladdin(object)
	/*Ưu tiên check GuardKnifeThrower trước, sau đó đến knife*/
	if (!collisionBody->checkCollision(object, dt, true))
	{
		
		knife->checkCollision(object, dt);
	}
	return 0.0f;
}

float GuardKnifeThrower::distanceBetweenAladdin()
{
	float xAla = _aladdin->getPositionX() + (_aladdin->getBounding().right - _aladdin->getBounding().left) / 2;
	float x = this->getPositionX();
	return xAla - x;
}

void GuardKnifeThrower::UpdateStatus(float dt)
{
	switch (this->getStatus())
	{
	case eStatus::DESTROY:
		return;
	case eStatus::DYING:
	{
		if (_animations[DYING]->getIndex() == 9)
		{
			_animations[DYING]->setIndex(0);
			this->setStatus(DESTROY);
		}
		return;
	}
	}


	if (distanceBetweenAladdin() < 0)
	{
		this->clearStatus();
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();

		if (knife->canChangeThrowDirection())
		{
			if (-distanceBetweenAladdin() < 300)
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				knife->setStatus(eStatus::THROW_LEFT_NEAR);
			}


			if (-distanceBetweenAladdin() > 300)
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				knife->setStatus(eStatus::THROW_LEFT_FAR);
			}
		}
		return;
	}
	else
	{
		this->clearStatus();
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();

		if (knife->canChangeThrowDirection())
		{
			if (distanceBetweenAladdin() < 300)
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				knife->setStatus(eStatus::THROW_RIGHT_NEAR);
			}

			
			if(distanceBetweenAladdin() > 300)
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				knife->setStatus(eStatus::THROW_RIGHT_FAR);
			}
		}
		return;
	}
}

IComponent* GuardKnifeThrower::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardKnifeThrower::~GuardKnifeThrower()
{
}

void GuardKnifeThrower::movingLeft()
{
	_sprite->setScaleX(-1.6);
}

void GuardKnifeThrower::movingRight()
{
	_sprite->setScaleX(1.6);
}

