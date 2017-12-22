#ifndef _LETTER_H
#define _LETTER_H

#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../Score/InforAladdin.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/ViewPort.h"

#define SCALELETTER D3DXVECTOR2(1.0f,1.0f)

class Letter :public BaseObject
{
public:
	Letter(int posX, int posY,char text);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;


	~Letter();
private:
	char _text;
	Vector2 posInCamera;
	map<char, Animation*> _animations;
	bool _isMove;
};
#endif _LETTER_H