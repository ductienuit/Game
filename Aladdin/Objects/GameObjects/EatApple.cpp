#include "EatApple.h"

EatApple::EatApple(int posX, int posY) :BaseObject(eID::APPLEEAT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::APPLEEAT);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
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

	_animations[NORMAL] = new Animation(_sprite, 0.02f);
	_animations[NORMAL]->addFrameRect(eID::APPLEEAT, "eat_apple_0", "eat_apple_0", NULL);
	

	_animations[BEHIT] = new Animation(_sprite, 0.12f);
	_animations[BEHIT]->addFrameRect(eID::APPLEEAT, "item_spark_", 12);
}

void EatApple::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	if (_animations[BEHIT]->getIndex() >= 6)
	{
		_animations[BEHIT]->setIndex(0);
		InforAladdin::getInstance()->plusApple(1);

		//âm thanh
		SoundManager::getInstance()->PlaySound("Resources/Audio/AppleCollect.wav", 0);
		//apple+=10;
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
			setStatus(BEHIT);
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

	//Check collision táo với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

EatApple::~EatApple()
{
}