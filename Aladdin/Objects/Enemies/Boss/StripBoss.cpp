#include "StripBoss.h"
extern vector<BaseObject*> listActive;
StripBoss::StripBoss(int posX, int posY) : BaseObject(eID::STRIP_BOSS)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::STRIP_BOSS);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	this->setStatus(BEHIT);
	setScale(SCALEAPPLE);
	this->setPosition(posX*SCALEFACTOR.x, posY*SCALEFACTOR.y, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void StripBoss::InIt()
{
	_animations[BEHIT] = new Animation(_sprite, 0.01f);
	_animations[BEHIT]->addFrameRect(eID::STRIP_BOSS, "explosion_", 26);
}

void StripBoss::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	if (_animations[BEHIT]->getIndex() >= 25)
	{
		_animations[BEHIT]->setIndex(0);
		setStatus(DESTROY);
		this->Release();
		delete this;
	}
}

void StripBoss::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void StripBoss::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void StripBoss::onCollisionBegin(CollisionEventArg *collision_event)
{

}

void StripBoss::onCollisionEnd(CollisionEventArg *)
{
}

float StripBoss::checkCollision(BaseObject *object, float dt)
{
	return 0.0f;
}

StripBoss::~StripBoss()
{
}