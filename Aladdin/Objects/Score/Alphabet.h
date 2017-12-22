#ifndef _ALPHABET_H
#define _ALPHABET_H

#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../Score/InforAladdin.h"
#include"../../FrameWork/Animation.h"
#include"../../FrameWork/ViewPort.h"
#include"../Score/Letter.h"

#define SCALEALPHABET D3DXVECTOR2(2.0f,2.0f)

class Alphabet :public BaseObject
{
public:
	Alphabet(int posInCameraX, int posInCameraY);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	virtual void setScale(Vector2 scale);
	virtual void setScale(float scale);
	virtual void setScaleX(float sx);
	virtual void setScaleY(float sy);

	void setString(string str,bool isMove);

	~Alphabet();
private:
	vector<BaseObject*> _listLetter;
	Vector2 _distance;
	string _text;
	bool _isMove;
};
#endif _ALPHABET_H