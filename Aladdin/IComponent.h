
#ifndef __ICOMPONENT_H__
#define __ICOMPONENT_H__
#include"define.h"
#include"Sprite.h"

USEGAME_FRAMEWORK

class IComponent
{
public:
	virtual void Update(float deltatime) = 0;
};

#endif // !__ICOMPONENT_H__

