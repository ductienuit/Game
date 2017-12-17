#ifndef __SKY_H__
#define __SKY_H__


#include"../Objects/BaseObject.h"
#include "../FrameWork/define.h"
#include"../FrameWork/ViewPort.h"

class Sky :public BaseObject
{
public:
	Sky();

	~Sky();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();

};
#endif __SKY_H__

