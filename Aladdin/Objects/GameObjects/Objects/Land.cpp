
#include "Land.h"


Land::Land(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type) : BaseObject(eID::LAND)
{
	// X là left. Y là top
	this->_bound.top = y;
	this->_bound.left = x;
	this->_bound.bottom = y - height;
	this->_bound.right = x + width;
	this->_type = type;
	BaseObject::setPhysicsBodySide(physicBodyDirection);

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
	this->InIt();
}

void Land::InIt()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	//this->setPhysicsBodySide(eDirection::TOP);
}

void Land::Update(float deltatime)
{
	//for (auto it : _listComponent)
	//{
	//	it.second->Update(deltatime);
	//}
}

void Land::Draw(LPD3DXSPRITE spriteHandle, ViewPort* viewport)
{
	// do nothing.
	//return;
	/*switch (_id)
	{
	case CLIMBABLE0:
		this->setColor(0xffffff00);
		break;
	
	case CLIMBABLE1:
		this->setColor(0xff00f000);
		break;
	case CLIMBABLE2:
		this->setColor(0xff00ff00);
		break;
	
	case PLATFORM:
		this->setColor(0xff00ffff);
		break;
	
	case SOLID:
		this->setColor(0xffff0000);
		break;
	
	default:
		this->setColor(0xff0000ff);
	}*/
	//RECT r;
	/*auto pos = viewport->getPositionInViewPort(new Vector3(getPositionX(), getPositionY(), 0));
	r.top = max(pos.y, 1);
	r.left = max(pos.x, 1);
	r.bottom = min(pos.y + _bound.top - _bound.bottom, WINDOWS_HEIGHT - 1);
	r.right = min(pos.x + _bound.right - _bound.left, WINDOWS_WIDTH - 1);*/
	/*r.top = WINDOWS_HEIGHT - _bound.top;
	r.left = _bound.left;
	r.right = _bound.right;
	r.bottom = WINDOWS_HEIGHT - _bound.bottom;

	DeviceManager::getInstance()->getDevice()->ColorFill(_surface, NULL, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	DeviceManager::getInstance()->getDevice()->StretchRect(
		_surface,
		NULL,
		DeviceManager::getInstance()->getSurface(),
		&r,
		D3DTEXF_NONE
	);*/
}

void Land::Release()
{
	for (auto it : _listComponent)
	{
		SAFE_DELETE(it.second);
	}
	_listComponent.clear();
}

Vector2 Land::getPosition()
{
	return Vector2(_bound.left, _bound.top);
}

float Land::getPositionX()
{
	return _bound.left;
}

float Land::getPositionY()
{
	return _bound.top;
}

float Land::getPositionBottom()
{
	return _bound.bottom;
}

void Land::setPosition(Vector3 vector)
{
	_bound.left = vector.x;
	_bound.top = vector.y;
}

void Land::setPosition(float x, float y, float z)
{
	_bound.left = x;
	_bound.top = y;
}

void Land::setPosition(Vector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

void Land::setPosition(float x, float y)
{
	_bound.left = x;
	_bound.top = y;
}

void Land::setPositionX(float x)
{
	_bound.left = x;
}

void Land::setPositionY(float y)
{
	_bound.right = y;
}

Vector2 Land::getScale()
{
	return Vector2(1,1);
}

void Land::setScale(Vector2 scale)
{
	// do nothing.
}

void Land::setScale(float scale)
{
	// do nothing.
}

void Land::setScaleX(float sx)
{
	// do nothing.
}

void Land::setScaleY(float sy)
{
	// do nothing.
}

Vector2 Land::getOrigin()
{
	return VECTOR2ZERO;
}

void Land::setOrigin(Vector2 origin)
{
	// do nothing.
}

float Land::getRotate()
{
	return 0.0f;
}

void Land::setRotate(float degree)
{
	// do nothing.
}

void Land::setZIndex(float z)
{
	// do nothing.
}

float Land::getZIndex()
{
	return 1;		// hard code
}

Vector2 Land::getAnchorPoint()
{
	return Vector2(_bound.left, _bound.right);
}

RECT Land::getBounding()
{
	return _bound;
}

eID Land::getId()
{
	return eID::LAND;
}

eLandType Land::getType()
{
	return _type;
}

void Land::ShowBB()
{
	RECT BBox = _bound;
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

Land::~Land()
{
}


//
//RECT BBox = _sprite->getBounding();
//float top = WINDOWS_HEIGHT - BBox.top;
//float left = BBox.left;
//float right = BBox.right;
//float bottom = WINDOWS_HEIGHT - BBox.bottom;
//
//LPD3DXLINE line;
//auto dv = DeviceManager::getInstance()->getDevice();
//D3DXCreateLine(dv, &line);
//D3DXVECTOR2 lines[] = { D3DXVECTOR2(left, top),
//D3DXVECTOR2(right, top),
//D3DXVECTOR2(right, bottom),
//D3DXVECTOR2(left, bottom),
//D3DXVECTOR2(left, top),
//D3DXVECTOR2(right, bottom) };
//line->SetWidth(4);
//line->Begin();
//line->Draw(lines, 6, this->getColor());
//line->End();
//line->Release();