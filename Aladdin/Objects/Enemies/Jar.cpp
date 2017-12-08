#include "Jar.h"

Jar::Jar(eStatus status, int posX, int posY, eDirection direction)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::JAR);
	_sprite->setFrameRect(0, 0, 32.0f, 16.0f);
	_originPosition = Vector2(posX, posY);

	_divingSprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	Vector2 v(direction * JAR_GRAVITY, 0);
	Vector2 a(0, 0);
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(posX, posY, 1.0f);
	text = new Text("Arial", "", 10, 25);
}

void Jar::InIt()
{
	//auto move = (Movement*)this->_listComponent["Movement"];
	//move->setVelocity(Vector2(move->getVelocity().x, JAR_JUMP));

	//auto gravity = new Gravity(Vector2(0, -JAR_GRAVITY), move);
	//gravity->setStatus(eGravityStatus::FALLING__DOWN);
	//_listComponent["Gravity"] = gravity;

	/*auto movement = new Movement(Vector2(9.8, 9.8), Vector2(20, 10), _sprite);
	_listComponent["Movement"] = movement;

	auto gravity = new Gravity(Vector2(0,-JAR_GRAVITY),movement);
	gravity->setStatus(eGravityStatus::FALLING__DOWN);*/
	//_listComponent["Gravity"] = gravity;

	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Jar::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Jar::onCollisionEnd);

	_animations[DROP] = new Animation(_sprite, 0.1f);
	_animations[DROP]->addFrameRect(eID::JAR, "lu_roi_", 6);

	_animations[DROP | DESTROY] = new Animation(_sprite, 0.1f);
	_animations[DROP | DESTROY]->addFrameRect(eID::JAR, "lu_be_", 8);

	_animations[DESTROY] = new Animation(_sprite, 0.1f);
	_animations[DESTROY]->addFrameRect(eID::JAR, "lu_be_", 8);

	/*_animations[FREE|DROP] = new Animation(_sprite, 0.1f);
	_animations[FREE|DROP]->addFrameRect(eID::JAR, "lu_be_00","lu_be_01",NULL);

	_animations[FREE] = new Animation(_sprite, 0.1f);
	_animations[FREE]->addFrameRect(eID::JAR, "lu_be_00", "lu_be_01", NULL);*/

	//dm méo có throw mà m add vô là sao

	//_sprite->drawBounding(false);
	//_sprite->setOrigin(Vector2(0, 0));

}
void Jar::Update(float deltatime)
{
	//eStatus xL = this->getStatus();
	//Hiêu ứng nó là Throw|DROP, thấy sai chưa
	_animations[this->getStatus()]->Update(deltatime);

	float x = this->getPositionX();
	float y = this->getPositionY() - 10;
	this->setPosition(x, y);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}
}

void Jar::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[this->getStatus()]->Draw(spritehandle, viewport);
	//text->Draw();
}

void Jar::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Jar::onCollisionBegin(CollisionEventArg *)
{
}

void Jar::onCollisionEnd(CollisionEventArg *)
{
}

float Jar::checkCollision(BaseObject *, float)
{
	return 0.0f;
}

IComponent* Jar::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

Jar::~Jar()
{
}


void Jar::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}

void Jar::movingDown()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, -JAR_GRAVITY));
}

void Jar::Drop()
{
	float x = _originPosition.x;
	float y = _originPosition.y - 10;
	this->setPosition(x, y);
}

float Jar::distanceBetweenAladdin()
{
	float xAla = _divingSprite->getPositionX() + (_divingSprite->getBounding().right - _divingSprite->getBounding().left) / 2;
	float x = this->getPositionX();

#pragma region Test
	char str[100];
	sprintf(str, "khoang cach voi aladdin: %f", xAla - x);
	text->setText(str);
#pragma endregion
	return xAla - x;
}

float Jar::PositionY()
{
	return this->getPositionY();
}