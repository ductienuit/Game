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
	~ViewPort(void);
	ViewPort(void);
	ViewPort(float x, float y);
	ViewPort(float x, float y, float width, float height);


	static ViewPort*	getInstance();
	void				setPositionWorld(Vector2 position);
	Vector2				getPositionWorld();

	float				getWidth();
	float				getHeight();

	//decard to world
	Vector3				getPositionInViewPort(Vector3* position);
	//world to decard
	Vector2				convertWorldtoDecard(Vector3*);

	// kiểm tra hcn có nằm trong màn hình không.
	bool				isContains(const RECT &rect);
	/*
	Lấy kích thước của viewport bằng HCN, tinhs trong world lớn
	*/
	RECT				getBounding();

private:
	static ViewPort* _instance;
	Vector2 _positionWorld;
	float _width;
	float _height;
};

#endif // !__VIEWPORT_H__
