#include "Jar.h"

Jar::Jar(eStatus status, int posX, int posY, int distancebroken) :BaseEnemy(eID::JAR)
{
	_distancebroken = distancebroken;
	_sprite = SpriteManager::getInstance()->getSprite(eID::JAR);
	_originPosition = Vector2(posX, posY);
	//_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 10.0f, 10.0f);

	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Jar::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Jar::onCollisionBegin);

	_animations[DROP] = new Animation(_sprite, 0.1f);
	_animations[DROP]->addFrameRect(eID::JAR, "jar_falling_", 6);


	_animations[DYING] = new Animation(_sprite, 0.05f);
	_animations[DYING]->addFrameRect(eID::JAR, "jar_broken_", 9);

}

void Jar::Update(float deltatime)
{
	switch (this->getStatus())
	{
		case DESTROY:
			return;
		case DROP:
		{

			float x = this->getPositionX();
			float y = this->getPositionY();
			if (y <= _originPosition.y - _distancebroken)
				setStatus(DYING);
			y -= JAR_VELOCITY;
			this->setPosition(x, y);
			break;
		}
		case DYING:
		{
			standing();
			if (_animations[DYING]->getIndex() >= 8)
			{
				_animations[DYING]->setIndex(0);
				this->setStatus(DESTROY);
				//score+=10;
				return;
			}
			break;
		}
		break;
	}
	_animations[this->getStatus()]->Update(deltatime);


	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void Jar::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void Jar::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Jar::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		if (collision_event->_otherObject->isInStatus(eStatus::ATTACK))
		{
			this->setStatus(DYING);
			break;
		}

		#pragma region Kiểm tra điều kiện aladdin bị trừ máu
		bool isBeAttack = !collision_event->_otherObject->isInStatus(eStatus::BEHIT) && !collision_event->_otherObject->isFlashing();
		/*DK1:Aladdin đang không bị đánh*/
		if (isBeAttack)
		{
			bool isStanding =  collision_event->_otherObject->isInStatus(NORMAL1) || collision_event->_otherObject->isInStatus(FREE);
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/FireFromCoal.wav", 0);
			InforAladdin::getInstance()->plusHealth(-10);
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
		#pragma endregion

		break;
	}
	}
}

void Jar::onCollisionEnd(CollisionEventArg *)
{
}

float Jar::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	if (isInStatus(DYING))
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

IComponent* Jar::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

Jar::~Jar()
{
}


void Jar::standing()
{
	/*auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);*/
}

void Jar::movingDown()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, -JAR_GRAVITY));
}

float Jar::PositionY()
{
	return this->getPositionY();
}