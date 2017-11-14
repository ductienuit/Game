﻿#include "CollisionBody.h"

CollisionBody::CollisionBody(BaseObject * target)
{
	_target = target;
	_collidePosition = Vector2(0, 0);
}

CollisionBody::~CollisionBody()
{
}

void CollisionBody::checkCollision(BaseObject * otherObject, float dt)
{
	eDirection direction;
	float time = isCollide(otherObject, direction, dt);

	if (time < 1.0f)
	{
		auto v = _target->getVelocity();
		auto pos = _target->getSprite()->getPosition(); //chổ này nên _target->getPosition(); vì movement set posiion trên sprite -_-

		_target->setPosition(pos.x + (v.x * dt / 1000) * time, pos.y + (v.y * dt / 1000)  * time);
		_collidePosition = _target->getSprite()->getPosition();

		CollisionEventArg* e = new CollisionEventArg(otherObject);
		e->_sideCollision = direction;

		__raise onCollisionBegin(e);
		_isColliding = true;
	}
	else if (_isColliding)
	{
		float x, y;
		if (!isColliding(_target->getSprite()->getBounding(), otherObject->getSprite()->getBounding()))
		{
			CollisionEventArg* e = new CollisionEventArg(otherObject);
			e->_sideCollision = eDirection::NONE;

			__raise onCollisionEnd(e);
			_isColliding = false;
		}
		else
		{
			//auto pos = _target->getSprite()->getPosition();
			//_target->setPosition(pos.x + x, pos.y + y);
		}
	}
}

float CollisionBody::isCollide(BaseObject * otherSprite, eDirection & direction, float dt)
{
	RECT myRect = _target->getSprite()->getBounding();
	RECT otherRect = otherSprite->getSprite()->getBounding();

	// sử dụng Broadphase rect để kt vùng tiếp theo có va chạm ko
	RECT broadphaseRect = getSweptBroadphaseRect(_target, dt);
	if (!isColliding(broadphaseRect, otherRect))
	{
		direction = eDirection::NONE;
		return 1.0f;
	}

	//SweptAABB
	// vận tốc mỗi frame
	Vector2 velocity = Vector2(_target->getVelocity().x / dt, _target->getVelocity().y / dt);

	// tìm khoảng cách giữa cạnh gần nhất, xa nhất 2 object dx, dy
	// dx
	if (velocity.x > 0)
	{
		_dxEntry = otherRect.left - myRect.right;
		_dxExit = otherRect.right - myRect.left;
	}
	else
	{
		_dxEntry = otherRect.right - myRect.left;
		_dxExit = otherRect.left - myRect.right;
	}

	// dy
	if (velocity.y > 0)
	{
		_dyEntry = otherRect.bottom - myRect.top;
		_dyExit = otherRect.top - myRect.bottom;
	}
	else
	{
		_dyEntry = otherRect.top - myRect.bottom;
		_dyExit = otherRect.bottom - myRect.top;
	}

	// tìm thời gian va chạm 
	if (velocity.x == 0)
	{
		// chia cho 0 ra vô cực
		_txEntry = -std::numeric_limits<float>::infinity();
		_txExit = std::numeric_limits<float>::infinity();
	}

	else
	{
		_txEntry = _dxEntry / velocity.x;
		_txExit = _dxExit / velocity.x;
	}

	if (velocity.y == 0)
	{
		_tyEntry = -std::numeric_limits<float>::infinity();
		_tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		_tyEntry = _dyEntry / velocity.y;
		_tyExit = _dyExit / velocity.y;
	}

	// thời gian va chạm
	// va chạm khi x và y CÙNG chạm => thời gian va chạm trễ nhất giữa x và y
	float entryTime = max(_txEntry, _tyEntry);
	// hết va chạm là 1 trong 2 x, y hết va chạm => thời gian sớm nhất để kết thúc va chạm
	float exitTime = min(_txExit, _tyExit);

	// object không va chạm khi:
	// nếu thời gian bắt đầu va chạm hơn thời gian kết thúc va chạm
	// thời gian va chạm x, y nhỏ hơn 0 (chạy qua luôn, 2 thằng đang đi xa ra nhau)
	// thời gian va chạm x, y lớn hơn 1 (còn xa quá chưa thể va chạm) 
	if (entryTime > exitTime || _txEntry < 0.0f && _tyEntry < 0.0f || _txEntry > 1.0f || _tyEntry > 1.0f)
	{
		// không va chạm trả về 1 đi tiếp bt
		direction = eDirection::NONE;
		return 1.0f;
	}

	// nếu thời gian va chạm x lơn hơn y
	if (_txEntry > _tyEntry)
	{
		// xét x
		// khoảng cách gần nhất mà nhỏ hơn 0 nghĩa là thằng kia đang nằm bên trái object này => va chạm bên phải nó
		if (_dxEntry < 0.0f)
		{
			direction = eDirection::RIGHT;
		}
		else
		{
			direction = eDirection::LEFT;
		}
	}
	else
	{
		// xét y
		if (_dyEntry < 0.0f)
		{
			direction = eDirection::TOP;
		}
		else
		{
			direction = eDirection::BOTTOM;
		}
	}

	_collideSide = direction;

	return entryTime;
}

bool CollisionBody::isColliding(BaseObject * otherObject, float & moveX, float & moveY, float dt)
{
	moveX = moveY = 0.0f;
	auto myRect = _target->getSprite()->getBounding();
	auto otherRect = otherObject->getSprite()->getBounding();

	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	// kt coi có va chạm không
	//  CÓ va chạm khi 
	//  left < 0 && right > 0 && top > 0 && bottom < 0
	//
	if (left > 0 || right < 0 || top < 0 || bottom > 0)
		return false;

	// tính offset x, y để đi hết va chạm
	// lấy khoảng cách nhỏ nhất
	moveX = abs(left) < right ? left : right;
	moveY = abs(top) < bottom ? top : bottom;

	// chỉ lấy offset nhỏ nhất
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

bool CollisionBody::isColliding(RECT myRect, RECT otherRect)
{
	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

RECT CollisionBody::getSweptBroadphaseRect(BaseObject* object, float dt)
{
	// vận tốc mỗi frame
	auto velocity = Vector2(object->getVelocity().x / dt, object->getVelocity().y / dt);
	auto myRect = object->getSprite()->getBounding();

	RECT rect;
	rect.top = velocity.y > 0 ? myRect.top + velocity.y : myRect.top;
	rect.bottom = velocity.y > 0 ? myRect.bottom : myRect.bottom + velocity.y;
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.right = velocity.y > 0 ? myRect.right + velocity.x : myRect.right;
	return rect;
}

bool CollisionBody::isColliding()
{
	return _isColliding;
}

void CollisionBody::Update(float dt)
{

}