
#include "BaseObject.h"

IControlable::IControlable()
{
	_input = InputController::getInstance();
}

BaseObject::BaseObject()
{
}

BaseObject::BaseObject(eID id)
{
	this->_id = id;
	this->setStatus(eStatus::NORMAL);
}

BaseObject::~BaseObject()
{
}

eID BaseObject::getId()
{
	return this->_id;
}

eStatus BaseObject::getStatus()
{
	return this->_status;
}

void BaseObject::setStatus(eStatus status)
{
	if (_status != status)
		_status = status;
}

void BaseObject::addStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() | status));
}

void BaseObject::removeStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() & ~status));
}

bool BaseObject::isInStatus(eStatus status)
{
	return (this->getStatus() & status) == status;
}

void BaseObject::clearStatus()
{
	this->setStatus(eStatus(this->getStatus() & eStatus::NORMAL));
}

Vector2 BaseObject::getPosition()
{
	return _sprite->getPosition();
}

float BaseObject::getPositionX()
{
	return _sprite->getPositionX();
}

float BaseObject::getPositionY()
{
	return _sprite->getPositionY();
}

void BaseObject::setPosition(Vector3 vector)
{
	_sprite->setPosition(vector);
}

void BaseObject::setPosition(float x, float y, float z)
{
	_sprite->setPosition(x, y, z);
}

void BaseObject::setPosition(Vector2 position)
{
	_sprite->setPosition(position);
}

void BaseObject::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);
}

void BaseObject::setPositionX(float x)
{
	_sprite->setPositionX(x);
}

void BaseObject::setPositionY(float y)
{
	_sprite->setPositionY(y);
}

Vector2 BaseObject::getScale()
{
	return _sprite->getScale();
}

void BaseObject::setScale(Vector2 scale)
{
	_sprite->setScale(scale);
}

void BaseObject::setScale(float scale)
{
	_sprite->setScale(scale);
}

void BaseObject::setScaleX(float sx)
{
	_sprite->setScaleX(sx);
}

void BaseObject::setScaleY(float sy)
{
	_sprite->setScaleY(sy);
}

Vector2 BaseObject::getOrigin()
{
	return _sprite->getOrigin();
}

void BaseObject::setOrigin(Vector2 origin)
{
	_sprite->setOrigin(origin);
}

float BaseObject::getRotate()
{
	return _sprite->getRotate();
}

void BaseObject::setRotate(float degree)
{
	_sprite->setRotate(degree);
}

void BaseObject::setZIndex(float z)
{
	_sprite->setZIndex(z);
}

float BaseObject::getZIndex()
{
	return _sprite->getZIndex();
}

void BaseObject::setOpacity(float opacity)
{
	_sprite->setOpacity(opacity);
}

float BaseObject::getOpacity()
{
	return _sprite->getOpacity();
}

void BaseObject::setColor(D3DXCOLOR color)
{
	_sprite->setColor(color);
}

D3DXCOLOR BaseObject::getColor()
{
	return _sprite->getColor();
}

void BaseObject::setCanUp(bool value)
{
	_canUp = value;
}

Vector2 BaseObject::getAnchorPoint()
{
	return _sprite->getAnchorPoint();
}

Sprite * BaseObject::getSprite()
{
	return _sprite;
}

RECT BaseObject::getBounding()
{
	return _sprite->getBounding();
}

float BaseObject::checkCollision(BaseObject * object, float dt)
{
	return 0.0f;
}

float BaseObject::checkCollision(BaseObject * object, eDirection & direction)
{
	return 0.0f;
}

Vector2 BaseObject::getVelocity()
{
	return Vector2(0, 0);
}

void BaseObject::Stop()
{
}


void BaseObject::setPhysicsBodySide(eDirection side)
{
	if (side != _physicsSide)
		_physicsSide = side;
}

eDirection BaseObject::getPhysicsBodySide()
{
	return _physicsSide;
}

void BaseObject::ShowBB()
{
	RECT BBox = getBounding();
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
}

void BaseObject::StopUp()
{
	_canUp = false;
}
