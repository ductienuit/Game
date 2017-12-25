#include "GuardLu.h"

GuardLu::GuardLu(eStatus status, int posX, int posY, BaseObject* aladdin, int minMove, int maxMove) :BaseEnemy(eID::GUARDLU)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDLU);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/

	_aladdin = aladdin;
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	Vector2 v(0 * GUARDLU_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	_minMove = getPositionX() - 20; //- minMove;
	_maxMove = getPositionX() + 350; //+ maxMove;
	InIt();
}

void GuardLu::InIt()
{

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardLu::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardLu::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDLU, "guardsLu_Moving_", 12);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDLU, "guardsLu_Moving_", 12);

	_animations[ATTACK] = new Animation(_sprite, 0.3f);
	_animations[ATTACK]->addFrameRect(eID::GUARDLU, "guardsLu_Attack_", 4);

	_animations[FREE] = new Animation(_sprite, 0.2f);
	_animations[FREE]->addFrameRect(eID::GUARDLU, "guardsLu_free_", 6);

	_animations[DYING] = new Animation(_sprite, 0.2f);
	_animations[DYING]->addFrameRect(eID::GUARDLU, "destroy_enermy_", 10);

	//_sprite->drawBounding(false);

	_hitpoint = 2;//1 lần đánh
	_score = 10; //Số điểm được mỗi lần giết enermy


}

void GuardLu::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	this->UpdateStatus(deltatime);
	
	// update component ?? sau cùng ?? s?a bên trên sau ?ó nó c?p nh?t ?úng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void GuardLu::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void GuardLu::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void GuardLu::onCollisionBegin(CollisionEventArg *collision_event)
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
					InforAladdin::getInstance()->plusScore(10);
					_hitpoint -= 1;
					this->setStatus(eStatus::DYING);
				}
				break;
			}
			else
			{
					bool isBeAttack = !collision_event->_otherObject->isInStatus(eStatus::BEHIT) && !collision_event->_otherObject->isFlashing();
					/*DK1:Aladdin đang không bị đánh*/
					if (isBeAttack)
					{
						bool isStanding =  collision_event->_otherObject->isInStatus(NORMAL1) || collision_event->_otherObject->isInStatus(FREE);
						if (_animations[ATTACK]->getIndex() == 3)
						{
							//âm thanh
							SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
							InforAladdin::getInstance()->plusApple(-5);
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
	}
}

void GuardLu::onCollisionEnd(CollisionEventArg *)
{
}

float GuardLu::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}
RECT GuardLu::getBounding()
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

Vector2 GuardLu::distanceBetweenAladdin()
{
	float xAla = _aladdin->getPositionX() + (_aladdin->getBounding().right - _aladdin->getBounding().left) / 2;
	float x = this->getPositionX();

	float yAla = _aladdin->getPositionY();
	float y = this->getPositionY();

	return Vector2(xAla - x, yAla - y);
}


void GuardLu::UpdateStatus(float dt)
{
	float xAla = _aladdin->getPositionX() + (_aladdin->getBounding().right - _aladdin->getBounding().left) / 2;
	switch (this->getStatus())
	{
		case eStatus::DESTROY:
			return;
		case eStatus::DYING:
		{
			standing();
			if (_animations[DYING]->getIndex() >= 9)
			{
				//SOUNDDDDDD
				//Nhạc khi object bị destroy
				SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
				_animations[DYING]->setIndex(0);
				this->setStatus(DESTROY);
				//score+=10;
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
			if (distance < 25 && distance > 2.5)
			{
				this->clearStatus();
				this->addStatus(eStatus::ATTACK);
				standing();
				return;
			}
			this->clearStatus();
			this->addStatus(eStatus::MOVING_LEFT);
			movingLeft();
			if (distance < 25)
			{
				this->setStatus(eStatus::MOVING_RIGHT);
				movingRight();
			}
			/*if (distance > 300)
			{
				standing();
				this->setStatus(eStatus::FREE);
				return;
			}*/
		}
		else if (distanceBetweenAladdin() > 0)
		{
			float distance = distanceBetweenAladdin().x;
			if (distance < 70 && distance > 10)
			{
				this->clearStatus();
				this->addStatus(eStatus::ATTACK);
				standing();
				return;
			}
			this->clearStatus();
			this->addStatus(eStatus::MOVING_RIGHT);
			movingRight();
			if (distance < 50)
			{
				this->clearStatus();
				this->addStatus(eStatus::MOVING_LEFT);
				movingLeft();
			}
			/*if (distance > 250)
			{
				standing();
				this->setStatus(eStatus::FREE);
			}*/
		}
	}
	else if ((_minMove > this->getPositionX()) && xAla < _minMove)
	{
		this->addStatus(eStatus::FREE);
		standing();
	}
	else if (distanceBetweenAladdin().x > 0 && xAla > _minMove && this->getPositionX() < _maxMove)
	{
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();
	}
	else if ((this->getPositionX() > _maxMove) && xAla > _maxMove)
	{
		this->addStatus(eStatus::FREE);
		standing();
	}
	else if (distanceBetweenAladdin().x < 0 && xAla < _maxMove)
	{
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();
	}
	else if (_minMove < this->getPositionX() < _maxMove)
	{
		this->setStatus(eStatus::FREE);
		standing();
	}
}

IComponent* GuardLu::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardLu::~GuardLu()
{
}

void GuardLu::movingLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-GUARDLU_SPEED, move->getVelocity().y));
}

void GuardLu::movingRight()
{
	_sprite->setScaleX(1.6);

	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(GUARDLU_SPEED, move->getVelocity().y));
}

void GuardLu::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}

