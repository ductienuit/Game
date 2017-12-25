#ifndef __END_SCENE_BACKGROUND_H__
#define __END_SCENE_BACKGROUND_H__

#define SCALE_END_SCENE_BACKGROUND D3DXVECTOR2(1.02f, 1.1f)

#include"../../Objects/BaseObject.h"
#include "../../FrameWork/define.h"
#include"../../FrameWork/ViewPort.h"
#include"../../FrameWork/Manager/SoundManager.h"

class BackgroundEndScene :public BaseObject
{
public:
	BackgroundEndScene();

	~BackgroundEndScene();

	void InIt();
	void Update(float deltatime);
	void Draw(LPD3DXSPRITE, ViewPort*);
	void Release();

};
#endif __END_SCENE_BACKGROUND_H__