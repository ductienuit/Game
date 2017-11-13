#include "Rope.h"

Rope::Rope() : BaseObject(eID::ROPE)
{
	this->_sprite = SpriteManager::getInstance()->getSprite(eID::ROPE);
	this->_sprite->setScale(1.0f);
	this->_sprite->setPosition(Vector2(400, 500));
}

Rope::~Rope() {
	
};

void Rope::InIt()
{
	_animations = new Animation(_sprite, 0.12f);
	_animations->addFrameRect(eID::ROPE, "rope_0","rope_0", NULL);
}

void Rope::Update(float deltatime)
{
	//_animations->NextFrame();
}


void Rope::Draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	//this->_sprite->Render(spriteHandle, viewport);
	_animations->Draw(spriteHandle, viewport);
}

void Rope::Release()
{
	SAFE_DELETE(this->_animations);
	SAFE_DELETE(this->_sprite);
}

float Rope::checkCollision(BaseObject * object, float dt)
{
	return 0.0f;
}
