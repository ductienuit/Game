#ifndef __SAND_H__
#define __SAND_H__


#include"../Objects/BaseObject.h"
#include "../FrameWork/define.h"
#include"../FrameWork/ViewPort.h"

class Sand :public BaseObject
{
public:
	Sand();

	~Sand();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();

};
#endif __SAND_H__

