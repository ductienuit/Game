#include "Alphabet.h"

Alphabet::Alphabet(int posX, int posY) :BaseObject(eID::ALPHABET)
{
}

void Alphabet::InIt()
{
}

void Alphabet::Update(float deltatime)
{
}

void Alphabet::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
}

void Alphabet::Release()
{
	SAFE_DELETE(this->_sprite);
}

void Alphabet::setString(string str)
{
	_text = str;
	for each (char c in _text)
	{
		_listLetter.push_back(new Letter(100, 100, c));
	}
}
Alphabet::~Alphabet()
{
}