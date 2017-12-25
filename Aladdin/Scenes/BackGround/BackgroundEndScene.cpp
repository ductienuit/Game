#include "BackgroundEndScene.h"
BackgroundEndScene::BackgroundEndScene() :BaseObject(eID::BACKGROUND)
{
	InIt();
}

BackgroundEndScene::~BackgroundEndScene()
{
}

void BackgroundEndScene::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENDSCENE_BACKGROUND);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALE_END_SCENE_BACKGROUND);
	this->setPosition(0, 0);
	//SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli.wav", 1);
}

void BackgroundEndScene::Update(float deltatime)
{

}

void BackgroundEndScene::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle, viewport);
}

void BackgroundEndScene::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}
