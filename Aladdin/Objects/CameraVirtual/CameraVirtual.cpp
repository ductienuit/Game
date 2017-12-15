
#include "CameraVirtual.h"


CameraVirtual::CameraVirtual(Vector2 pos) : BaseObject(eID::CAMERAVIRTUAL)
{
	_sprite = new Sprite(pos.x, pos.y, WINDOWS_WIDTH,WINDOWS_HEIGHT,true);
}

void CameraVirtual::InIt()
{
	//do notthing
}

void CameraVirtual::Update(float deltatime)
{
	_sprite->Render();
}

void CameraVirtual::Draw(LPD3DXSPRITE spriteHandle, ViewPort* viewport)
{
	//do notthing
}

void CameraVirtual::Release()
{
	//do notthing
}
CameraVirtual::~CameraVirtual()
{
	//do nothing
}
