
#ifndef __LAND_H__
#define __LAND_H__

#include "../../../FrameWork/define.h"
#include "../../BaseObject.h"
#include "../../../FrameWork/IComponent.h"
#include"../../../FrameWork/CollisionBody.h"

class Land : public BaseObject
{
public:
	Land(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type);
	~Land();

	// Các phương thức override từ BaseObject.
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	eID getId() override;
	eLandType getType();
	//void		ShowBB();

private:
	eLandType _type;
	LPDIRECT3DSURFACE9 _surface;
	int _height;
	int _width;
	Vector3  _positionViewport;
};


#endif // !__LAND_H__