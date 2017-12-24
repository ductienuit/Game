#include "Monkey.h"

Monkey::Monkey(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::MONKEY);
	/*Dòng dưới để set framewidth hoặc height
	để vừa vào khởi tạo không bị sai collison.
	Hàm InIt sẽ tự động cập nhật lại khi set status*/
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	_originPosition = Vector2(posX, posY);

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;
	_listComponent["Gravity"] = new Gravity(Vector2(0, -100), movement);

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

	_animations[ENDSCENE] = new Animation(_sprite, 0.15f);
	_animations[ENDSCENE]->addFrameRect(eID::MONKEY, "monkey_0", 8);
}

void Monkey::Update(float deltatime)
{
	_sprite->setScaleX(1.6);
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-270, 0));
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

Monkey::~Monkey()
{
}
