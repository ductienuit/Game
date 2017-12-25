#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__


#include"../../Objects/BaseObject.h"
#include "../../FrameWork/define.h"
#include"../../FrameWork/ViewPort.h"
#include"../../FrameWork/Manager/SoundManager.h"

class BackGround:public BaseObject
{
public:
	BackGround();

	~BackGround();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();
	
};
#endif __BACKGROUND_H__

