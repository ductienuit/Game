#ifndef __BACKGROUNDBOSS_H__
#define __BACKGROUNDBOSS_H__

#include"../Objects/BaseObject.h"
#include "../FrameWork/define.h"
#include"../FrameWork/ViewPort.h"


class BackGroundBoss :public BaseObject
{
public:
	BackGroundBoss();
	~BackGroundBoss();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();

};
#endif __BACKGROUNDBOSS_H__
