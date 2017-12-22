#ifndef _APPLE_H
#define _APPLE_H

#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../Score/InforAladdin.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/ViewPort.h"
#include"../Score/Alphabet.h"
#include"InforAladdin.h"
#include<string.h>

#define SCALEAPPLE2 D3DXVECTOR2(2.2f,2.2f)

class Apple :public BaseObject
{
public:
	Apple(int posX = 100, int posY = 100);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	~Apple();
private:
	map<eStatus, Animation*> _animations;
	Alphabet* _countApple;
};
#endif _APPLE_H