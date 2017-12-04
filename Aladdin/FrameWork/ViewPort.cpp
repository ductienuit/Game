#include "ViewPort.h"

ViewPort::ViewPort()
{
}

ViewPort::ViewPort(float x, float y)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
}

ViewPort::ViewPort(float x, float y, float width, float height)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
	_width = width;
	_height = height;
}

ViewPort::~ViewPort()
{
}

void ViewPort::setPositionWorld(Vector2 position)
{
	if (_positionWorld != position)
		_positionWorld = position;
}

Vector2 ViewPort::getPositionWorld()
{
	return _positionWorld;
}

float ViewPort::getWidth()
{
	return _width;
}

float ViewPort::getHeight()
{
	return _height;
}

Vector3 ViewPort::getPositionInViewPort(Vector3* position)
{
	D3DXMATRIX mt;
	D3DXVECTOR4 posViewPort;

	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = (-1) * _positionWorld.x;
	mt._42 = _positionWorld.y;

	D3DXVec3Transform(&posViewPort, position, &mt);

	return Vector3(posViewPort.x, posViewPort.y, posViewPort.z);
}

bool ViewPort::isContains(const RECT &rect)
{
	if (rect.right < _positionWorld.x)
		return false;
	if (rect.bottom > _positionWorld.y)
		return false;
	if (rect.left > _positionWorld.x + _width)
		return false;
	if (rect.top < _positionWorld.y - _height)
		return false;
	return true;
}

RECT ViewPort::getBounding()
{
	RECT rect;
	//rect.left = _positionWorld.x;
	//rect.bottom = WINDOW_HEIGHT - _positionWorld.y;
	//rect.top = rect.bottom + _height;
	//rect.right = rect.left + _width;

	rect.left = _positionWorld.x;
	rect.top = _positionWorld.y;
	rect.bottom = rect.top - _height;
	rect.right = rect.left + _width;

	return rect;
}

