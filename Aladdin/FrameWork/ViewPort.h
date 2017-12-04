#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "define.h"

/*
ViewPort là class dùng để chuyển hệ toạ độ top-left về hệ toạ độ đê-cac
là toạ độ camera trong thế giới game.
*/
class ViewPort
{
public:
	ViewPort();
	ViewPort(float x, float y);
	ViewPort(float x, float y, float width, float height);
	~ViewPort();

	void setPositionWorld(Vector2 position);
	Vector2 getPositionWorld();

	float getWidth();
	float getHeight();


	Vector3 getPositionInViewPort(Vector3* position);

	// kiểm tra hcn có nằm trong màn hình không.
	bool	isContains(const RECT &rect);

	/*
	Lấy kích thước của viewport bằng HCN, tinhs trong world lớn
	*/
	RECT getBounding();

private:
	Vector2 _positionWorld;
	float _width;
	float _height;
};

#endif // !__VIEWPORT_H__
