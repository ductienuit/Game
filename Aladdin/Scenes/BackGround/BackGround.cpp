#include "BackGround.h".


BackGround::BackGround():BaseObject(eID::BACKGROUND)
{
}

BackGround::~BackGround()
{
}

void BackGround::InIt()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BACKGROUND);
	this->setOrigin(ORIGINZERO);//Set top left dưới 0 0
	this->setScale(SCALEMAP);
	this->setPosition(0, 0);
	//SoundManager::getInstance()->PlaySound("Resources/Audio/PrinceAli.wav", 1);
}

void BackGround::Update(float deltatime)
{
	
}

void BackGround::Draw(LPD3DXSPRITE spriteHandle, ViewPort *viewport)
{
	_sprite->Render(spriteHandle,viewport);
}

void BackGround::Release()
{
	_sprite->Release();
	_sprite = nullptr;
}
