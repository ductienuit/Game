#include "Boom.h"
extern vector<BaseObject*> listActive;
Boom::Boom(int posX, int posY) : BaseObject(eID::BOOM)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOOM);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(NORMAL);
	setScale(SCALEAPPLE);
	this->setPosition(posX*SCALEFACTOR.x, posY*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Boom::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Boom::onCollisionBegin);

	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::BOOM, "Boom_00", "Boom_00",NULL);

	_animations[BEHIT] = new Animation(_sprite, 0.1f);
	_animations[BEHIT]->addFrameRect(eID::BOOM, "item_spark__0", 15);
}

void Boom::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	if (_animations[BEHIT]->getIndex() >= 6)
	{
		_animations[BEHIT]->setIndex(0);
		//apple+=10;
		setStatus(DESTROY);
	}
}

void Boom::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void Boom::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Boom::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		vector<BaseObject*> _listActive;
		_listActive = listActive;
		for each(auto object in _listActive)
		{
			// obj la Enermy va aladdin
			if (object == nullptr)
				continue;

			eID temp = object->getId();
			if (temp == APPLEEAT || temp == COINEAT ||temp == HEARTEAT|| temp == LAND ||temp==RESTARTPOINT ||
				temp == ALADDIN || object->getStatus() == DESTROY)
				continue;
			object->setStatus(DYING);
		}


		setStatus(BEHIT);
		break;
	}
	}

}

void Boom::onCollisionEnd(CollisionEventArg *)
{
}

float Boom::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision táo với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

Boom::~Boom()
{
}