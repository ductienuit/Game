#include "EatApple.h"

EatApple::EatApple(int posX, int posY) :BaseObject(eID::APPLEEAT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::APPLEEAT);
	_itemSpark = SpriteManager::getInstance()->getSprite(eID::ITEMSPARK);
	this->setStatus(NORMAL);
	setScale(SCALEAPPLE);
	this->setPosition(posX*SCALEFACTOR.x, posY*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void EatApple::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &EatApple::onCollisionBegin);

	_animations[NORMAL] = new Animation(_sprite, 10.0f);
	_animations[NORMAL]->addFrameRect(eID::APPLEEAT, "apple_00", "apple_00", "apple_00", NULL);

	_animations[BEHIT] = new Animation(_itemSpark, 0.05f);
	_animations[BEHIT]->addFrameRect(eID::ITEMSPARK, "item_spark_strip_", 7);
}

void EatApple::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	if (_animations[BEHIT]->getIndex() >= 6)
	{
		_animations[BEHIT]->setIndex(0);
		setStatus(DESTROY);
	}
}

void EatApple::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void EatApple::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void EatApple::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
		case eID::ALADDIN:
		{
			//_sprite = _itemSpark;
			//setStatus(BEHIT);
			break;
		}
	}
	
}

void EatApple::onCollisionEnd(CollisionEventArg *)
{
}

float EatApple::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

EatApple::~EatApple()
{
}