#include "BackgroundMenu.h"
BackgroundMenu::BackgroundMenu() :BaseObject(eID::BACKGROUND)
{
}

BackgroundMenu::~BackgroundMenu()
{
}

void BackgroundMenu::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::MENUBACKGROUND);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALEMENUBACKGROUND);
	this->setPosition(0, 0);
	//SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli.wav", 1);
}

void BackgroundMenu::Update(float deltatime)
{

}

void BackgroundMenu::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void BackgroundMenu::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}
