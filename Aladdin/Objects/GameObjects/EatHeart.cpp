#include "EatHeart.h"

EatHeart::EatHeart(int posX, int posY) :BaseObject(eID::HEARTEAT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::HEARTEAT);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(NORMAL);
	setScale(SCALEHEART);
	this->setPosition(posX*SCALEFACTOR.x, posY*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void EatHeart::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &EatHeart::onCollisionBegin);

	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::HEARTEAT, "eat_heart_0", 4);

	_animations[BEHIT] = new Animation(_sprite, 0.12f);
	_animations[BEHIT]->addFrameRect(eID::HEARTEAT, "item_spark_0", 12);
}

void EatHeart::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);


	if (_animations[BEHIT]->getIndex() >= 6)
	{
		_animations[BEHIT]->setIndex(0);

		InforAladdin::getInstance()->plusHealth(50);
		setStatus(DESTROY);
	}
}

void EatHeart::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void EatHeart::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void EatHeart::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{

		SoundManager::getInstance()->PlaySound("Resources/Audio/ExtraHealth.wav", 0);
		setStatus(BEHIT);
		break;
	}
	}

}

void EatHeart::onCollisionEnd(CollisionEventArg *)
{
}

float EatHeart::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	if (isInStatus(BEHIT))
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision tim v?i aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

EatHeart::~EatHeart()
{
}