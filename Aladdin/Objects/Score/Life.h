#ifndef _LIFE_H
#define _LIFE_H

#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../Score/InforAladdin.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/ViewPort.h"
#include"../Score/Alphabet.h"
#include"InforAladdin.h"

#define SCALELIFE D3DXVECTOR2(2.0f, 2.0f)
#define SCALETEXTLIFE D3DXVECTOR2(1.0f, 1.0f)

class Life :public BaseObject
{
public:
	Life(int posX = 100, int posY = 100);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	~Life();
private:
	map<eStatus, Animation*> _animations;
	Alphabet* _countLife;
};
#endif _LIFE_H