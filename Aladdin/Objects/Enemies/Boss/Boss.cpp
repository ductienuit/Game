#include "Boss.h"


Boss::Boss(eStatus status, int posX, int posY, Aladdin* aladdin) :BaseEnemy(eID::BOSS)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);

	_aladdin = aladdin;

	this->setStatus(status);
	this->setPosition(posX*SCALEBOSSFRONT.x, posY*SCALEBOSSFRONT.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Boss::InIt()
{

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Boss::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Boss::onCollisionEnd);

	_animations[BEHIT] = new Animation(_sprite, 0.1f);
	_animations[BEHIT]->addFrameRect(eID::BOSS, "jafar_1_4", "jafar_1_3", "jafar_1_2", NULL);

	_animations[PULL_LEFT] = new Animation(_sprite, 0.15f);
	_animations[PULL_LEFT]->addFrameRect(eID::BOSS, "jafar_1_", 8);

	_animations[PULL_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[PULL_RIGHT]->addFrameRect(eID::BOSS, "jafar_1_", 8);

	_animations[ATTACK_LEFT] = new Animation(_sprite, 0.15f);
	_animations[ATTACK_LEFT]->addFrameRect(eID::BOSS, "jafar_1_4", "jafar_1_5", "jafar_1_6", "jafar_1_7", NULL);

	_animations[ATTACK_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[ATTACK_RIGHT]->addFrameRect(eID::BOSS, "jafar_1_4", "jafar_1_5", "jafar_1_6", "jafar_1_7", NULL);

	_animations[THROW_RIGHT_FAR] = new Animation(_sprite, 0.2f);
	_animations[THROW_RIGHT_FAR]->addFrameRect(eID::BOSS, "jafar_1_4", "jafar_1_5", "jafar_1_6", "jafar_1_7", NULL);

	_animations[THROW_LEFT_FAR] = new Animation(_sprite, 0.15f);
	_animations[THROW_LEFT_FAR]->addFrameRect(eID::BOSS, "jafar_1_4", "jafar_1_5", "jafar_1_6", "jafar_1_7", NULL);

	_animations[DYING] = new Animation(_sprite, 0.1f);
	_animations[DYING]->addFrameRect(eID::BOSS, "destroy_enermy_00_0", 10);

	_hitpoint = 50;
	_frequency = new StopWatch();
}

void Boss::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	this->UpdateStatus(deltatime);

	for (int i = 0; i < _listStar.size(); i++)
	{
		_listStar[i]->Update(deltatime);
	}

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void Boss::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);

	for (int i = 0; i < _listStar.size(); i++)
	{
		if (_listStar[i]->isInStatus(DESTROY))
		{
			_listStar[i]->Release();
			delete  _listStar[i];
			_listStar.erase(_listStar.begin() + i);
		}
		else
			_listStar[i]->Draw(spritehandle, viewport);
	}
}

void Boss::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Boss::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		if (collision_event->_otherObject->isInStatus(ATTACK))
		{
			//mạng sống còn 1 và bức ảnh ATTACK của aladdin bằng 1
			if (collision_event->_otherObject->getIndex() == 4 && _hitpoint >= 1)
			{
				_hitpoint = 0;
				this->setStatus(eStatus::DYING);
			}
			break;

		}
		break;
	}
	}
}

void Boss::onCollisionEnd(CollisionEventArg *)
{
}

float Boss::checkCollision(BaseObject *object, float dt)
{
	//if (object == this)
	//	return 0.0f;
	//auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	////Check collision enermy(this) với aladdin(object)
	///*Ưu tiên check Boss trước, sau đó đến knife*/
	//collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

void Boss::UpdateStatus(float dt)
{
	eStatus status = getStatus();
	switch (status)
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
		case eStatus::BEHIT:
		{
			if (_animations[BEHIT]->getIndex() >= 2)
			{
				_animations[BEHIT]->setIndex(0);
				if (_hitpoint <= 16)
				{
					isVersion2 = true;
					this->setStatus(THROW_LEFT_FAR);
					return;
				}
				this->setStatus(PULL_LEFT);
			}
		}
		case eStatus::PULL_LEFT:
		{
			if (_animations[PULL_LEFT]->getIndex() >= 7)
			{
				_animations[PULL_LEFT]->Stop();
			}
			else _animations[PULL_LEFT]->Start();

			if (_frequency->isStopWatch(90))
			{
				_listStar.push_back(new Star(getPositionX() - 10, getPositionY(), true, _aladdin));
				_frequency->restart();
			}
			// new star
			break;
		}
		case eStatus::PULL_RIGHT:
		{
			if (_animations[PULL_RIGHT]->getIndex() >= 7)
			{
				_animations[PULL_RIGHT]->Stop();
			}
			else _animations[PULL_RIGHT]->Start();


			if (_frequency->isStopWatch(90))
			{
				_listStar.push_back(new Star(getPositionX() + 10, getPositionY(), false, _aladdin));

				_frequency->restart();
			}
			// new star
			break;
		}
	}




	Vector2 distance = distanceBetweenAladdin();
	if (isVersion2)
	{
		//Aladdin bên trái enermy
		if (distance.x <= 0)
		{
			distance.x = (-1)*distance.x;
			if (distance.x < 90)
			{
				_aladdin->Stop(true);
				if (!_aladdin->isInStatus(BEHIT))
				{
					_aladdin->setStatus(BEHIT);
					InforAladdin::getInstance()->plusHealth(-10);
				}
			}
			else
			{
				setStatus(THROW_LEFT_FAR);
				setScaleX(-SCALECHARACTER.x);
			}
		}
		else
		{
			if (distance.x < 90)
			{
				if (!_aladdin->isInStatus(BEHIT))
				{
					_aladdin->setStatus(BEHIT);
					InforAladdin::getInstance()->plusHealth(-10);
				}
			}
			else
			{
				setStatus(THROW_RIGHT_FAR);
				setScaleX(SCALECHARACTER.x);
			}
		}
	}
	else
	{
		//Aladdin bên trái enermy
		if (distance.x <= 0)
		{
			distance.x = (-1)*distance.x;
			if (distance.x < 90)
			{
				setStatus(ATTACK_LEFT);
				setScaleX(-SCALECHARACTER.x);
				_aladdin->Stop(true);
				/*if (!_aladdin->isInStatus(BEHIT))
				{
					_aladdin->setStatus(BEHIT);
					InforAladdin::getInstance()->plusHealth(-10);
				}*/
			}
			else
			{
				setStatus(PULL_LEFT);
				setScaleX(-SCALECHARACTER.x);
			}
		}
		else
		{
			if (distance.x < 90)
			{
				setStatus(ATTACK_RIGHT);
				setScaleX(SCALECHARACTER.x);
				_aladdin->Stop(true);
				/*if (!_aladdin->isInStatus(BEHIT))
				{
					_aladdin->setStatus(BEHIT);
					InforAladdin::getInstance()->plusHealth(-10);
				}*/
			}
			else
			{
				setStatus(PULL_RIGHT);
				setScaleX(SCALECHARACTER.x);
			}
		}
	}
}

Boss::~Boss()
{
}

Vector2 Boss::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX();
	float x = this->getPositionX();

	float yAla = _divingSprite->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x, yAla - y);
}