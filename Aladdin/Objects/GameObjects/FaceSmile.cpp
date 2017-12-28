#include "FaceSmile.h"

FaceSmile::FaceSmile(int posX, int posY) :BaseObject(eID::FACESMILE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::FACESMILE);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(NORMAL);
	setScale(SCALEAPPLE);
	this->setPosition(posX*SCALEFACTOR.x, posY*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

FaceSmile::FaceSmile(int posX, int posY, bool isBoss) :BaseObject(eID::FACESMILE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::FACESMILE);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(NORMAL);
	this->setPosition(posX*SCALEBOSSFRONT.x, posY*SCALEBOSSFRONT.y, 1.0f);
	setScale(SCALEAPPLE);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void FaceSmile::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &FaceSmile::onCollisionBegin);

	_animations[NORMAL] = new Animation(_sprite, 0.12f);
	_animations[NORMAL]->addFrameRect(eID::FACESMILE, "facesmile_00", "facesmile_00", "facesmile_00", "facesmile_00", "facesmile_01", "facesmile_02", "facesmile_03", NULL);

	_animations[BEHIT] = new Animation(_sprite, 0.12f);
	_animations[BEHIT]->addFrameRect(eID::FACESMILE, "item_spark_", 12);
}

void FaceSmile::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	if (_animations[BEHIT]->getIndex() >= 6)
	{
		_animations[BEHIT]->setIndex(0);
		InforAladdin::getInstance()->plusApple(1);
		//facesmile+=10;
		setStatus(DESTROY);
	}
}


void FaceSmile::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void FaceSmile::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void FaceSmile::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		setStatus(BEHIT);
		//âm thanh
		SoundManager::getInstance()->PlaySound("Resources/Audio/AppleCollect.wav", 0);
		break;
	}
	}

}

void FaceSmile::onCollisionEnd(CollisionEventArg *)
{
}

float FaceSmile::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	if (isInStatus(BEHIT))
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision facesmile với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

FaceSmile::~FaceSmile()
{
}