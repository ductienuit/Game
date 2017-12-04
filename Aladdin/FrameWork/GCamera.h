#ifndef __GCAMERA_H__
#define __GCAMERA_H__

#include "define.h"

/*
GCamera là class dùng để chuyển hệ toạ độ top-left về hệ toạ độ đê-cac
là toạ độ camera trong thế giới game.
*/
class GCamera
{
public:
	GCamera();
	GCamera(float x, float y);
	GCamera(float x, float y, float width, float height);
	~GCamera();

	void setPositionWorld(Vector2 position);
	Vector2 getPositionWorld();

	float getWidth();
	float getHeight();

	//Lấy position trong viewport
	Vector3 getPositionInGCamera(Vector3* position);
	// kiểm tra hcn có nằm trong màn hình không.
	bool	isContains(const RECT &rect);

	/*
	Lấy kích thước của viewport bằng HCN, tinhs trong world lớn
	*/
	RECT getBounding();

	void UpdateCamera(int);

private:
	Vector2 _positionWorld;
	float _width;
	float _height;
};

#endif // !__GCAMERA_H__
