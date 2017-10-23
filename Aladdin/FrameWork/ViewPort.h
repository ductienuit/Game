#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "define.h"

/*
Viewport là class dùng để chuyển hệ toạ độ top-left về hệ toạ độ đê-cac
là toạ độ camera trong thế giới game.
*/
class Viewport
{
public:
	Viewport();
	Viewport(float x, float y);
	Viewport(float x, float y, float width, float height);
	~Viewport();

	void setPositionWorld(Vector2 position);
	Vector2 getPositionWorld();

	float getWidth();
	float getHeight();

	//Lấy position trong viewport
	Vector3 getPositionInViewport(Vector3* position);
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
