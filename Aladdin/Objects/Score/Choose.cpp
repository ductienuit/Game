#include "Choose.h"
Choose::Choose(int posX, int posY) :BaseObject(eID::CHOOSE)
{
	auto _input = InputController::getInstance();

	_sprite = SpriteManager::getInstance()->getSprite(eID::CHOOSE);
	this->setStatus(NORMAL);

	this->setPosition(posX*SCALEONE.x, posY*SCALEONE.y, 1.0f);
	this->setOrigin(ORIGINZERO);
	setScale(SCALEONE);
	_sprite->setFrameRect(0, 0, 5.0f, 5.0f);
	InIt();
}

void Choose::InIt()
{
	_animations[NORMAL] = new Animation(_sprite, 0.1f);
	_animations[NORMAL]->addFrameRect(eID::CHOOSE, "choose", "choose", NULL);
}

void Choose::UpdateInput(float dt)
{
	auto _input = InputController::getInstance();
	if(_input->isKeyDown(DIK_DOWN))
	{
		setPosition(120, 150, 1.0f);
	}
	else if (_input->isKeyDown(DIK_UP))
	{
		setPosition(120, 190, 1.0f);
	}
	else if (_input->isKeyDown(DIK_SPACE))
	{
		SceneManager::getInstance()->ReplaceScene(new PlayScene());
	}
}

void Choose::Update(float deltatime)
{
	_animations[NORMAL]->Update(deltatime);
}

void Choose::Draw(LPD3DXSPRITE spritehandle, ViewPort* viewport)
{
	_animations[NORMAL]->Draw(spritehandle, viewport);
}

void Choose::Release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	SAFE_DELETE(this->_sprite);
}

Choose::~Choose()
{
}
