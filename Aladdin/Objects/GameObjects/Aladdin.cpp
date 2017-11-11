#include "ALADDIN.h"
/*
D:\x99\DirectX\Include
D:\x99\DirectX\Lib\x86
*/
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
	//__hook(&InputController::__eventkeyPressed, _input, &Aladdin::onKeyPressed);
	__hook(&InputController::__eventkeyReleased, _input, &Aladdin::onKeyReleased);

	_sprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ALADDIN, "standing_0"));
	_sprite->setZIndex(1.0f);
	_input = InputController::getInstance();
	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(Vector2(0, -GRAVITY), movement);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::ALADDIN, "standing_0", "standing_0", NULL);

	_animations[eStatus::NORMAL1] = new Animation(_sprite, 0.15f);
	_animations[eStatus::NORMAL1]->addFrameRect(eID::ALADDIN, "standing_", 7); //7 là số ảnh

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "jump_up_", 10);

	_animations[eStatus::JUMPING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING_RIGHT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 9);

	_animations[eStatus::JUMPING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING_LEFT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 9);

	_animations[eStatus::MOVING_RIGHT | eStatus::JUMPING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_RIGHT | eStatus::JUMPING_RIGHT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 9);

	_animations[eStatus::MOVING_LEFT | eStatus::JUMPING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_LEFT | eStatus::JUMPING_LEFT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 9);

	_animations[eStatus::LOOKING_UP] = new Animation(_sprite, 0.5f);
	_animations[eStatus::LOOKING_UP]->addFrameRect(eID::ALADDIN, "look_up_0", "look_up_1", "look_up_2", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::SITTING_DOWN] = new Animation(_sprite, 0.5f);
	_animations[eStatus::LOOKING_UP | eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "look_up_2", "look_up_1", "look_up_0", NULL);

	_animations[eStatus::SITTING_DOWN] = new Animation(_sprite, 0.2f);
	_animations[eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "sit_0", "sit_1", "sit_2", "sit_3", NULL);

	_animations[eStatus::FREE] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FREE]->addFrameRect(eID::ALADDIN, "free_", 32);

	//_animations[eStatus::DROP] = new Animation(_sprite, 0.1f);
	//_animations[eStatus::DROP]->addFrameRect(eID::ALADDIN, "drop_down_0", "drop_down_1", "drop_down_2","drop_down_3", "drop_down_4", "drop_down_5", "drop_down_6", "drop_down_7", "drop_down_8");

	_animations[eStatus::NORMAL | eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL | eStatus::THROW]->addFrameRect(eID::ALADDIN, "throw_", 5);

	_animations[eStatus::ATTACK | eStatus::SITTING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::ATTACK | eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "swing_sword_", 5);

	_animations[eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "walk_", 13);

	_animations[eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "walk_", 13);

	_animations[eStatus::SITTING_DOWN | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SITTING_DOWN | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "sit_0", "sit_1",
		"sit_2", "sit_3", NULL);

	_animations[eStatus::SITTING_DOWN | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SITTING_DOWN | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "sit_0", "sit_1",
		"sit_2", "sit_3", NULL);

	/*_animations[eStatus::LOOKING_UP | eStatus::SHOOTING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::SHOOTING]->addFrameRect(eID::ALADDIN, "shot_up_01", "shot_up_02", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "walk_shot_up_01", "walk_shot_up_02", "walk_shot_up_03", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "walk_shot_up_01", "walk_shot_up_02", "walk_shot_up_03", NULL);
	*/

	_animations[eStatus::THROW | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::THROW | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "throw_0", "throw_1",
		"throw_2", "throw_3", "throw_4", "throw_5", NULL);

	_animations[eStatus::THROW | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::THROW | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "throw_0", "throw_1",
		"throw_2", "throw_3", "throw_4", "throw_5", NULL);

	//cầm kiếm chém
	_animations[eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "swing_sword_0", "swing_sword_1", "swing_sword_2", "swing_sword_3", "swing_sword_4", NULL);
	//sit_attack ngồi đâm
	_animations[eStatus::SITTING_DOWN | eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SITTING_DOWN | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "sit_attack_0", "sit_attack_1", "sit_attack_2", "sit_attack_3", "sit_attack_4", "sit_attack_5", "sit_attack_6", NULL);


	_sprite->drawBounding(false);
	_sprite->setOrigin(Vector2(0.5f, 0.0f));


	this->setStatus(eStatus::NORMAL);

	//create stopwatch to wait time state normal or free of aladdin
	_normalAnimateStopWatch = new StopWatch();
	_firstAnimateStopWatch = new StopWatch();
}

void Aladdin::Update(float deltatime)
{
	if (_sprite->getPositionY() < TEST_LAND)
	{
		_sprite->setPositionY(TEST_LAND);

		auto gravity = (Gravity*)this->_componentList["Gravity"];
		gravity->setStatus(eGravityStatus::SHALLOWED);

		if (this->isInStatus(eStatus::JUMPING))
		{
			this->removeStatus(eStatus::JUMPING);
		}

		else if (this->isInStatus(eStatus::JUMPING_RIGHT))
		{
			this->removeStatus(eStatus::JUMPING_RIGHT);
		}

		else if (this->isInStatus(eStatus::JUMPING_LEFT))
		{
			this->removeStatus(eStatus::JUMPING_LEFT);

		}
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

	switch (_status)
	{
	case(eStatus::NORMAL):
	{
		//Change normal to free animation after 5 minute
		if (_firstAnimateStopWatch->isStopWatch(1300))
		{
			this->addStatus(eStatus::NORMAL1);
			_normalAnimateStopWatch->restart();  //Chuyển sang trạng thái normal1 thì mình khởi động lại đồng hồ đếm
		}

		if (_input->isKeyDown(DIK_LEFT))
		{
			this->addStatus(eStatus::MOVING_LEFT);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->addStatus(eStatus::MOVING_RIGHT);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			this->addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_UP))
		{
			this->addStatus(eStatus::LOOKING_UP);
		}
		else if (_input->isKeyDown(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyDown(DIK_C))
		{
			jump(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::NORMAL1):
	{
		//Line Below: Change normal to free animation after 5 minute		
		if (_normalAnimateStopWatch->isStopWatch(2000))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::FREE);
		}

		if (_input->isKeyDown(DIK_LEFT))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::MOVING_LEFT);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::MOVING_RIGHT);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_UP))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::LOOKING_UP);
		}
		else if (_input->isKeyDown(DIK_X))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyDown(DIK_C))
		{
			this->removeStatus(eStatus::NORMAL1);
			jump(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::FREE):
	{
		if (_input->isKeyDown(DIK_LEFT))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::MOVING_LEFT);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::MOVING_RIGHT);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_UP))
		{
			this->addStatus(eStatus::LOOKING_UP);
		}
		else if (_input->isKeyDown(DIK_X)) //chém
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyDown(DIK_C))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			jump(eStatus::JUMPING);
			break;
		}
	}
	case(eStatus::MOVING_LEFT):
	{
		this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);
		if (_input->isKeyDown(DIK_C))
		{
			jump(eStatus::JUMPING_LEFT);
		}
		break;
	}
	case(eStatus::MOVING_RIGHT):
	{
		this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);
		if (_input->isKeyDown(DIK_C))
		{
			jump(eStatus::JUMPING_RIGHT);
		}

		break;
	}
	case (eStatus::JUMPING):
	{
		if (_input->isKeyDown(DIK_LEFT))
			this->moveLeft();
		else if (_input->isKeyDown(DIK_RIGHT))
			this->moveRight();
		break;
	}
	case(eStatus::DROP):
	{
		//check cham dat hoac collision voi mot object
		break;
	}
	case(eStatus::SITTING_DOWN):
	{
		if (_animations[_currentAnimateIndex]->getIndex() == 3)
		{
			_animations[_currentAnimateIndex]->Stop();
		}
		if (_input->isKeyDown(DIK_LEFT))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			_sprite->setScaleX(-1);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			_sprite->setScaleX(1);
		}
		else if (_input->isKeyDown(DIK_X))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyDown(DIK_C))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			jump(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::LOOKING_UP):
	{
		if (_animations[_currentAnimateIndex]->getIndex() == 2)
		{
			_animations[_currentAnimateIndex]->Stop();
		}
		//left, right, down,x,c,z
		if (_input->isKeyDown(DIK_LEFT))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			_sprite->setScaleX(-1);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			_sprite->setScaleX(1);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->removeStatus(eStatus::LOOKING_UP);
			this->addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_X))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->removeStatus(eStatus::LOOKING_UP);
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->removeStatus(eStatus::LOOKING_UP);
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyDown(DIK_C))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->removeStatus(eStatus::FREE);
			this->removeStatus(eStatus::LOOKING_UP);
			jump(eStatus::JUMPING);
		}
		break;
	}
	}
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
//
//void Aladdin::onKeyPressed(KeyEventArg* key_event)
//{
//	if (this->isInStatus(eStatus::DYING)) //Nếu đang trong hiệu ứng chết thì dẹp
//		return;
//	switch (key_event->_key)
//	{
//	case DIK_C:
//	{
//
//		/*if (!this->isInStatus(eStatus::JUMPING) && !this->isInStatus(eStatus::DROP))
//		{
//			this->removeStatus(eStatus::SHOOTING);
//			this->addStatus(eStatus::JUMPING);
//			this->addStatus(eStatus::DROP);
//			this->jump();
//		}	*/
//		this->removeStatus(eStatus::FREE);
//		this->jump();
//		break;
//	}
//	case DIK_LEFT:
//	{
//		this->removeStatus(eStatus::FREE);
//		this->removeStatus(eStatus::SITTING_DOWN);
//		this->removeStatus(eStatus::MOVING_RIGHT);
//		this->addStatus(eStatus::MOVING_LEFT);
//
//		break;
//	}
//	case DIK_RIGHT:
//	{
//		this->removeStatus(eStatus::FREE);
//		this->removeStatus(eStatus::SITTING_DOWN);
//		this->removeStatus(eStatus::MOVING_LEFT);
//		this->addStatus(eStatus::MOVING_RIGHT);
//
//		break;
//	}
//	case DIK_DOWN:
//	{
//		this->removeStatus(eStatus::FREE);
//		this->addStatus(eStatus::SITTING_DOWN);
//		break;
//	}
//	case DIK_UP:
//	{
//		this->removeStatus(eStatus::FREE);
//		this->addStatus(eStatus::LOOKING_UP);
//		break;
//	}
//	case DIK_X:
//	{
//		this->removeStatus(eStatus::FREE);
//		this->addStatus(eStatus::SHOOTING);
//		break;
//	}
//	default:
//		break;
//	}
//}
//
void Aladdin::onKeyReleased(KeyEventArg * key_event)
{
	switch (key_event->_key)
	{
	case DIK_RIGHT:
	{
		this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);
		this->removeStatus(eStatus::MOVING_RIGHT);
	}
	case DIK_LEFT:
	{
		this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);
		this->removeStatus(eStatus::MOVING_LEFT);
	}
	case DIK_DOWN:
	{
		this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);
		this->removeStatus(eStatus::SITTING_DOWN);
	}
	case DIK_UP:
	{
		this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);
		this->removeStatus(eStatus::LOOKING_UP);
	}
	case DIK_X:
	{
		this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);
		this->removeStatus(eStatus::ATTACK);
		break;
	}
	case DIK_Z: //ném
	{
		this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);
		this->removeStatus(eStatus::THROW);
	}
	/*case DIK_C:
	{
	this->removeStatus(eStatus::JUMPING);
	break;
	}*/
	default:
		break;
	}
	if (this->isInStatus(eStatus::NORMAL))  //Restart stop watch to count time change state normal2 of Aladdin
	{
		_firstAnimateStopWatch->restart();
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

void Aladdin::jump(eStatus status)
{
	if (this->isInStatus(status))
		return;

	this->addStatus(status);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_JUMP_VEL));

	auto g = (Gravity*)this->_componentList["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Aladdin::sitDown()
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

	if (this->isInStatus(eStatus::MOVING_LEFT))
	{
		this->moveLeft();
	}
	else if (this->isInStatus(eStatus::MOVING_RIGHT))
	{
		this->moveRight();
	}
	//else if ((this->getStatus() & eStatus::SITTING_DOWN) == eStatus::SITTING_DOWN)
	//{
	//	this->sitDown();
	//}
	else if (this->isInStatus(eStatus::JUMPING_RIGHT) && this->isInStatus(eStatus::JUMPING_LEFT))
	{
		this->standing();
	}
	//else if ((this->getStatus() & eStatus::ATTACK) == eStatus::JUMPING_RIGHT)
	//{
	//	//this->sitDown();
	//}
}

void Aladdin::updateCurrentAnimateIndex()
{
	if (this->isInStatus(eStatus::JUMPING))
	{
		_currentAnimateIndex = eStatus::JUMPING;
	}
	else if (this->isInStatus(eStatus::THROW) && (this->isInStatus(eStatus::LOOKING_UP) ||
		this->isInStatus(eStatus::SITTING_DOWN)) && (this->isInStatus(eStatus::MOVING_LEFT) ||
			this->isInStatus(eStatus::MOVING_RIGHT)))
	{
		_currentAnimateIndex = (eStatus)(this->getStatus() & ~eStatus::THROW);
	}
	else if (this->isInStatus(eStatus::SITTING_DOWN) && this->isInStatus(eStatus::THROW))
	{
		_currentAnimateIndex = eStatus::SITTING_DOWN;
	}
	else
	{
		_currentAnimateIndex = this->getStatus();
	}
}
