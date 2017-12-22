#include "GuardLu.h"

GuardLu::GuardLu(eStatus status, int posX, int posY, eDirection direction) :BaseEnemy(eID::GUARDLU)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDLU);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDLU_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
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
				this->setStatus(eStatus::DYING);
			}
			break;
		}
		else
			/*DK1:Aladdin đang không bị đánh
			DK2 bức ảnh status Attack của guartlu hiện tại là 3*/
			if (collision_event->_otherObject->isInStatus(eStatus::BEHIT) == false
				&&
				this->_animations[ATTACK]->getIndex() == 3)
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/CloudPoof.wav", 0);
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

float GuardLu::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

#pragma region Test
	char str[100];
	sprintf(str, "khoang cach voi aladdin: %f", xAla - x);
	text->setText(str);
#pragma endregion


	return xAla - x;
}

void GuardLu::UpdateStatus(float dt)
{
	switch (this->getStatus())
	{
		case eStatus::DESTROY:
			return;
		case eStatus::DYING:
		{
			standing();
			if (_animations[DYING]->getIndex() >= 9)
			{
				_animations[DYING]->setIndex(0);
				this->setStatus(DESTROY);
				//score+=10;
			}
			return;
		}
	}



	if (distanceBetweenAladdin() < 0)
	{
		float distance = -distanceBetweenAladdin();
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
		if (distance > 300)
		{
			standing();
			this->setStatus(eStatus::FREE);
			return;
		}
	}
	else if (distanceBetweenAladdin() > 0)
	{
		float distance = distanceBetweenAladdin();
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
		if (distance>250)
		{
			standing();
			this->setStatus(eStatus::FREE);
		}
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

