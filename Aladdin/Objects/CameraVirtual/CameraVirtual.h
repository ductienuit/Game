#ifndef __CAMERA_VIRTUAL_H__
#define __CAMERA_VIRTUAL_H__

#include "../../FrameWork/debug.h"
#include "../../FrameWork/IComponent.h"
#include"../../FrameWork/CollisionBody.h"
#include "../BaseObject.h"

class CameraVirtual : public BaseObject
{
public:
	CameraVirtual(Vector2 pos);
	~CameraVirtual();

	// Các phương thức override từ BaseObject.
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;
	//void		ShowBB();

private:
	Vector3  _positionViewport;
};


#endif // !__CAMERA_VIRTUAL_H__