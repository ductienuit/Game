#include "Transformable.h"

Transformable::Transformable()
{
	_scale = Vector2(1.0f, 1.0f);
}

Transformable::~Transformable()
{
}

Vector2 Transformable::getPosition()
{
	return _position;
}

float Transformable::getPositionX()
{
	return _position.x;
}

float Transformable::getPositionY()
{
	return _position.y;
}

void Transformable::setPosition(float x, float y, float z)
{
	Vector3 v(x, y, z);
	this->setPosition(v);
}

void Transformable::setPosition(Vector3 vector)
{
	this->_position = Vector2(vector.x, vector.y);
}

void Transformable::setPosition(Vector2 position)
{
	this->_position = Vector2(position.x, position.y);
}

void Transformable::setPosition(float x, float y)
{
	this->setPositionX(x);
	this->setPositionY(y);
}

void Transformable::setPositionX(float x)
{
	if (x != _position.x)
		_position.x = x;
}

void Transformable::setPositionY(float y)
{
	if (y != _position.y)
		_position.y = y;
}

Vector2 Transformable::getPositionViewPort()
{
	return _positionViewport;
}

Vector2 Transformable::getScale()
{
	return _scale;
}

void Transformable::setScale(Vector2 scale)
{
	if (scale == _scale)
		return;

	_scale = scale;
}

void Transformable::setScale(float scale)
{
	if (scale != _scale.x || scale != _scale.y)
	{
		_scale.x = scale;
		_scale.y = scale;
	}
}

void Transformable::setScaleX(float sx)
{
	if (sx != _scale.x)
		_scale.x = sx;
}

void Transformable::setScaleY(float sy)
{
	if (sy != _scale.y)
		_scale.y = sy;
}

float Transformable::getRotate()
{
	return _rotate;
}

void Transformable::setRotate(float degree)
{
	if (degree == _rotate)
		return;

	_rotate = degree;
}

Vector2 Transformable::getOrigin()
{
	return _origin;
}

void Transformable::setOrigin(Vector2 origin)
{
	if (origin != _origin)
		_origin = origin;
}

void Transformable::setZIndex(float z)
{
	if (z != _zIndex)
		_zIndex = z;
}

float Transformable::getZIndex()
{
	return _zIndex;
}

Vector2 Transformable::getAnchorPoint()
{
	return _anchorPoint;
}
