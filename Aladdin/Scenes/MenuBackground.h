#ifndef __MENUBACKGROUND_H__
#define __MENUBACKGROUND_H__
#define SCALEMENUBACKGROUND D3DXVECTOR2(1.01f, 1.1f)

#include"../Objects/BaseObject.h"
#include "../FrameWork/define.h"
#include"../FrameWork/ViewPort.h"
#include"../FrameWork/Manager/SoundManager.h"

class MenuBackground :public BaseObject
{
public:
	MenuBackground();

	~MenuBackground();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();

};
#endif __MENUBACKGROUND_H__