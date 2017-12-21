#include "Fire.h"

Fire::Fire(eStatus status, int posX, int posY, eDirection direction) :BaseEnemy(eID::FIRE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::FIRE);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(status);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Fire::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Fire::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Fire::onCollisionEnd);

	_animations[eStatus::BEHIT] = new Animation(_sprite, 0.15f);
	_animations[eStatus::BEHIT]->addFrameRect(eID::FIRE,"burn_",9);
}

void Fire::Update(float deltatime)
{
	if (isInStatus(STOPWALK))
		return;
	_animations[this->getStatus()]->Update(deltatime);

	UpdateStatus();
}

void Fire::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_sprite->UpdatePosition();
	if (isInStatus(STOPWALK))
		return;
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void Fire::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Fire::UpdateStatus()
{
	if (_animations[BEHIT]->getIndex() >= 8)
	{
		_animations[BEHIT]->setIndex(0);
		setStatus(STOPWALK);
	}
}

void Fire::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
		case eID::ALADDIN:
		{
			/*DK1:Aladdin đang không bị đánh*/
			if (collision_event->_otherObject->isInStatus(eStatus::BEHIT) == false )
			{
				this->setStatus(BEHIT);

				if (_animations[BEHIT]->getIndex() == 3)
				{	
					//Lưu trạng thái trước khi hết bị đánh set lại cái trạng thái cũ
					collision_event->_otherObject->savePreStatus();
					//Set status aladdin bị đánh
					collision_event->_otherObject->setStatus(eStatus::BEHIT);
					ScoreAladdin::getInstance()->plusHealth(-10);
				}
			}
			break;
		}
	}
}

void Fire::onCollisionEnd(CollisionEventArg *)
{
}

float Fire::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

IComponent* Fire::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

RECT Fire::getBounding()
{
	RECT rect = BaseObject::getBounding();
	rect.top -= 50;

	return rect;
}

Fire::~Fire()
{
}
