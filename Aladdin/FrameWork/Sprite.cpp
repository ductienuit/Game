#include "Sprite.h"
USEGAME_FRAMEWORK

Sprite::~Sprite()
{
	//	this->_surface->Release();
}


Sprite::Sprite(LPD3DXSPRITE spriteHandle, LPCSTR filePath, int totalFrames, int cols)
{
	_origin = ORIGINCHARACTER;
	_scale = SCALECHARACTER;
	_lastScale = _scale;
	_zIndex = 1;
	_rotate = 0.0f;

	auto rs = _texture.LoadFromFile(spriteHandle, filePath);
	if (rs != D3D_OK)
		throw;

	/*Vì mình truyền vào list rectangle nên mình set tổng
		frame bằng 1 và số cột sprite là 1*/
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

Sprite::Sprite(int x, int y, int w, int h, Vector2 scale, int totalFrames, int cols)
{
	_origin = ORIGINZERO;
	_scale = scale;
	_zIndex = 0;
	_rotate = 0.0f;
	_position.x = x*scale.x; //Phải nhân để ra đúng tọa độ scale
	_position.y = y*scale.y; //background và character nhân nên position cũng vậy

	_totalFrames = totalFrames;
	_columns = cols;
	_textureWidth = w;
	_textureHeight = h;
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
	Vector3 position = Vector3(_position.x, _position.y, _zIndex);
	_texture.Render(spriteHandle, &_frameRect, _position, _scale, _rotate, _origin);
}

void Sprite::Render(LPD3DXSPRITE spriteHandle, ViewPort* viewport)
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
	this->UpdateBounding();
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
	/*_lastScale = _scale;

	if (_scale.x < 0 && sx > 0)
	{
		_scale.x = sx;
		float lastPosition = _position.x;
		float distance = abs(_bound.right - _bound.left);

		_position.x = lastPosition - distance;
		float scaleW = _frameWidth * abs(_scale.x);
		float scaleH = _frameHeight * abs(_scale.y);

		this->_bound.left = _position.x - scaleW* _origin.x;
		this->_bound.bottom = _position.y - scaleH* _origin.y;
		this->_bound.right = _bound.left + scaleW;
		this->_bound.top = _bound.bottom + scaleH;
		return;
	}
	else if (_scale.x > 0 && sx < 0)
	{
		_scale.x = sx;
		float lastPosition = _position.x;
		float distance = abs(_bound.right - _bound.left);
		_position.x = lastPosition + distance;
		float scaleW = _frameWidth * abs(_scale.x);
		float scaleH = _frameHeight * abs(_scale.y);

		this->_bound.left = _position.x - scaleW ;
		this->_bound.bottom = _position.y - scaleH;
		this->_bound.right = _bound.left + scaleW;
		this->_bound.top = _bound.bottom + scaleH;
		return;
	}*/
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

RECT Sprite::getBoundingDraw(RECT bound)
{
	UpdateBoundingDraw(bound);
	return _boundDraw;
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
	_frameRect.top = y ;
	_frameRect.right = x + width;
	_frameRect.left = x;
	_frameRect.bottom = y - height;

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

void Sprite::DrawRect(RECT BBox)
{
#pragma region Visualize collision
	float top = WINDOWS_HEIGHT - BBox.top;
	float left = BBox.left;
	float right = BBox.right;
	float bottom = WINDOWS_HEIGHT - BBox.bottom;

	LPD3DXLINE line;
	auto dv = DeviceManager::getInstance()->getDevice();
	D3DXCreateLine(dv, &line);
	D3DXVECTOR2 lines[] = { D3DXVECTOR2(left, top),
		D3DXVECTOR2(right, top),
		D3DXVECTOR2(right, bottom),
		D3DXVECTOR2(left, bottom),
		D3DXVECTOR2(left, top),
		D3DXVECTOR2(right, bottom) };
	line->SetWidth(1);
	line->Begin();
	line->Draw(lines, 6, 0xffffffff);
	line->End();
	line->Release();
#pragma endregion
}

void Sprite::UpdatePosition()
{
	Vector3 positionViewPort;
	positionViewPort = ViewPort::getInstance()->getPositionInViewPort(&Vector3(_position.x, _position.y, 1));
	_positionViewport.x = positionViewPort.x;
	_positionViewport.y = positionViewPort.y;
	this->UpdateBounding();
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

	_bound.left = min(min(p1.x, p2.x), min(p3.x, p4.x));
	_bound.top = max(max(p1.y, p2.y), max(p3.y, p4.y));
	_bound.right = max(max(p1.x, p2.x), max(p3.x, p4.x));
	_bound.bottom = min(min(p1.y, p2.y), min(p3.y, p4.y));
}

void Sprite::UpdateBoundingDraw(RECT bound)
{
	Vector3 positionViewPort;
	positionViewPort = ViewPort::getInstance()->getPositionInViewPort(&Vector3(_position.x, _position.y, 1));
	_positionViewport.x = positionViewPort.x;
	_positionViewport.y = positionViewPort.y;

	float width = abs(bound.right - bound.left);
	float height = abs(bound.top - bound.bottom);

	float scaleW = width;
	float scaleH = height;

	this->_boundDraw.left = _positionViewport.x - scaleW * _origin.x;
	this->_boundDraw.top = WINDOWS_HEIGHT - _positionViewport.y - scaleH * _origin.y;
	this->_boundDraw.right = _boundDraw.left + scaleW;
	this->_boundDraw.bottom = _boundDraw.top + scaleH;

	// 4 điểm của hcn
	Vector2 p1 = Vector2(_boundDraw.left, _boundDraw.top);
	Vector2 p2 = Vector2(_boundDraw.right, _boundDraw.top);
	Vector2 p3 = Vector2(_boundDraw.right, _boundDraw.bottom);
	Vector2 p4 = Vector2(_boundDraw.left, _boundDraw.bottom);

	_boundDraw.left = min(min(p1.x, p2.x), min(p3.x, p4.x));
	_boundDraw.top = max(max(p1.y, p2.y), max(p3.y, p4.y));
	_boundDraw.right = max(max(p1.x, p2.x), max(p3.x, p4.x));
	_boundDraw.bottom = min(min(p1.y, p2.y), min(p3.y, p4.y));

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
