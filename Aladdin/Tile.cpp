#include "Tile.h"

Tile::Tile(float x, float y, eID id, int left, int top, int right, int bottom) : BaseObject(id)
{
	this->_sprite = SpriteManager::getInstance()->getSprite(id);
	this->_sprite->setPosition(x, y);

	_animations = new Animation(_sprite, 0.1f);
	_animations->addFrameRect(left, top, right, bottom);
}

Tile::~Tile() {
	
};

void Tile::InIt()
{
}

void Tile::Update(float deltatime)
{
}


void Tile::Draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animations->Draw(spriteHandle, viewport);
}

void Tile::Release()
{
	SAFE_DELETE(this->_animations);
	SAFE_DELETE(this->_sprite);
}

void Tile::ShowBB()
{
	switch (_id)
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
	}

	RECT BBox = _sprite->getBounding();
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
	line->SetWidth(4);
	line->Begin();
	line->Draw(lines, 6, this->getColor());
	line->End();
	line->Release();
}

float Tile::checkCollision(BaseObject * object, float dt)
{
	return 0.0f;
}
