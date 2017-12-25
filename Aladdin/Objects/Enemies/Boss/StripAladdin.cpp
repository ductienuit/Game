#include "StripAladdin.h"

StripAladdin::StripAladdin(int posX, int posY) : BaseObject(eID::STRIP_ALADDIN)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::STRIP_ALADDIN);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(BEHIT);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void StripAladdin::InIt()
{
	_animations[BEHIT] = new Animation(_sprite, 0.06f);
	_animations[BEHIT]->addFrameRect(eID::STRIP_ALADDIN, "spell_", 4);
}

void StripAladdin::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	switch (_status)
	{
	case DESTROY:
		return;
	case BEHIT:
	{
		setScale(SCALEAPPLE);
		if (_animations[BEHIT]->getIndex() >= 3)
		{
			_animations[BEHIT]->setIndex(0);
			setStatus(DESTROY);
		}
	}
	}
}

void StripAladdin::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void StripAladdin::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void StripAladdin::onCollisionBegin(CollisionEventArg *collision_event)
{

}

void StripAladdin::onCollisionEnd(CollisionEventArg *)
{
}

float StripAladdin::checkCollision(BaseObject *object, float dt)
{
	return 0.0f;
}

StripAladdin::~StripAladdin()
{
}