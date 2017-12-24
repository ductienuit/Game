#ifndef __BACKGROUNDBOSSBACK_H__
#define __BACKGROUNDBOSSBACK_H__

#include"../Objects/BaseObject.h"
#include "../FrameWork/define.h"
#include"../FrameWork/ViewPort.h"


class BackGroundBossBack :public BaseObject
{
public:
	BackGroundBossBack(int posX=0, int posY=0);
	~BackGroundBossBack();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();

};
#endif __BACKGROUNDBOSSBACK_H__
