#include "FireBoss.h"


FireBoss::FireBoss(int posX, int posY, bool isLeft) :BaseObject(eID::FIRE_BOSS)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::FIRE_BOSS);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);

	Vector2 v(0, 0);
	Vector2 a(0, 0);

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	setScale(SCALEFACTOR);
	
	text = new Text("Arial", "", 10, 25);
	_isLeft = isLeft;
	if (isLeft)
	{
		setPosition(posX - 15, posY);
		this->setStatus(ATTACK_LEFT);
		setScaleX(-SCALEFACTOR.x);
	}
	else
	{
		setPosition(posX + 15, posY);
		this->setStatus(ATTACK_RIGHT);
		setScaleX(SCALEFACTOR.x);
	}
	InIt();
}

void FireBoss::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &FireBoss::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &FireBoss::onCollisionEnd);

	_animations[ATTACK_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[ATTACK_RIGHT]->addFrameRect(eID::FIRE_BOSS, "movingflame_", 8);

	_animations[ATTACK_LEFT] = new Animation(_sprite, 0.1f);
	_animations[ATTACK_LEFT]->addFrameRect(eID::FIRE_BOSS, "movingflame_", 8);
}

void FireBoss::Update(float deltatime)
{

	switch (_status)
	{
		case DESTROY:
			return;
		case ATTACK_RIGHT:
		{
			movingRight();
			break;
		}
		case ATTACK_LEFT:
		{
			movingLeft();
			break;
		}
	}

	_animations[_status]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void FireBoss::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[_status]->Draw(spritehandle, viewport);
}

void FireBoss::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void FireBoss::onCollisionBegin(CollisionEventArg *collision_event)
{
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::ALADDIN:
	{
		/*DK1:Aladdin đang không bị đánh*/
		if (collision_event->_otherObject->isInStatus(eStatus::BEHIT) == false)
		{
			this->setStatus(BEHIT);

			if (_animations[_status]->getIndex() == 3 || _animations[_status]->getIndex() == 7)
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/FireFromCoal.wav", 0);
				//Lưu trạng thái trước khi hết bị đánh set lại cái trạng thái cũ
				collision_event->_otherObject->savePreStatus();
				//Set status aladdin bị đánh
				collision_event->_otherObject->setStatus(eStatus::BEHIT);
				InforAladdin::getInstance()->plusHealth(-10);
			}
		}
		break;
	}
	}
}

void FireBoss::onCollisionEnd(CollisionEventArg *)
{
}

float FireBoss::checkCollision(BaseObject *object, float dt)
{
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	if (isInStatus(DESTROY))
		return 0.0f;
	if (collisionBody->checkCollision(object, dt, true))
		return 0.0f;
}

FireBoss::~FireBoss()
{
}

void FireBoss::movingLeft()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-FIRE_SPEED, move->getVelocity().y));
}

void FireBoss::movingRight()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(FIRE_SPEED, move->getVelocity().y));
}

void FireBoss::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}

