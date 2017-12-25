#include "EndSceneBackground.h"
EndSceneBackground::EndSceneBackground() :BaseObject(eID::BACKGROUND)
{
	InIt();
}

EndSceneBackground::~EndSceneBackground()
{
}

void EndSceneBackground::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENDSCENE_BACKGROUND);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALE_END_SCENE_BACKGROUND);
	this->setPosition(0, 0);
	//SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli.wav", 1);
}

void EndSceneBackground::Update(float deltatime)
{

}

void EndSceneBackground::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void EndSceneBackground::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}
