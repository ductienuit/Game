#ifndef __BACKGROUNDBOSSFRONT_H__
#define __BACKGROUNDBOSSFRONT_H__

#include"../Objects/BaseObject.h"
#include "../FrameWork/define.h"
#include"../FrameWork/ViewPort.h"


class BackGroundBossFront :public BaseObject
{
public:
	BackGroundBossFront();
	~BackGroundBossFront();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();

};
#endif __BACKGROUNDBOSSFRONT_H__
