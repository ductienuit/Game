#include "RestartPoint.h"
RestartPoint::RestartPoint(int posX, int posY) :BaseObject(eID::RESTARTPOINT)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::RESTARTPOINT);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(NORMAL);
	setScale(SCALEAPPLE);
	this->setPosition(posX*SCALEFACTOR.x, posY*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void RestartPoint::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &RestartPoint::onCollisionBegin);

	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::RESTARTPOINT, "genie_restart_point_00", "genie_restart_point_00", NULL);

	_animations[BEHIT] = new Animation(_sprite, 0.12f);
	_animations[BEHIT]->addFrameRect(eID::RESTARTPOINT, "genie_restart_point_0", 10);

	_animations[FREE] = new Animation(_sprite, 0.12f);
	_animations[FREE]->addFrameRect(eID::RESTARTPOINT, "genie_restart_point_09", "genie_restart_point_09", "genie_restart_point_09", NULL);

	_animations[STOPWALK] = new Animation(_sprite, 0.12f);
	_animations[STOPWALK]->addFrameRect(eID::RESTARTPOINT, "restart_point_", 14);
	
	_canTurn = true;
}

void RestartPoint::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	


}

void RestartPoint::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void RestartPoint::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void RestartPoint::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	 switch (objectID)
	{
	case eID::ALADDIN:
	{
		if (_animations[STOPWALK]->getIndex() >= 10)
		{
			collision_event->_otherObject->setOpacity(1.0);
		}
		if (_canTurn)
		{
			setStatus(BEHIT);
			collision_event->_otherObject->SetRestartPoint(this);
			if (_animations[BEHIT]->getIndex() >= 8)
			{
				_canTurn = false;
				_animations[BEHIT]->setIndex(9);
			}
		}
		else
		{
			setStatus(FREE);
		}
		break;
	}
	}
}

void RestartPoint::onCollisionEnd(CollisionEventArg *)
{
	//this->clearStatus();
	//this->setStatus(STOPWALK);
}

float RestartPoint::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision táo với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}


RestartPoint::~RestartPoint()
{

}