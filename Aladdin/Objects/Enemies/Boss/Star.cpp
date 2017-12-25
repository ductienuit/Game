#include "Star.h"
extern vector<BaseObject*>	listStrip;

Star::Star(int posX, int posY, bool isLeft, Aladdin* aladdin) :BaseObject(eID::STAR)
{

	_aladdin = aladdin;
	_sprite = SpriteManager::getInstance()->getSprite(eID::STAR);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	_originPosition = Vector2(posX, posY + 100);

	Vector2 v(0, 0);
	Vector2 a(0, 0);

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;
	_listComponent["Gravity"] = new Gravity(Vector2(0, -STAR_GRAVITY), movement);

	setScale(SCALEFACTOR);
	this->setStatus(ATTACK);
	text = new Text("Arial", "", 10, 25);
	_isLeft = isLeft;
	if (isLeft)
		setPosition(posX - 15, posY + 100);
	else
		setPosition(posX + 15, posY + 100);
	InIt();
}

void Star::InIt()
{
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Star::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Star::onCollisionEnd);

	_animations[ATTACK] = new Animation(_sprite, 0.1f);
	_animations[ATTACK]->addFrameRect(eID::STAR, "star_", 3);
}

void Star::Update(float deltatime)
{

	switch (_status)
	{
	case DESTROY:
		return;
	case ATTACK:
	{
		float x = this->getPositionX();
		float y = this->getPositionY();

		Vector2 posAla = _aladdin->getPosition();
		Vector2 vAla = _aladdin->getVelocity();

		if (_isLeft)
		{
			if (x<=posAla.x)
			{
				setPosition(posAla);

				int h = rand() % 50 + 1;
				listStrip.push_back(new StripAladdin(posAla.x, posAla.y+h));

				setPosition(posAla.x, posAla.y + h);
				_aladdin->addVelocity(100);
				setStatus(DESTROY);
				return;
			}
			


			if (abs(x - posAla.x)<200)
			{
				setVelocity(vAla.y);
				if(vAla.y<0)
					setVelocity(0);
			}
			else if (y < 70)
			{
				auto gravity = (Gravity*)_listComponent["Gravity"];
				gravity->setStatus(eGravityStatus::SHALLOWED);
				setPositionY(50);
			}
			movingLeft();
		}
		else
		{
			if (x >= posAla.x)
			{
				setPosition(posAla);

				int h = rand() % 50 + 1;
				listStrip.push_back(new StripAladdin(posAla.x, posAla.y + h));

				setStatus(DESTROY);

				_aladdin->addVelocity(-100);
				return;
			}

			if (abs(x - posAla.x)<200)
			{
				setVelocity(vAla.y);
				if (vAla.y<0)
					setVelocity(0);
			}
			else if (y < 70)
			{
				auto gravity = (Gravity*)_listComponent["Gravity"];
				gravity->setStatus(eGravityStatus::SHALLOWED);
				setPositionY(50);
			}

			movingRight();			
		}
		break;
	}
	break;
	}

	_animations[_status]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}

	float rotate = rand() % (359)/2;
	setRotate(rotate);
}

void Star::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[_status]->Draw(spritehandle, viewport);
}

void Star::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

void Star::onCollisionBegin(CollisionEventArg *collision_event)
{
}

void Star::onCollisionEnd(CollisionEventArg *)
{
}

float Star::checkCollision(BaseObject *object, float dt)
{
	return 0.0f;
}

IComponent* Star::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

Star::~Star()
{
}

void Star::movingLeft()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(-STAR_SPEED, move->getVelocity().y));
}

void Star::movingRight()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(STAR_SPEED, move->getVelocity().y));
}

void Star::standing()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);
}

void Star::setVelocity(float vy)
{
	auto move = (Movement*)this->_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, vy));
}
