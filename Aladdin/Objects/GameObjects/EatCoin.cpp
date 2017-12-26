#include "EatCoin.h"

EatCoin::EatCoin(int posX, int posY) : BaseObject(eID::COINEAT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::COINEAT);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(NORMAL);
	setScale(SCALEAPPLE);
	this->setPosition(posX*SCALEFACTOR.x, posY*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void EatCoin::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &EatCoin::onCollisionBegin);

	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::COINEAT, "coin_0", 9);

	_animations[BEHIT] = new Animation(_sprite, 0.12f);
	_animations[BEHIT]->addFrameRect(eID::COINEAT, "item_spark_", 12);
}

void EatCoin::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	if (_animations[BEHIT]->getIndex() >= 6)
	{
		_animations[BEHIT]->setIndex(0);
		InforAladdin::getInstance()->plusCoin(5);
		setStatus(DESTROY);
	}
}

void EatCoin::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void EatCoin::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void EatCoin::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		//SOUNDDDDDDDDDDDDDDDDDDDDDDD THAY NHẠC< NHẠC SAI< CÁI NÀY T MỚI BỎ VÀO
		SoundManager::getInstance()->PlaySound("Resources/Audio/ExtraHealth.wav", 0);
		setStatus(BEHIT);
		break;
	}
	}

}

void EatCoin::onCollisionEnd(CollisionEventArg *)
{
}

float EatCoin::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	if (isInStatus(BEHIT))
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision táo với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

EatCoin::~EatCoin()
{
}