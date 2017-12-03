#include "ViewPort.h"

Viewport::Viewport()
{
	//do nothing
}

Viewport::~Viewport()
{
}

Viewport::Viewport(float x, float y)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
}

Viewport::Viewport(float x, float y, float width, float height)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
	_width = width;
	_height = height;
}

void Viewport::setPositionWorld(Vector2 position)
{
	if (_positionWorld != position)
		_positionWorld = position;
}

Vector2 Viewport::getPositionWorld()
{
	return _positionWorld;
}

float Viewport::getWidth()
{
	return _width;
}

float Viewport::getHeight()
{
	return _height;
}

Vector3 Viewport::getPositionInViewport(Vector3* position)
{
	//D3DXMATRIX mt;
	//D3DXVECTOR4 posViewport;

	//D3DXMatrixIdentity(&mt);
	//mt._22 = -1.0f;
	//mt._41 = (-1) * _positionWorld.x;
	//mt._42 = _positionWorld.y;

	//D3DXVec3Transform(&posViewport, position, &mt);

	//return Vector3(posViewport.x, posViewport.y, posViewport.z);
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -_positionWorld.x;
	matrix._42 = _positionWorld.y;

	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, position, &matrix);

	D3DXVECTOR3 result = D3DXVECTOR3(MatrixResult.x, MatrixResult.y, MatrixResult.z);
	return result;
}

bool Viewport::isContains(const RECT & rect)
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

RECT Viewport::getBounding()
{
	RECT rect;

	rect.left = _positionWorld.x;
	rect.top = _positionWorld.y;
	rect.bottom = rect.top - _height;
	rect.right = rect.left + _width;

	return rect;
}