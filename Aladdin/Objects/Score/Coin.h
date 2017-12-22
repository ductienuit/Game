#ifndef _COIN_H
#define _COIN_H

#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../Score/InforAladdin.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/ViewPort.h"
#include"../Score/Alphabet.h"
#include"InforAladdin.h"

class Coin :public BaseObject
{
public:
	Coin(int posX = 100, int posY = 100);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void UpdateStatus();

	~Coin();
private:
	map<eStatus, Animation*> _animations;
	Alphabet* _countCoin;
};
#endif _COIN_H