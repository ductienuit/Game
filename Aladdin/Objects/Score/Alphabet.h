#ifndef _ALPHABET_H
#define _ALPHABET_H

#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../Score/InforAladdin.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/ViewPort.h"
#include"../Score/Letter.h"

#define SCALEALPHABET D3DXVECTOR2(1.0f,1.0f)

class Alphabet :public BaseObject
{
public:
	Alphabet(int posX = 100, int posY = 100);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void setString(string str);

	~Alphabet();
private:
	vector<BaseObject*> _listLetter;
	string _text;
};
#endif _ALPHABET_H