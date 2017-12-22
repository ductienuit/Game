#include "Alphabet.h"

Alphabet::Alphabet(int posInCameraX, int posInCameraY) :BaseObject(eID::ALPHABET)
{
	_distance.x = posInCameraX;
	_distance.y = posInCameraY;
	_sprite = SpriteManager::getInstance()->getSprite(eID::ALPHABET);
	setPosition(posInCameraX,posInCameraY);
	setScale(SCALEONE);
	setOrigin(ORIGINZERO);

	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	InIt();
}

void Alphabet::InIt()
{
}

void Alphabet::Update(float deltatime)
{
	int distance = 0;
	float posX = getPositionX();
	float posY = getPositionY();
	Vector2 newPosition;
	if (_isMove)
	{
		newPosition = ViewPort::getInstance()->getPositionWorld();
		setPosition(newPosition.x + _distance.x, newPosition.y - WINDOWS_HEIGHT + _distance.y);
	}
	posX = getPositionX();
	posY = getPositionY();
	for each(auto letter in _listLetter)
	{
		letter->setPosition(Vector2(posX+distance,posY));
		distance += 10;
	}
}

void Alphabet::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	for each(auto letter in _listLetter)
		letter->Draw(spritehandle, viewport);
}

void Alphabet::Release()
{
	SAFE_DELETE(this->_sprite);
	for each (auto c in _listLetter)
	{
		c->Release();
		delete c;
	}
	_listLetter.clear();
}

void Alphabet::setString(string str, bool isMove)
{
	if (str == _text)
		return;
	//Xoa các ký tự cũ
	for each (auto c in _listLetter)
	{
		c->Release();
		delete c;
	}
	_listLetter.clear();

	//Cài các ký tự mới vào
	_text = str;
	_isMove = isMove;
	int x = getPositionX();
	for each (char c in _text)
	{
		x += 10;
		_listLetter.push_back(new Letter(x, getPositionY(), c));
	}
}

Alphabet::~Alphabet()
{
}