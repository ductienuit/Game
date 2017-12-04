#include "GCamera.h"

GCamera::GCamera()
{
	
}

GCamera::~GCamera()
{
}

GCamera::GCamera(float x, float y)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
}

GCamera::GCamera(float x, float y, float width, float height)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
	_width = width;
	_height = height;
}

void GCamera::setPositionWorld(Vector2 position)
{
	if (_positionWorld != position)
		_positionWorld = position;
}

Vector2 GCamera::getPositionWorld()
{
	return _positionWorld;
}

float GCamera::getWidth()
{
	return _width;
}

float GCamera::getHeight()
{
	return _height;
}

Vector3 GCamera::getPositionInGCamera(Vector3* position)
{
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

bool GCamera::isContains(const RECT & rect)
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

RECT GCamera::getBounding()
{
	RECT rect;

	rect.left = _positionWorld.x;
	rect.top = _positionWorld.y;
	rect.bottom = rect.top - _height;
	rect.right = rect.left + _width;

	return rect;
}


//// REVIEW
//void GCamera::UpdateCamera(int x)
//{
//	// camera ko vẽ ra ngoài
//	// luôn để player nằm giữa màn hình
//	if (x > _positionWorld.x + _width || x < _positionWorld.x)
//	{
//		_positionWorld.x = x - _width / 2;
//	}
//	if (x  < 0 - _width / 2)
//		_positionWorld.x = x - _width / 2;
//
//
//	// viewport left == left
//	if (_positionWorld.x < left)
//		_positionWorld.x = left;
//
//	// viewport right = right
//	if (_positionWorld.x + _width > right)
//		_positionWorld.x = right - _width;
//}
// Vị trí hiện tại của viewport. 

void GCamera::UpdateCamera(int x)
{
	//Vector2 current_position = _viewport->getPositionWorld();
	//Vector2 worldsize = this->background->getWorldSize();
	// Bám theo object.
	//Vector2 new_position = Vector2(max(x - 260, 0), WINDOWS_HEIGHT);		// 200 khoảng cách tối đa giữa object và map -> hardcode

	////#if(!_DEBUG)
	//// Không cho đi ngược
	//if (new_position.x < current_position.x)
	//{
	//	new_position.x = current_position.x;
	//}
	////#endif

	//// Không cho đi quá map.
	//if (new_position.x + WINDOWS_WIDTH > 4771)
	//{
	//	new_position.x = worldsize.x - WINDOWS_WIDTH;
	//}
	//_positionWorld = new_position;
}