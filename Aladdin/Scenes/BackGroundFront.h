#ifndef __BACKGROUNDFRONT_H__
#define __BACKGROUNDFRONT_H__

#include"../Objects/BaseObject.h"
#include "../../FrameWork/define.h"
#include"../../FrameWork/ViewPort.h"

class BackGroundFront:public BaseObject
{
public:
	BackGroundFront();
	~BackGroundFront();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();

};
#endif __BACKGROUNDFRONT_H__
