#include "ALADDIN.h"

Aladdin::Aladdin() : BaseObject(eID::ALADDIN)
{
}

Aladdin::~Aladdin()
{
	for (auto it = _animations.begin(); it != _animations.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_animations.clear();

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();

	SAFE_DELETE(_sprite);
}

void Aladdin::InIt()
{
	__hook(&InputController::__eventkeyPressed, _input, &Aladdin::onKeyPressed);
	__hook(&InputController::__eventkeyReleased, _input, &Aladdin::onKeyReleased);

	_sprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ALADDIN, "standing_0"));
	_sprite->setZIndex(1.0f);

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(Vector2(0, -GRAVITY), movement);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::ALADDIN, "standing_0", "standing_1","standing_2","standing_3","standing_4", "standing_5", "standing_6", NULL);

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "jump_up_0", "jump_up_1", "jump_up_2", "jump_up_3", "jump_up_4", "jump_up_5", "jump_up_6", "jump_up_7", "jump_up_8", "jump_up_9", NULL);

	_animations[eStatus::LOOKING_UP] = new Animation(_sprite, 0.5f);
	_animations[eStatus::LOOKING_UP]->addFrameRect(eID::ALADDIN, "look_up_0", "look_up_1", "look_up_2", NULL);

	_animations[eStatus::SITTING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "sit_0", "sit_1", "sit_2", "sit_3", NULL);

	//_animation[eStatus::DROP] = new Animation(_sprite, 0.1f);
	//_animations[eStatus::DROP]->addFrameRect(eID::ALADDIN, "drop_down_0", "drop_down_1", "drop_down_2", "drop_down_3", "drop_down_4", "drop_down_5", "drop_down_6", "drop_down_7", "drop_down_8");

	_animations[eStatus::NORMAL | eStatus::SHOOTING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL | eStatus::SHOOTING]->addFrameRect(eID::ALADDIN, "throw_0", "throw_1", "throw_2", "throw_3", "throw_4", "throw_5", NULL);

	_animations[eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "walk_1", "walk_2", "walk_3", "walk_4", "walk_5", "walk_6", "walk_7", "walk_8", "walk_9", "walk_10", "walk_11", "walk_12", NULL);

	_animations[eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "walk_1", "walk_2", "walk_3", "walk_4", "walk_5", "walk_6", "walk_7", "walk_8", "walk_9", "walk_10", "walk_11", "walk_12", NULL);
	
	_animations[eStatus::SITTING_DOWN | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SITTING_DOWN | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "sit_0", "sit_1", "sit_2", "sit_3", NULL);

	_animations[eStatus::SITTING_DOWN | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SITTING_DOWN | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "sit_0", "sit_1", "sit_2", "sit_3", NULL);

	/*_animations[eStatus::LOOKING_UP | eStatus::SHOOTING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::SHOOTING]->addFrameRect(eID::ALADDIN, "shot_up_01", "shot_up_02", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "walk_shot_up_01", "walk_shot_up_02", "walk_shot_up_03", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "walk_shot_up_01", "walk_shot_up_02", "walk_shot_up_03", NULL);

	*/
	_animations[eStatus::SHOOTING | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SHOOTING | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "throw_0", "throw_1", "throw_2", "throw_3", "throw_4", "throw_5", NULL);

	_animations[eStatus::SHOOTING | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SHOOTING | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "throw_0", "throw_1", "throw_2", "throw_3", "throw_4", "throw_5", NULL);

	_sprite->drawBounding(false);
	_sprite->setOrigin(Vector2(0.5f, 0.0f));

	this->setStatus(eStatus::NORMAL);
}

void Aladdin::Update(float deltatime)
{
	if (_sprite->getPositionY() < TEST_LAND)
	{
		_sprite->setPositionY(TEST_LAND);

		auto gravity = (Gravity*)this->_componentList["Gravity"];
		gravity->setStatus(eGravityStatus::SHALLOWED);

		this->removeStatus(eStatus::JUMPING);
		this->standing();
	}

	this->updateStatus(deltatime);

	this->updateCurrentAnimateIndex();

	_animations[_currentAnimateIndex]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->Update(deltatime);
	}

}

void Aladdin::UpdateInput(float dt)
{
}

void Aladdin::Draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animations[_currentAnimateIndex]->Draw(spriteHandle, viewport);
}

void Aladdin::Release()
{
	_sprite->Release();
	_animations.clear();
}

void Aladdin::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);
}

void Aladdin::onKeyPressed(KeyEventArg* key_event)
{
	if (this->isInStatus(eStatus::DYING)) //Nếu đang trong hiệu ứng chết thì dẹp
		return;
	switch (key_event->_key)
	{
	case DIK_C:
	{

		/*if (!this->isInStatus(eStatus::JUMPING) && !this->isInStatus(eStatus::DROP))
		{
			this->removeStatus(eStatus::SHOOTING);
			this->addStatus(eStatus::JUMPING);
			this->addStatus(eStatus::DROP);
			this->jump();
		}	*/
		this->jump();
		break;
	}
	case DIK_LEFT:
	{
		this->removeStatus(eStatus::SITTING_DOWN);
		this->removeStatus(eStatus::MOVING_RIGHT);
		this->addStatus(eStatus::MOVING_LEFT);

		break;
	}
	case DIK_RIGHT:
	{
		this->removeStatus(eStatus::SITTING_DOWN);
		this->removeStatus(eStatus::MOVING_LEFT);
		this->addStatus(eStatus::MOVING_RIGHT);

		break;
	}
	case DIK_DOWN:
	{
		this->addStatus(eStatus::SITTING_DOWN);
		break;
	}
	case DIK_UP:
	{
		this->addStatus(eStatus::LOOKING_UP);
		break;
	}
	case DIK_X:
	{
		this->addStatus(eStatus::SHOOTING);
		break;
	}
	default:
		break;
	}
}

void Aladdin::onKeyReleased(KeyEventArg * key_event)
{
	switch (key_event->_key)
	{
	case DIK_RIGHT:
	{
		this->removeStatus(eStatus::MOVING_RIGHT);
		break;
	}
	case DIK_LEFT:
	{
		this->removeStatus(eStatus::MOVING_LEFT);
		break;
	}
	case DIK_DOWN:
	{
		this->removeStatus(eStatus::SITTING_DOWN);
		break;
	}
	case DIK_UP:
	{
		this->removeStatus(eStatus::LOOKING_UP);
		break;
	}
	case DIK_X:
	{
		this->removeStatus(eStatus::SHOOTING);
		break;
	}
	default:
		break;
	}
}

void Aladdin::standing()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(0, 0));
}

void Aladdin::moveLeft()
{
	_sprite->setScaleX(-1);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(-ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::moveRight()
{
	_sprite->setScaleX(1);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::jump()
{
	if (this->isInStatus(eStatus::JUMPING) || this->isInStatus(eStatus::DROP))
		return;

	this->addStatus(eStatus::JUMPING);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_JUMP_VEL));

	auto g = (Gravity*)this->_componentList["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Aladdin::layDown()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(0, move->getVelocity().y));
}

void Aladdin::addStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() | status));
}

void Aladdin::removeStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() & ~status));
}

bool Aladdin::isInStatus(eStatus status)
{
	return (this->getStatus() & status) == status;
}

Vector2 Aladdin::getVelocity()
{
	auto move = (Movement*)this->_componentList["Movement"];
	return move->getVelocity();
}

void Aladdin::updateStatus(float dt)
{
	if ((this->getStatus() & eStatus::MOVING_LEFT) == eStatus::MOVING_LEFT)
	{
		this->moveLeft();
	}
	else if ((this->getStatus() & eStatus::MOVING_RIGHT) == eStatus::MOVING_RIGHT)
	{
		this->moveRight();
	}
	else if ((this->getStatus() & eStatus::SITTING_DOWN) == eStatus::SITTING_DOWN)
	{
		this->layDown();
	}
	else if ((this->getStatus() & eStatus::JUMPING) != eStatus::JUMPING)
	{
		this->standing();
	}
}

void Aladdin::updateCurrentAnimateIndex()
{
	if (this->isInStatus(eStatus::JUMPING))
	{
		_currentAnimateIndex = eStatus::JUMPING;
	}
	else if (this->isInStatus(eStatus::SHOOTING) && (this->isInStatus(eStatus::LOOKING_UP) ||
		this->isInStatus(eStatus::SITTING_DOWN)) && (this->isInStatus(eStatus::MOVING_LEFT) ||
			this->isInStatus(eStatus::MOVING_RIGHT)))
	{
		_currentAnimateIndex = (eStatus)(this->getStatus() & ~eStatus::SHOOTING);
	}
	else if (this->isInStatus(eStatus::SITTING_DOWN) && this->isInStatus(eStatus::SHOOTING))
	{
		_currentAnimateIndex = eStatus::SITTING_DOWN;
	}
	else
	{
		_currentAnimateIndex = this->getStatus();
	}
}
