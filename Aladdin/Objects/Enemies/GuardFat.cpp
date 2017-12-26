#include "GuardFat.h"
extern vector<BaseObject*> listFireActive;

GuardFat::GuardFat(eStatus status, int posX, int posY, BaseObject* aladdin, int minMove, int maxMove) :BaseEnemy(eID::GUARDFAT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDFAT);
	_aladdin = aladdin;
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	Vector2 v(0, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	_minMove = getPositionX() - 250; //- minMove;
	_maxMove = getPositionX() + 200; //+ maxMove;
	InIt();
}

void GuardFat::InIt()
{
	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardFat::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardFat::onCollisionEnd);

	_animations[NORMAL] = new Animation(_sprite, 0.15f);
	_animations[NORMAL]->addFrameRect(eID::GUARDFAT, "guardsFat_Near_0", 6);

	_animations[FREE] = new Animation(_sprite, 0.15f);
	_animations[FREE]->addFrameRect(eID::GUARDFAT, "guardsFat_Near_0", 6);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDFAT, "guardsFat_Moving_0", 8);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDFAT, "guardsFat_Moving_0", 8);

	_animations[ATTACK] = new Animation(_sprite, 0.15f);
	_animations[ATTACK]->addFrameRect(eID::GUARDFAT, "guardsFat_AttackTwo_0", 5);

	_animations[SITTING_DOWN| ATTACK] = new Animation(_sprite, 0.15f);
	_animations[SITTING_DOWN | ATTACK]->addFrameRect(eID::GUARDFAT, "guardsFat_AttackOne_0", 6);

	_animations[BEHIT] = new Animation(_sprite, 0.1f);
	_animations[BEHIT]->addFrameRect(eID::GUARDFAT, "guardsFat_beingAttack_0", 6);

	_animations[DYING] = new Animation(_sprite, 0.1f);
	_animations[DYING]->addFrameRect(eID::GUARDFAT, "destroy_enermy_00_0", 10);

	//guardsFat_burn_0
	//bị bỏng
	_animations[eStatus::STOPWALK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::STOPWALK]->addFrameRect(eID::GUARDFAT, "guardsFat_burn_0", 9);

	_sprite->setOrigin(Vector2(0.5, 0));

	_hitpoint = 4;//Số lần đánh
	_score = 10; //Số điểm được mỗi lần giết enermy
}

void GuardFat::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	this->UpdateStatus(deltatime);

	//update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void GuardFat::UpdateStatus(float dt)
{
	float xAla = _aladdin->getPositionX() + (_aladdin->getBounding().right - _aladdin->getBounding().left) / 2;
	switch (this->getStatus())
	{
	case eStatus::DESTROY:
		return;
	case eStatus::BEHIT:
	{
		standing();
		if (_animations[BEHIT]->getIndex() == 5)
		{
			_animations[BEHIT]->setIndex(0);
			removeStatus(BEHIT);
			setStatus(ATTACK);
			if (_hitpoint <= 0)
			{
				//InforAladdin::getInstance()->plusScore(10);
				//SOUNDDDDDD
				SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
				this->setStatus(DYING);
			}
		}
		return;
	}
	case eStatus::DYING:
	{
		if (_animations[DYING]->getIndex() == 9)
		{
			_animations[DYING]->setIndex(0);

			//Nhạc khi object bị destroy
			this->setStatus(DESTROY);
		}
		return;
	}
	}

	this->clearStatus();
	if (_minMove < this->getPositionX() && this->getPositionX() < _maxMove)
	{
		if (distanceBetweenAladdin().x < 0)
		{
			float distance = -distanceBetweenAladdin().x;
			if (distance > 300)
			{
				this->setStatus(eStatus::FREE);
				standing();
			}
			else if (50 < distance && distance < 300)
			{
				this->addStatus(eStatus::MOVING_LEFT);
				movingLeft();
			}
			else if (distance <= 50)
			{
				_sprite->setScaleX(-1.6);
				this->setStatus(eStatus::ATTACK);
				standing();
			}
		}
		else if (distanceBetweenAladdin().x > 0)
		{
			float distance = distanceBetweenAladdin().x;
			if (distance > 300)
			{

				this->setStatus(eStatus::FREE);
				standing();
			}
			else if (50 < distance && distance < 300)
			{
				this->addStatus(eStatus::MOVING_RIGHT);
				movingRight();
			}
			else if (distance <= 50)
			{
				_sprite->setScaleX(1.6);
				this->setStatus(eStatus::ATTACK);
				standing();
			}
		}
	}
	else if ((_minMove > this->getPositionX()) && xAla < _minMove)
	{
		this->addStatus(eStatus::ATTACK);
		standing();
	}
	else if (distanceBetweenAladdin().x > 0 && xAla > _minMove && this->getPositionX() < _maxMove)
	{
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();
	}
	else if ((this->getPositionX() > _maxMove) && xAla > _maxMove)
	{
		this->addStatus(eStatus::ATTACK);
		standing();
	}
	else if (distanceBetweenAladdin().x < 0 && xAla < _maxMove)
	{
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();
	}
}

void GuardFat::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void GuardFat::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void GuardFat::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
		case eID::ALADDIN:
		{
			if (collision_event->_otherObject->isInStatus(SITTING_DOWN))
			{
				this->setStatus(eStatus(SITTING_DOWN | ATTACK));
			}

			if (collision_event->_otherObject->isInStatus(ATTACK))
			{
				//mạng sống còn 1 và bức ảnh ATTACK của aladdin bằng 1
				if (collision_event->_otherObject->getIndex() == 2 && _hitpoint >= 1)
				{
					_hitpoint -= 2;
					this->setStatus(eStatus::BEHIT);
				}
				break;
			}
			else
			{					
				bool isBeAttack = !collision_event->_otherObject->isInStatus(eStatus::BEHIT) && !collision_event->_otherObject->isFlashing();
				if (isBeAttack)
				{
					
					if (_animations[ATTACK]->getIndex() == 4)
					{
						//âm thanh
						SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
						InforAladdin::getInstance()->plusHealth(-10);

						bool isStanding =  collision_event->_otherObject->isInStatus(NORMAL1) || collision_event->_otherObject->isInStatus(FREE);
						if (isStanding)
						{
							//Set status aladdin bị đánh
							collision_event->_otherObject->setStatus(eStatus::BEHIT);
						}
						else
						{
							//Set status aladdin bị đánh
							collision_event->_otherObject->StartFlash();
						}
					}
				}
				break;
			}

			break;
		}
		case eID::FIRE:
		{
			setStatus(STOPWALK);
			break;
		}
	}
}

void GuardFat::onCollisionEnd(CollisionEventArg *)
{
//	setStatus(FREE);
}

float GuardFat::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	if (isInStatus(DYING))
	{
		return 0.0f;
	}
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	if(!isInStatus(ATTACK))
		//Check guard Fat với lửa
		for each(auto fire in listFireActive)
		{
			collisionBody->checkCollision(fire, dt,true);
		}


	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt, true);

	return 0.0f;
}

RECT GuardFat::getBounding()
{
	RECT r = BaseObject::getBounding();
	//if (isInStatus(FREE))
	//{
	//	float distancex = abs(r.right - r.left) / 3.0f;
	//	r.left = r.left + distancex;
	//	r.right = r.right - distancex;
	//}
	return r;
}

Vector2 GuardFat::distanceBetweenAladdin()
{
	float xAla = _aladdin->getPositionX() + (_aladdin->getBounding().right - _aladdin->getBounding().left) / 2;
	float x = this->getPositionX();

	float yAla = _aladdin->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x, yAla - y);
}

IComponent* GuardFat::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardFat::~GuardFat()
{
}

void GuardFat::movingLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-GUARDFAT_SPEED, move->getVelocity().y));
}

void GuardFat::movingRight()
{
	_sprite->setScaleX(1.6);

	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(GUARDFAT_SPEED, move->getVelocity().y));
}

void GuardFat::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}
