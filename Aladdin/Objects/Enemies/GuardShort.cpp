#include "GuardShort.h"

GuardShort::GuardShort(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::GUARDSHORT);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * GUARDSHORT_SPEED, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
}

void GuardShort::InIt()
{

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &GuardShort::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &GuardShort::onCollisionEnd);

	_animations[MOVING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_LEFT]->addFrameRect(eID::GUARDSHORT, "guardsShort_Moving_0", 8);

	_animations[MOVING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[MOVING_RIGHT]->addFrameRect(eID::GUARDSHORT, "guardsShort_Moving_0", 8);

	_animations[ATTACK] = new Animation(_sprite, 0.2f);
	_animations[ATTACK]->addFrameRect(eID::GUARDSHORT, "guardsShort_attack_0", 5);

	_animations[THROW] = new Animation(_sprite, 0.15f);
	_animations[THROW]->addFrameRect(eID::GUARDSHORT, "guardsShort_throw_0", 5);

	_sprite->setOrigin(Vector2(0, 0));

}

void GuardShort::Update(float deltatime)
{
	this->UpdateStatus(deltatime);

	_animations[this->getStatus()]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void GuardShort::Draw(LPD3DXSPRITE spritehandle, Viewport* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	text->Draw();
}

void GuardShort::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void GuardShort::onCollisionBegin(CollisionEventArg *)
{
}

void GuardShort::onCollisionEnd(CollisionEventArg *)
{
}

float GuardShort::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

float GuardShort::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() +(_divingSprite->getBounding().right- _divingSprite->getBounding().left) / 2;
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
	sprintf(str, "khoang cach voi aladdin: %f", xAla);
	text->setText(str);
#pragma endregion


	return xAla - x;
}

void GuardShort::UpdateStatus(float dt)
{
	if (distanceBetweenAladdin() < 0)
	{
		float distance = -distanceBetweenAladdin();
		if (distance < 200)
		{
			this->clearStatus();
			this->addStatus(eStatus::ATTACK);
			standing();
			return;
		}
		this->clearStatus();
		this->addStatus(eStatus::MOVING_LEFT);
		movingLeft();
	}
	else if (distanceBetweenAladdin() > 0)
	{
		float distance = distanceBetweenAladdin();
		if (distance < 200)
		{
			this->clearStatus();
			this->addStatus(eStatus::ATTACK);
			standing();
			return;
		}
		this->clearStatus();
		this->addStatus(eStatus::MOVING_RIGHT);
		movingRight();
	}
}

IComponent* GuardShort::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

GuardShort::~GuardShort()
{
}

void GuardShort::movingLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-GUARDSHORT_SPEED, move->getVelocity().y));
}

void GuardShort::movingRight()
{
	_sprite->setScaleX(1.6);

	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(GUARDSHORT_SPEED, move->getVelocity().y));
}

void GuardShort::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}
