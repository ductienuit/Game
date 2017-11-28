#include "ThrowAction.h"

ThrowAction::ThrowAction(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDSHORT);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * THROWACTION_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
}

void ThrowAction::InIt()
{

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &ThrowAction::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &ThrowAction::onCollisionEnd);

	_animations[THROW] = new Animation(_sprite, 0.15f);
	_animations[THROW]->addFrameRect(eID::GUARDSHORT, "guardsShort_throw_0", 5);

	//_sprite->drawBounding(false);
	_sprite->setOrigin(Vector2(0, 0));

}

void ThrowAction::Update(float deltatime)
{
	this->UpdateStatus(deltatime);

	_animations[this->getStatus()]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void ThrowAction::Draw(LPD3DXSPRITE spritehandle, Viewport* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	text->Draw();
}

void ThrowAction::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void ThrowAction::onCollisionBegin(CollisionEventArg *)
{
}

void ThrowAction::onCollisionEnd(CollisionEventArg *)
{
}

float ThrowAction::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

void ThrowAction::UpdateStatus(float dt)
{
	if (distanceBetweenAladdin() < 0)
	{
		float distance = -distanceBetweenAladdin();
		if (distance < 150 && distance > 25)
		{
			//this->clearStatus();
			this->addStatus(eStatus::THROW);
			//standing();
			return;
		}
		/*this->clearStatus();
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();*/
		if (distance < 25)
		{
			//this->clearStatus();
			//this->addStatus(eStatus::MOVING_RIGHT);
			//movingRight();
		}
	}
	else if (distanceBetweenAladdin() > 0)
	{
		float distance = distanceBetweenAladdin();
		if (distance < 150 && distance > 25)
		{
			//this->clearStatus();
			this->addStatus(eStatus::THROW);
			//standing();
			return;
		}
		/*this->clearStatus();
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();*/
		if (distance < 25)
		{
			this->clearStatus();
			//this->addStatus(eStatus::MOVING_LEFT);
			//movingLeft();
		}
	}
}

IComponent* ThrowAction::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

ThrowAction::~ThrowAction()
{
}

void ThrowAction::movingLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-THROWACTION_SPEED, move->getVelocity().y));
}

void ThrowAction::movingRight()
{
	_sprite->setScaleX(1.6);

	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(THROWACTION_SPEED, move->getVelocity().y));
}

void ThrowAction::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}

void ThrowAction::Throw()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
	auto g = (Gravity*)this->_listComponent["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

float ThrowAction::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

	/*RECT BBox = _divingSprite->getBounding();
	float top = WINDOWS_HEIGHT - BBox.top;
	float left = _divingSprite->getPositionX()+(_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float right = BBox.right;
	float bottom = WINDOWS_HEIGHT - BBox.bottom;

	LPD3DXLINE line;
	auto dv = DeviceManager::getInstance()->getDevice();
	D3DXCreateLine(dv, &line);
	D3DXVECTOR2 lines[] = { D3DXVECTOR2(left, top),
	D3DXVECTOR2(right, top),
	D3DXVECTOR2(right, bottom),
	D3DXVECTOR2(left, bottom),
	D3DXVECTOR2(left, top),
	D3DXVECTOR2(right, bottom) };
	line->SetWidth(4);
	line->Begin();
	line->Draw(lines, 6, 0xffffffff);
	line->End();
	line->Release();*/

#pragma region Test
	char str[100];
	sprintf(str, "khoang cach voi aladdin: %f", xAla - x);
	text->setText(str);
#pragma endregion
	return xAla - x;
}
