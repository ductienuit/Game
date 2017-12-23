
#include "Land.h"


Land::Land(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type) : BaseObject(eID::LAND)
{
	_sprite = new Sprite(x, y, width,height);
	_sprite->setFrameRect(0, 0, width, height);
	_width = width;
	_height = height;
	_type = type;
}

Land::Land(int x, int y, int width, int height, eLandType type, Vector2 scale)
{
	_sprite = new Sprite(x, y, width, height,scale);
	_sprite->setFrameRect(0, 0, width, height);
	_width = width;
	_height = height;
	_type = type;
}

void Land::InIt()
{
}

void Land::Update(float deltatime)
{
}

void Land::Draw(LPD3DXSPRITE spriteHandle, ViewPort* viewport)
{
}

void Land::Release()
{
}

eID Land::getId()
{
	return eID::LAND;
}

eLandType Land::getType()
{
	return _type;
}

//void Land::ShowBB()
//{
//	RECT BBox = _bound;
//	float top = WINDOWS_HEIGHT - BBox.top;
//	float left = BBox.left;
//	float right = BBox.right;
//	float bottom = WINDOWS_HEIGHT - BBox.bottom;
//
//	LPD3DXLINE line;
//	auto dv = DeviceManager::getInstance()->getDevice();
//	D3DXCreateLine(dv, &line);
//	D3DXVECTOR2 lines[] = { D3DXVECTOR2(left, top),
//		D3DXVECTOR2(right, top),
//		D3DXVECTOR2(right, bottom),
//		D3DXVECTOR2(left, bottom),
//		D3DXVECTOR2(left, top),
//		D3DXVECTOR2(right, bottom) };
//	line->SetWidth(1);
//	line->Begin();
//	line->Draw(lines, 6, 0xffffffff);
//	line->End();
//	line->Release();
//}

Land::~Land()
{
}
