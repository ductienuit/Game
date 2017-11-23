#include "Sprite.h"
USEGAME_FRAMEWORK

Sprite::~Sprite()
{
	//	this->_surface->Release();
}


Sprite::Sprite(LPD3DXSPRITE spriteHandle, LPCSTR filePath, int totalFrames, int cols)
{
	_origin = Vector2(0.0f, 0.0f);
	_scale = Vector2(1.6f,1.92f);
	_zIndex = 1;
	_rotate = 0.0f;

	auto rs = _texture.LoadFromFile(spriteHandle, filePath);
	if (rs != D3D_OK)
		throw;

	_totalFrames = totalFrames;
	_columns = cols;
	_textureWidth = _texture.getWidth();
	_textureHeight = _texture.getHeight();
	_frameWidth = _textureWidth / cols;
	_frameHeight = _textureHeight * cols / totalFrames;
	_index = 0;
	_currentFrame = Vector2(0, 0);

	this->setIndex(0);
	this->UpdateBounding();

	_isDrawBounding = false;
	_surface = nullptr;

	//create surface
	DeviceManager::getInstance()->getDevice()->CreateOffscreenPlainSurface(
		WINDOWS_WIDTH,
		WINDOWS_HEIGHT,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&_surface,
		NULL
	);
}

void Sprite::Release()
{
	this->_texture.Release();
}

void Sprite::Render(LPD3DXSPRITE spriteHandle)
{
	_texture.Render(
		spriteHandle,
		&_frameRect,
		Vector2((int)_position.x, (int)_position.y),
		_scale,
		_rotate,
		_origin,
		_zIndex
	);
}

//void Sprite::Render(LPD3DXSPRITE spriteHandle, Viewport* viewport)
//{
//	_texture.render(
//		spriteHandle,
//		&_frameRect,
//		*viewport,
//		_position,
//		_scale,
//		_rotate,
//		_origin,
//		_zIndex
//	);
//
//	//Vẽ bounding để xem
//	if (_surface == nullptr || _isDrawBounding == false)
//	{
//		return;
//	}
//
//	RECT r;
//	r.top = WINDOW_HEIGHT - _bound.top;
//	r.left = _bound.left;
//	r.bottom = WINDOW_HEIGHT - _bound.bottom;
//	r.right = _bound.right;
//
//	DeviceManager::getInstance()->getDevice()->ColorFill(_surface, NULL, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
//
//	DeviceManager::getInstance()->getDevice()->StretchRect(
//		_surface,
//		NULL,
//		DeviceManager::getInstance()->getSurface(),
//		&r,
//		D3DTEXF_NONE
//	);
//}

void Sprite::Render(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_texture.Render(
		spriteHandle,
		&_frameRect,
		*viewport,
		_position,
		_scale,
		_rotate,
		_origin,
		_zIndex
	);

	//Vẽ bounding để xem
	if (_surface == nullptr || _isDrawBounding == false)
	{
		return;
	}

	RECT r;
	r.top = WINDOWS_HEIGHT - _bound.top;
	r.left = _bound.left;
	r.bottom = WINDOWS_HEIGHT - _bound.bottom;
	r.right = _bound.right;

	DeviceManager::getInstance()->getDevice()->ColorFill(_surface, NULL, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	DeviceManager::getInstance()->getDevice()->StretchRect(
		_surface,
		NULL,
		DeviceManager::getInstance()->getSurface(),
		&r,
		D3DTEXF_NONE
	);
}


void Sprite::setPosition(float x, float y, float z)
{
	Vector3 v(x, y, z);
	this->setPosition(v);
}

void Sprite::setPosition(Vector3 vector)
{
	this->_position = Vector2(vector.x, vector.y);
	this->UpdateBounding();
}

void Sprite::setPosition(Vector2 position)
{
	this->_position = position;
	this->UpdateBounding();
}

void Sprite::setPositionX(float x)
{
	if (x == _position.x)
		return;

	_position.x = x;
	this->UpdateBounding();
}

void Sprite::setPositionY(float y)
{
	if (y == _position.y)
		return;

	_position.y = y;
	this->UpdateBounding();
}

void Sprite::setScale(Vector2 scale)
{
	if (scale == _scale)
		return;

	_scale = scale;
	this->UpdateBounding();
}

void Sprite::setScale(float scale)
{
	if (scale != _scale.x || scale != _scale.y)
	{
		_scale.x = scale;
		_scale.y = scale;
		this->UpdateBounding();
	}
}

void Sprite::setScaleX(float sx)
{
	if (sx == _scale.x)
		return;

	_scale.x = sx;
	this->UpdateBounding();
}

void Sprite::setScaleY(float sy)
{
	if (sy == _scale.y)
		return;

	_scale.y = sy;
	this->UpdateBounding();
}

void Sprite::setRotate(float degree)
{
	if (degree == _rotate)
		return;

	_rotate = degree;
	this->UpdateBounding();
}

void Sprite::setOrigin(Vector2 origin)
{
	if (origin == _origin)
		return;

	_origin = origin;
	_anchorPoint = Vector2(_bound.left + _frameWidth * _scale.x * _origin.x, _bound.bottom + _frameHeight * _scale.y * _origin.y);

	this->UpdateBounding();
}

void Sprite::setZIndex(float z)
{
	if (z != _zIndex)
		_zIndex = z;
}

RECT Sprite::getBounding()
{
	return _bound;
}

void Sprite::setFrameRect(RECT rect)
{
	_frameRect = rect;

	_frameWidth = abs(_frameRect.left - _frameRect.right);
	_frameHeight = abs(_frameRect.top - _frameRect.bottom);

	this->UpdateBounding();
}

void Sprite::setFrameRect(float top, float right, float bottom, float left)
{
	_frameRect.top = top;
	_frameRect.right = right;
	_frameRect.left = left;
	_frameRect.bottom = bottom;

	_frameWidth = abs(_frameRect.left - _frameRect.right);
	_frameHeight = abs(_frameRect.top - _frameRect.bottom);

	this->UpdateBounding();
}

void Sprite::setFrameRect(float x, float y, int width, int height)
{
	_frameRect.top = y;
	_frameRect.right = x + width;
	_frameRect.left = x;
	_frameRect.bottom = y + height;

	_frameWidth = width;
	_frameHeight = height;

	this->UpdateBounding();
}

RECT Sprite::getFrameRect()
{
	return _frameRect;
}

RECT Sprite::getFrameRectByIndex(int index)
{
	index = index % _totalFrames;
	RECT rect;
	rect.left = (long)_currentFrame.x * _frameWidth;
	rect.right = _frameRect.left + _frameWidth;
	rect.top = (long)_currentFrame.y * _frameHeight;
	rect.bottom = _frameRect.top + _frameHeight;
	return rect;
}

void Sprite::nextFrame()
{
	if (_totalFrames <= 1)
		return;

	this->setIndex(_index + 1);
}

void Sprite::setIndex(int index)
{
	if (_index != index)
		_index = index;

	this->setCurrentFrame();
}

int Sprite::getFrameWidth()
{
	return _frameWidth * abs(_scale.x);
}

int Sprite::getFrameHeight()
{
	return _frameHeight * abs(_scale.y);
}

int Sprite::getTextureWidth()
{
	return _textureWidth * abs(_scale.x);
}

int Sprite::getTextureHeight()
{
	return _textureHeight * abs(_scale.y);
}

void Sprite::drawBounding(bool draw)
{
	if (draw != _isDrawBounding)
		_isDrawBounding = draw;
}

void Sprite::setOpacity(float opacity)
{
	if (_opacity == opacity)
		return;

	_opacity = opacity;
	_texture.setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, _opacity));
}

float Sprite::getOpacity()
{
	return _opacity;
}

void Sprite::setColor(D3DXCOLOR color)
{
	_color = color;
	_texture.setColor(_color);
}

D3DXCOLOR Sprite::getColor()
{
	return _color;
}

void Sprite::setFrameRect()
{
	this->_frameRect.left = (long)_currentFrame.x * _frameWidth;
	this->_frameRect.right = _frameRect.left + _frameWidth;
	this->_frameRect.top = (long)_currentFrame.y * _frameHeight;
	this->_frameRect.bottom = _frameRect.top + _frameHeight;
}

void Sprite::setCurrentFrame()
{
	if (_index >= _totalFrames)
		_index = _index % _totalFrames;

	this->_currentFrame.x = _index % _columns;
	this->_currentFrame.y = _index / _columns;

	this->setFrameRect();
}

void Sprite::UpdateBounding()
{
	float scaleW = _frameWidth * abs(_scale.x);
	float scaleH = _frameHeight * abs(_scale.y);

	this->_bound.left = _position.x - scaleW * _origin.x;
	this->_bound.bottom = _position.y - scaleH * _origin.y;
	this->_bound.right = _bound.left + scaleW;
	this->_bound.top = _bound.bottom + scaleH;

	// 4 điểm của hcn
	Vector2 p1 = Vector2(_bound.left, _bound.top);
	Vector2 p2 = Vector2(_bound.right, _bound.top);
	Vector2 p3 = Vector2(_bound.right, _bound.bottom);
	Vector2 p4 = Vector2(_bound.left, _bound.bottom);
	_anchorPoint = Vector2(_bound.left + scaleW * _origin.x, _bound.bottom + scaleH * _origin.y);

	//rotate 4 điểm
	p1 = RotatePointAroundOrigin(p1, _rotate, _anchorPoint);
	p2 = RotatePointAroundOrigin(p2, _rotate, _anchorPoint);
	p3 = RotatePointAroundOrigin(p3, _rotate, _anchorPoint);
	p4 = RotatePointAroundOrigin(p4, _rotate, _anchorPoint);

	_bound.left = min(min(p1.x, p2.x), min(p3.x, p4.x));
	_bound.top = max(max(p1.y, p2.y), max(p3.y, p4.y));
	_bound.right = max(max(p1.x, p2.x), max(p3.x, p4.x));
	_bound.bottom = min(min(p1.y, p2.y), min(p3.y, p4.y));
}

Vector2 Sprite::RotatePointAroundOrigin(Vector2 point, float angle, Vector2 origin)
{
	// nhân ma trận xoay
	/*
	x' = x.cos(t) - y.sin(t)
	y' = x.sin(t) + y.cos(t)	
	t là góc quay theo radian
	vậy quanh quanh 1 điểm mình dời về góc rồi quay xong dời lại
	Chi tiết:
	https://www.stdio.vn/articles/read/401/xu-ly-anh-voi-opencv-phong-to-thu-nho-va-xoay-anh
	*/

	Vector2 newPoint;
	//trừ vì sprite xoay với cái này lệch 90*
	float rad = -angle * (M_PI / 180);

	float _sin = sin(rad);
	float _cos = cos(rad);

	//dời điểm về góc
	point -= origin;

	//xoay
	newPoint.x = point.x * _cos - point.y * _sin;
	newPoint.y = point.x * _sin + point.y * _cos;

	//dời về chổ cũ
	newPoint += origin;

	return newPoint;
}
