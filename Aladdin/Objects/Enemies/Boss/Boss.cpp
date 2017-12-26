#include "Boss.h"

extern vector<BaseObject*>	listStrip;

Boss::Boss(eStatus status, int posX, int posY, Aladdin* aladdin) :BaseEnemy(eID::BOSS)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

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
	_animations[BEHIT]->addFrameRect(eID::BOSS, "jafar_04", "jafar_03", "jafar_02", NULL);

	_animations[PULL_LEFT] = new Animation(_sprite, 0.15f);
	_animations[PULL_LEFT]->addFrameRect(eID::BOSS, "jafar_0", 8);

	_animations[PULL_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[PULL_RIGHT]->addFrameRect(eID::BOSS, "jafar_0", 8);

	_animations[ATTACK_LEFT] = new Animation(_sprite, 0.12f);
	_animations[ATTACK_LEFT]->addFrameRect(eID::BOSS, "jafar_04", "jafar_05", "jafar_06", "jafar_07", NULL);

	_animations[ATTACK_RIGHT] = new Animation(_sprite, 0.12f);
	_animations[ATTACK_RIGHT]->addFrameRect(eID::BOSS, "jafar_04", "jafar_05", "jafar_06", "jafar_07", NULL);

	_animations[THROW_RIGHT_FAR] = new Animation(_sprite, 0.15f);
	_animations[THROW_RIGHT_FAR]->addFrameRect(eID::BOSS, "jafar_snake_",11);

	_animations[THROW_LEFT_FAR] = new Animation(_sprite, 0.15f);
	_animations[THROW_LEFT_FAR]->addFrameRect(eID::BOSS, "jafar_snake_", 11);

	_animations[DYING] = new Animation(_sprite, 0.1f);
	_animations[DYING]->addFrameRect(eID::BOSS, "destroy_enermy_00_0", 10);

	_hitpoint = 48;
	_frequency = new StopWatch();
	_frequencyFireBoss = new StopWatch();
	_alarmSetAppleAladdin = new StopWatch();
}

void Boss::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	this->UpdateStatus(deltatime);

	if (isversion2)
	{
		for (int i = 0; i < _listStar.size(); i++)
		{
			_listStar[i]->Release();
			delete  _listStar[i];
			_listStar.erase(_listStar.begin() + i);
		}
		_listStar.clear();
	}
	else
	{
		for (int i = 0; i < _listStar.size(); i++)
		{
			_listStar[i]->Update(deltatime);
		}
	}

	for (int i = 0; i < _listFireBoss.size(); i++)
	{
		_listFireBoss[i]->Update(deltatime);
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

	for (int i = 0; i < _listFireBoss.size(); i++)
	{
		if (_listFireBoss[i]->isInStatus(DESTROY))
		{
			_listFireBoss[i]->Release();
			delete  _listStar[i];
			_listFireBoss.erase(_listStar.begin() + i);
		}
		else
			_listFireBoss[i]->Draw(spritehandle, viewport);
	}
}

void Boss::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}



	for (int i = 0; i < _listFireBoss.size(); i++)
	{
		_listFireBoss[i]->Release();
		delete  _listFireBoss[i];
		_listFireBoss.erase(_listFireBoss.begin() + i);
	}
	_listFireBoss.clear();

	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Boss::onCollisionBegin(CollisionEventArg *collision_event)
{
	eStatus status = getStatus();
	switch (status)
	{
		case eStatus::DESTROY:
			return;
		case eStatus::ATTACK_RIGHT:
		{
			#pragma region Kiểm tra điều kiện aladdin bị trừ máu
			bool isBeAttack = !collision_event->_otherObject->isInStatus(eStatus::BEHIT) && !collision_event->_otherObject->isFlashing();
			/*DK1:Aladdin đang không bị đánh*/
			if (isBeAttack)
			{
				bool isStanding =  collision_event->_otherObject->isInStatus(NORMAL1) || collision_event->_otherObject->isInStatus(FREE);
				_aladdin->Stop(true);
				//âm thanh
				//SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
				InforAladdin::getInstance()->plusHealth(-40);
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
			break;
			#pragma endregion
		}
		case eStatus::ATTACK_LEFT:
		{
			#pragma region Kiểm tra điều kiện aladdin bị trừ máu
			bool isBeAttack = !collision_event->_otherObject->isInStatus(eStatus::BEHIT) && !collision_event->_otherObject->isFlashing();
			/*DK1:Aladdin đang không bị đánh*/
			if (isBeAttack)
			{
				bool isStanding =  collision_event->_otherObject->isInStatus(NORMAL1) || collision_event->_otherObject->isInStatus(FREE);
				_aladdin->Stop(true);
				//âm thanh
				//SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
				InforAladdin::getInstance()->plusHealth(-40);
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
			break;
			#pragma endregion
		}
		case eStatus::THROW_LEFT_FAR:
		{

			//if (_animations[THROW_LEFT_FAR]->getIndex() == 4 || _animations[THROW_LEFT_FAR]->getIndex() == 10)
			//{
			//	if (!_aladdin->isInStatus(BEHIT))
			//	{
			//		_aladdin->Stop(true);
			//		_aladdin->setStatus(BEHIT);
			//		InforAladdin::getInstance()->plusHealth(-10);
			//	}
			//}

			#pragma region Kiểm tra điều kiện aladdin bị trừ máu
			bool isBeAttack = !collision_event->_otherObject->isInStatus(eStatus::BEHIT) && !collision_event->_otherObject->isFlashing();
			/*DK1:Aladdin đang không bị đánh*/
			if (isBeAttack)
			{
				bool isStanding =  collision_event->_otherObject->isInStatus(NORMAL1) || collision_event->_otherObject->isInStatus(FREE);
				//âm thanh
				//SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
				InforAladdin::getInstance()->plusHealth(-40);
				if (isStanding)
				{
					//Set status aladdin bị đánh
					collision_event->_otherObject->setStatus(eStatus::BEHIT);
					SoundManager::getInstance()->PlaySound("Resources/Audio/AladdinHurt.wav", 0);
					//Set status aladdin bị đánh
				}
				else
				{
					//Set status aladdin bị đánh
					collision_event->_otherObject->StartFlash();
					//Set status aladdin bị đánh
					SoundManager::getInstance()->PlaySound("Resources/Audio/AladdinHurt.wav", 0);
				}
			}
			#pragma endregion
			break;
		}
		case eStatus::THROW_RIGHT_FAR:
		{
			#pragma region Kiểm tra điều kiện aladdin bị trừ máu
			bool isBeAttack = !collision_event->_otherObject->isInStatus(eStatus::BEHIT) && !collision_event->_otherObject->isFlashing();
			/*DK1:Aladdin đang không bị đánh*/
			if (isBeAttack)
			{
				bool isStanding =  collision_event->_otherObject->isInStatus(NORMAL1) || collision_event->_otherObject->isInStatus(FREE);
				//âm thanh
				//SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
				InforAladdin::getInstance()->plusHealth(-40);
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
			break;
		}
	}


	if (collision_event->_otherObject->isInStatus(ATTACK))
	{
		if (collision_event->_otherObject->getIndex() == 2 && _hitpoint >= 1)
		{
			_hitpoint -= 1;
			this->setStatus(eStatus::BEHIT);
		}
	}
}

void Boss::onCollisionEnd(CollisionEventArg *)
{
}

float Boss::checkCollision(BaseObject *object, float dt)
{
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	collisionBody->checkCollision(_aladdin , dt, true);

	for (int i = 0; i < _listFireBoss.size(); i++)
		_listFireBoss[i]->checkCollision(object, dt);

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
				_hitpoint;
			}
			return;
		}
		case eStatus::BEHIT:
		{
			if (_animations[BEHIT]->getIndex() >= 2)
			{
				float x = getPositionX();
				float y = getPositionY();
				listStrip.push_back(new StripBoss(x,y));
				_animations[BEHIT]->setIndex(0);
				
				if (_hitpoint <= 26)
				{
					isversion2 = true;

					if (_alarmSetAppleAladdin->isStopWatch(1000))
						InforAladdin::getInstance()->setApple(15);

					//SOUNDBOSS
					//âm thanh
					SoundManager::getInstance()->PlaySound("Resources/Audio/JafarSnake.wav", 0);
					this->setStatus(THROW_LEFT_FAR);
					return;
				}
				//SOUNDBOSS
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/JafarLaugh.wav", 0);
				this->setStatus(PULL_LEFT);
			}
			return;
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


			if (_frequency->isStopWatch(130))
			{
				_listStar.push_back(new Star(getPositionX() + 10, getPositionY(), false, _aladdin));

				_frequency->restart();
			}
			// new star
			break;
		}
		case eStatus::THROW_LEFT_FAR:
		{
			if(_frequencyFireBoss->isStopWatch(1700))
			{
				float x = getPositionX();
				float y = getPositionY();
				_listFireBoss.push_back(new FireBoss(x,y-45,true));
				_frequencyFireBoss->restart();
			}
			break;
		}
		case eStatus::THROW_RIGHT_FAR:
		{
			if (_frequencyFireBoss->isStopWatch(1700))
			{
				float x = getPositionX();
				float y = getPositionY();
				_listFireBoss.push_back(new FireBoss(x, y-45, false));
				_frequencyFireBoss->restart();
			}
			break;
		}
	}
	

	Vector2 distance = distanceBetweenAladdin();
	if (isversion2)
	{
		//Aladdin bên trái enermy
		if (distance.x <= 0)
		{
			setStatus(THROW_LEFT_FAR);
			setScaleX(-SCALECHARACTER.x);
		}
		else
		{
			setStatus(THROW_RIGHT_FAR);
			setScaleX(SCALECHARACTER.x);
		}
	}
	else
	{
		InforAladdin::getInstance()->setApple(99);
		//Aladdin bên trái enermy
		if (distance.x <= 0)
		{
			distance.x = (-1)*distance.x;
			if (distance.x < 90)
			{
				setStatus(ATTACK_LEFT);
				setScaleX(-SCALECHARACTER.x);
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
	float xAla = _aladdin->getPositionX();
	float x = this->getPositionX();

	float yAla = _aladdin->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x, yAla - y);
}

void Boss::OptimizeFire(RECT* rect)
{
	for (size_t i = 0; i < _listFireBoss.size(); i++)
	{
		RECT apple = _listFireBoss[i]->getBounding();
		RECT temp = *rect;
		temp.top = apple.bottom;

		if (!isContain(_listFireBoss[i], temp))
		{
			_listFireBoss[i]->Release();
			delete _listFireBoss[i];
			_listFireBoss.erase(_listFireBoss.begin() + i);
		}
	}
}

bool Boss::isVersion2()
{
	return isversion2;
}

bool Boss::isContain(BaseObject*object, RECT rect1)
{
	/*25/11 Đức Tiến đã sửa*/
	RECT rect2 = object->getBounding();
	swap(rect2.top, rect2.bottom);
	return !(rect2.left > rect1.right || rect2.right < rect1.left || rect2.top > rect1.bottom || rect2.bottom < rect1.top);
}