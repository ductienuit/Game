#ifndef __SCENE_H__
#define __SCENE_H__

#include"define.h"
//#include "../../FrameWork/Viewport.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN
class Scene
{
public:
	Scene();
	virtual ~Scene();

	bool virtual InIt() = 0;
	void virtual Update(float dt) = 0;   //
	void virtual UpdateInput(float dt) = 0;	
	void virtual Draw(LPD3DXSPRITE spriteHandle) = 0;
	void virtual Release() = 0;

	//Viewport*  getViewport();
protected:
	//Viewport* _viewport;
private:

};
GAME_FRAMEWORK_END
#endif // !__SCENE_H__

