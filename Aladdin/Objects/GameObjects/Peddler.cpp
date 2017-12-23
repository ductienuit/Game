#include "Peddler.h"

Peddler::Peddler(int posX, int posY) :BaseObject(eID::PEDDLER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::PEDDLER);

	this->setStatus(FREE);
	this->setPosition(posX*SCALECHARACTER.x, posY*SCALECHARACTER.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Peddler::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Peddler::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Peddler::onCollisionEnd);

	_animations[eStatus::FREE] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FREE]->addFrameRect(eID::PEDDLER, "peddler_00", "peddler_01", "peddler_02", "peddler_03", "peddler_04", "peddler_05", "peddler_06", "peddler_07", "peddler_08", "peddler_09", "peddler_10", 
		"peddler_11", "peddler_12", "peddler_13", NULL);
}

void Peddler::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	UpdateStatus();

	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{

		it->second->Update(deltatime);
	}
}

void Peddler::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_sprite->UpdatePosition();
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void Peddler::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Peddler::UpdateStatus()
{
}

void Peddler::onCollisionBegin(CollisionEventArg *collision_event)
{
}

void Peddler::onCollisionEnd(CollisionEventArg *)
{
}

float Peddler::checkCollision(BaseObject *object, float dt)
{
	return 0.0f;
}

RECT Peddler::getBounding()
{
	RECT rect = BaseObject::getBounding();

	return rect;
}

Peddler::~Peddler()
{
}
