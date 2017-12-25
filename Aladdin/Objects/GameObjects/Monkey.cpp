#include "Monkey.h"

Monkey::Monkey(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::MONKEY);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);

	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
	InIt();
}

void Monkey::InIt()
{
	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	_animations[ENDSCENE] = new Animation(_sprite, 0.1f);
	_animations[ENDSCENE]->addFrameRect(eID::MONKEY, "monkey_0", 8);


	//Chổ này t ko chỉnh ảnh đc. m chỉnh hộ phát :3
	_animations[FREE] = new Animation(_sprite, 0.1f);
	_animations[FREE]->addFrameRect(eID::MONKEY, "monkey_0", 8);
}

void Monkey::Update(float deltatime)
{
	movingLeft();

	_animations[this->getStatus()]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void Monkey::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
}

void Monkey::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Monkey::movingLeft()
{
	_sprite->setScaleX(1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-MONKEY_SPEED, 0));
}

Monkey::~Monkey()
{
}
