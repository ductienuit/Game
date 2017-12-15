#include "KnifeShort.h"

KnifeShort::KnifeShort(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::KNIFE);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	_originPosition = Vector2(posX - 120, posY + 60);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * KNIFE_SHORT_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void KnifeShort::InIt()
{

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &KnifeShort::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &KnifeShort::onCollisionEnd);

	_animations[THROW] = new Animation(_sprite, 0.1f);
	_animations[THROW]->addFrameRect(eID::KNIFE, "guardsShort_throw_01", "guardsShort_throw_02", "guardsShort_throw_03", "guardsShort_throw_04"
		, "guardsShort_throw_05", "guardsShort_throw_06", "guardsShort_throw_07", NULL);

}
void KnifeShort::Update(float deltatime)
{
	_animations[this->getStatus()]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void KnifeShort::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void KnifeShort::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void KnifeShort::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		/*DK1:Aladdin đang không bị đánh*/
		if (collision_event->_otherObject->isInStatus(eStatus::BEHIT) == false && !isInStatus(DESTROY))
		{
			//Set status aladdin bị đánh
			collision_event->_otherObject->setStatus(eStatus::BEHIT);
		}
		break;
	}
	default:
		break;
	}
}

void KnifeShort::onCollisionEnd(CollisionEventArg *)
{
}

float KnifeShort::checkCollision(BaseObject *object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];

	//Check collision enermy(this) với aladdin(object)
	collisionBody->checkCollision(object, dt, true);
	return 0.0f;
}

IComponent* KnifeShort::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

KnifeShort::~KnifeShort()
{
}

void KnifeShort::movingLeft(float x, float y)
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-KNIFE_SHORT_SPEED, -KNIFE_SHORT_JUMP));
	x = x - 80;
	y = y + 60;
	this->setPosition(x, y);
}

void KnifeShort::movingRight(float x, float y)
{
	_sprite->setScaleX(1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(KNIFE_SHORT_SPEED, -KNIFE_SHORT_JUMP));

	x = x + 80;
	y = y + 60;
	this->setPosition(x, y);
}
