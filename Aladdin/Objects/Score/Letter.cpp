#include "Letter.h"

Letter::Letter(int posX, int posY, char text) :BaseObject(eID::LETTER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::LETTER);
	this->setStatus(NORMAL);
	this->setOrigin(ORIGINZERO);
	setScale(SCALELETTER);
	posInCamera.x = posX;
	posInCamera.y = posY;
	_text = text;
	InIt();
}

void Letter::InIt()
{
	_animations['A'] = new Animation(_sprite, 0.1f);
	_animations['A']->addFrameRect(eID::LETTER, "alphabet_0", "alphabet_0", NULL);

	_animations['B'] = new Animation(_sprite, 0.1f);
	_animations['B']->addFrameRect(eID::LETTER, "alphabet_1", "alphabet_1", NULL);

	_animations['C'] = new Animation(_sprite, 0.1f);
	_animations['C']->addFrameRect(eID::LETTER, "alphabet_2", "alphabet_2", NULL);

	_animations['D'] = new Animation(_sprite, 0.1f);
	_animations['D']->addFrameRect(eID::LETTER, "alphabet_3", "alphabet_3", NULL);

	_animations['E'] = new Animation(_sprite, 0.1f);
	_animations['E']->addFrameRect(eID::LETTER, "alphabet_4", "alphabet_4", NULL);

	_animations['F'] = new Animation(_sprite, 0.1f);
	_animations['F']->addFrameRect(eID::LETTER, "alphabet_5", "alphabet_5", NULL);

	_animations['G'] = new Animation(_sprite, 0.1f);
	_animations['G']->addFrameRect(eID::LETTER, "alphabet_6", "alphabet_6", NULL);

	_animations['H'] = new Animation(_sprite, 0.1f);
	_animations['H']->addFrameRect(eID::LETTER, "alphabet_7", "alphabet_7", NULL);

	_animations['I'] = new Animation(_sprite, 0.1f);
	_animations['I']->addFrameRect(eID::LETTER, "alphabet_8", "alphabet_8", NULL);

	_animations['J'] = new Animation(_sprite, 0.1f);
	_animations['J']->addFrameRect(eID::LETTER, "alphabet_9", "alphabet_9", NULL);

	_animations['K'] = new Animation(_sprite, 0.1f);
	_animations['K']->addFrameRect(eID::LETTER, "alphabet_10", "alphabet_10", NULL);

	_animations['L'] = new Animation(_sprite, 0.1f);
	_animations['L']->addFrameRect(eID::LETTER, "alphabet_11", "alphabet_11", NULL);

	_animations['M'] = new Animation(_sprite, 0.1f);
	_animations['M']->addFrameRect(eID::LETTER, "alphabet_12", "alphabet_12", NULL);

	_animations['N'] = new Animation(_sprite, 0.1f);
	_animations['N']->addFrameRect(eID::LETTER, "alphabet_13", "alphabet_13", NULL);

	_animations['O'] = new Animation(_sprite, 0.1f);
	_animations['O']->addFrameRect(eID::LETTER, "alphabet_14", "alphabet_14", NULL);

	_animations['P'] = new Animation(_sprite, 0.1f);
	_animations['P']->addFrameRect(eID::LETTER, "alphabet_15", "alphabet_15", NULL);

	_animations['Q'] = new Animation(_sprite, 0.1f);
	_animations['Q']->addFrameRect(eID::LETTER, "alphabet_16", "alphabet_16", NULL);

	_animations['R'] = new Animation(_sprite, 0.1f);
	_animations['R']->addFrameRect(eID::LETTER, "alphabet_17", "alphabet_17", NULL);

	_animations['S'] = new Animation(_sprite, 0.1f);
	_animations['S']->addFrameRect(eID::LETTER, "alphabet_18", "alphabet_18", NULL);

	_animations['T'] = new Animation(_sprite, 0.1f);
	_animations['T']->addFrameRect(eID::LETTER, "alphabet_19", "alphabet_19", NULL);

	_animations['U'] = new Animation(_sprite, 0.1f);
	_animations['U']->addFrameRect(eID::LETTER, "alphabet_20", "alphabet_20", NULL);

	_animations['V'] = new Animation(_sprite, 0.1f);
	_animations['V']->addFrameRect(eID::LETTER, "alphabet_21", "alphabet_21", NULL);

	_animations['W'] = new Animation(_sprite, 0.1f);
	_animations['W']->addFrameRect(eID::LETTER, "alphabet_22", "alphabet_22", NULL);

	_animations['X'] = new Animation(_sprite, 0.1f);
	_animations['X']->addFrameRect(eID::LETTER, "alphabet_23", "alphabet_23", NULL);

	_animations['Y'] = new Animation(_sprite, 0.1f);
	_animations['Y']->addFrameRect(eID::LETTER, "alphabet_24", "alphabet_24", NULL);

	_animations['Z'] = new Animation(_sprite, 0.1f);
	_animations['Z']->addFrameRect(eID::LETTER, "alphabet_25", "alphabet_25", NULL);

	_animations['0'] = new Animation(_sprite, 0.1f);
	_animations['0']->addFrameRect(eID::LETTER, "alphabet_26", "alphabet_26", NULL);

	_animations['1'] = new Animation(_sprite, 0.1f);
	_animations['1']->addFrameRect(eID::LETTER, "alphabet_27", "alphabet_27", NULL);

	_animations['2'] = new Animation(_sprite, 0.1f);
	_animations['2']->addFrameRect(eID::LETTER, "alphabet_28", "alphabet_28", NULL);

	_animations['3'] = new Animation(_sprite, 0.1f);
	_animations['3']->addFrameRect(eID::LETTER, "alphabet_29", "alphabet_29", NULL);

	_animations['4'] = new Animation(_sprite, 0.1f);
	_animations['4']->addFrameRect(eID::LETTER, "alphabet_30", "alphabet_30", NULL);

	_animations['5'] = new Animation(_sprite, 0.1f);
	_animations['5']->addFrameRect(eID::LETTER, "alphabet_31", "alphabet_31", NULL);

	_animations['6'] = new Animation(_sprite, 0.1f);
	_animations['6']->addFrameRect(eID::LETTER, "alphabet_32", "alphabet_32", NULL);

	_animations['7'] = new Animation(_sprite, 0.1f);
	_animations['7']->addFrameRect(eID::LETTER, "alphabet_33", "alphabet_33", NULL);

	_animations['8'] = new Animation(_sprite, 0.1f);
	_animations['8']->addFrameRect(eID::LETTER, "alphabet_34", "alphabet_34", NULL);

	_animations['9'] = new Animation(_sprite, 0.1f);
	_animations['9']->addFrameRect(eID::LETTER, "alphabet_35", "alphabet_35", NULL);

}

void Letter::Update(float deltatime)
{
}

void Letter::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[_text]->Draw(spritehandle, viewport);
}

void Letter::Release()
{
	SAFE_DELETE(this->_sprite);
}

Letter::~Letter()
{
}

