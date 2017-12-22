#include "MenuBackground.h"
MenuBackground::MenuBackground() :BaseObject(eID::BACKGROUND)
{
}

MenuBackground::~MenuBackground()
{
}

void MenuBackground::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::MENUBACKGROUND);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALEMENUBACKGROUND);
	this->setPosition(0, 0);
	//SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli.wav", 1);
}

void MenuBackground::Update(float deltatime)
{

}

void MenuBackground::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void MenuBackground::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}
