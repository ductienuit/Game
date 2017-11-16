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
#pragma region Trang Thai Co Ban
	//__hook(&InputController::__eventkeyPressed, _input, &Aladdin::onKeyPressed);
	__hook(&InputController::__eventkeyReleased, _input, &Aladdin::onKeyReleased);

	_sprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(Vector2(0, -GRAVITY), movement);
	_componentList["CollisionBody"] = new CollisionBody(this);

	__hook(&CollisionBody::onCollisionBegin, (CollisionBody*)_componentList["CollisionBody"], &Aladdin::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, (CollisionBody*)_componentList["CollisionBody"], &Aladdin::onCollisionEnd);

	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ALADDIN, "standing_0"));
	_sprite->setZIndex(1.0f);
	_input = InputController::getInstance();

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::ALADDIN, "standing_0", "standing_0", NULL);

	_animations[eStatus::NORMAL1] = new Animation(_sprite, 0.3f);
	_animations[eStatus::NORMAL1]->addFrameRect(eID::ALADDIN, "standing_", 7); //7 là số ảnh

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "jump_up_", 10);

	_animations[eStatus::JUMPING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING_RIGHT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 9);

	_animations[eStatus::JUMPING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING_LEFT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 9);

	_animations[eStatus::MOVING_LEFT | eStatus::JUMPING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_LEFT | eStatus::JUMPING_LEFT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 9);

	_animations[eStatus::MOVING_RIGHT | eStatus::JUMPING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_RIGHT | eStatus::JUMPING_RIGHT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 9);

	_animations[eStatus::LOOKING_UP] = new Animation(_sprite, 0.2f);
	_animations[eStatus::LOOKING_UP]->addFrameRect(eID::ALADDIN, "look_up_0", "look_up_1", "look_up_2", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::SITTING_DOWN] = new Animation(_sprite, 0.5f);
	_animations[eStatus::LOOKING_UP | eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "look_up_2", "look_up_1", "look_up_0", NULL);

	_animations[eStatus::SITTING_DOWN] = new Animation(_sprite, 0.12f);
	_animations[eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "sit_0", "sit_1", "sit_2", "sit_3", NULL);

	_animations[eStatus::FREE] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FREE]->addFrameRect(eID::ALADDIN, "free_", 32);

	//_animations[eStatus::DROP] = new Animation(_sprite, 0.1f);
	//_animations[eStatus::DROP]->addFrameRect(eID::ALADDIN, "drop_down_0", "drop_down_1", "drop_down_2","drop_down_3", "drop_down_4", "drop_down_5", "drop_down_6", "drop_down_7", "drop_down_8");
#pragma endregion
#pragma region Throw Attack Moving Left Right Dying
	_animations[eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::THROW]->addFrameRect(eID::ALADDIN, "throw_", 5);

	_animations[eStatus::ATTACK | eStatus::SITTING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::ATTACK | eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "swing_sword_", 5);

	_animations[eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "walk_", 13);

	_animations[eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "walk_", 13);

	/*_animations[eStatus::LOOKING_UP | eStatus::SHOOTING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::SHOOTING]->addFrameRect(eID::ALADDIN, "shot_up_01", "shot_up_02", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "walk_shot_up_01", "walk_shot_up_02", "walk_shot_up_03", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "walk_shot_up_01", "walk_shot_up_02", "walk_shot_up_03", NULL);
	*/

	_animations[eStatus::THROW | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::THROW | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "throw_", 6);

	_animations[eStatus::THROW | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::THROW | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "throw_", 6);

	//cầm kiếm chém
	_animations[eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "swing_sword_", 5);
	//sit_attack ngồi đâm
	_animations[eStatus::SITTING_DOWN | eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SITTING_DOWN | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "sit_attack_", 7);

	_animations[eStatus::SITTING_DOWN | eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SITTING_DOWN | eStatus::THROW]->addFrameRect(eID::ALADDIN, "sit_throw_", 5);

	_animations[eStatus::JUMPING | eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING | eStatus::THROW]->addFrameRect(eID::ALADDIN, "jump_throw_", 5);

	_animations[eStatus::JUMPING_RIGHT | eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING_RIGHT | eStatus::THROW]->addFrameRect(eID::ALADDIN, "jump_throw_", 5);

	_animations[eStatus::JUMPING_LEFT | eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING_LEFT | eStatus::THROW]->addFrameRect(eID::ALADDIN, "jump_throw_", 5);

	_animations[eStatus::JUMPING_RIGHT | eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING_RIGHT | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "jump_attack_", 6);

	_animations[eStatus::JUMPING_LEFT | eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING_LEFT | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "jump_attack_", 6);

	_animations[eStatus::JUMPING | eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "jump_attack_", 6);


	_animations[eStatus::MOVING_RIGHT | eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_RIGHT | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "run_attack_0", 8);

	_animations[eStatus::MOVING_LEFT | eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_LEFT | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "run_attack_0", 8);


	_animations[eStatus::DYING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::DYING]->addFrameRect(eID::ALADDIN, "die_", 28);
#pragma endregion
#pragma region SWING
	_animations[eStatus::SWING | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "swing_0", 10);

	_animations[eStatus::SWING | eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING | eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "swing_0", 10);

	_animations[eStatus::SWING | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "swing_0", 10);

	_animations[eStatus::SWING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING]->addFrameRect(eID::ALADDIN, "swing_0", 10);

	_animations[eStatus::SWING | eStatus::FREE] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING | eStatus::FREE]->addFrameRect(eID::ALADDIN, "swing_free", 5);

	_animations[eStatus::SWING | eStatus::THROW] = new Animation(_sprite, 0.14f);
	_animations[eStatus::SWING | eStatus::THROW]->addFrameRect(eID::ALADDIN, "climb_throw_0", 5);

	_animations[eStatus::SWING | eStatus::ATTACK] = new Animation(_sprite, 0.14f);
	_animations[eStatus::SWING | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "climb_attack_0", 7);
#pragma endregion
#pragma region Attack and looking Up

	_animations[eStatus::ATTACK | eStatus::LOOKING_UP] = new Animation(_sprite, 0.1f);
	_animations[eStatus::ATTACK | eStatus::LOOKING_UP]->addFrameRect(eID::ALADDIN, "lookingup_attack_0"
		, "lookingup_attack_1"
		, "lookingup_attack_2"
		, "lookingup_attack_3"
		, "lookingup_attack_4"
		, "lookingup_attack_5"
		, "lookingup_attack_6"
		, "lookingup_attack_7"
		, "lookingup_attack_8"
		, "lookingup_attack_9"
		, "lookingup_attack_2"
		, "lookingup_attack_3"
		, "lookingup_attack_4"
		, "lookingup_attack_5"
		, "lookingup_attack_6"
		, "lookingup_attack_7"
		, "lookingup_attack_8"
		, "lookingup_attack_9"
		, "lookingup_attack_2"
		, "lookingup_attack_10"
		, "lookingup_attack_11", NULL
	);
#pragma endregion
#pragma region Climb
	_animations[eStatus::CLIMB] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMB]->addFrameRect(eID::ALADDIN, "climb_", 10);

	_animations[eStatus::CLIMB | eStatus::JUMPING] = new Animation(_sprite, 0.055f);
	_animations[eStatus::CLIMB | eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "climb_jump_0", 9);

	_animations[eStatus::CLIMB | eStatus::THROW] = new Animation(_sprite, 0.14f);
	_animations[eStatus::CLIMB | eStatus::THROW]->addFrameRect(eID::ALADDIN, "climb_throw_0", 5);

	_animations[eStatus::CLIMB | eStatus::ATTACK] = new Animation(_sprite, 0.14f);
	_animations[eStatus::CLIMB | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "climb_attack_0", 7);

	_sprite->drawBounding(false);
	_sprite->setOrigin(Vector2(0.5f, 0.0f));


	this->setStatus(eStatus::NORMAL);

	//create stopwatch to wait time state normal or free of aladdin
	_normalAnimateStopWatch = new StopWatch();
	_firstAnimateStopWatch = new StopWatch();
#pragma endregion
}

void Aladdin::Update(float deltatime)
{
	if (_sprite->getPositionY() < TEST_ROPE)
	{
		_sprite->setPositionY(TEST_ROPE);
		auto gravity = (Gravity*)this->_componentList["Gravity"];
		gravity->setStatus(eGravityStatus::SHALLOWED);
		this->removeStatus(eStatus::JUMPING);
		this->standing();

		this->removeStatus(eStatus::JUMPING_RIGHT);
		this->removeStatus(eStatus::JUMPING_LEFT);
	}

	this->updateStatus(deltatime);

	//Loc dieu kien
	this->updateCurrentAnimateIndex();

	//Lọc các hiệu ứng khi nhấn một lần và thực hiện toàn bộ hiệu ứng
	//Nhấn Z sẽ render toàn bộ ảnh ném táo. Nhớ xóa removeStatus ở keyRelease
	this->updateStatusOneAction(deltatime);

	if (this->isInStatus(eStatus::CLIMB) || this->isInStatus(eStatus::SWING))
	{
		if(this->isInStatus(eStatus::ATTACK) || this->isInStatus(eStatus::THROW)||this->isInStatus(eStatus::JUMPING))
			_animations[_currentAnimateIndex]->Update(deltatime);		
	}
	else _animations[_currentAnimateIndex]->Update(deltatime);

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
		//Change normal to free animation after 4 second
		if (_firstAnimateStopWatch->isStopWatch(4000))
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
		else if (_input->isKeyPressed(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			jump(eStatus::JUMPING);
		}
		else if (_input->isKeyPressed(DIK_S))
		{
			unHookInputEvent();
			this->addStatus(eStatus::DYING);
		}
		break;
	}
	case(eStatus::NORMAL1):
	{
		//Line Below: Change normal to free animation after 5 minute		
		if (_normalAnimateStopWatch->isStopWatch(5000))
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
		else if (_input->isKeyPressed(DIK_X))
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			this->removeStatus(eStatus::NORMAL1);
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			this->removeStatus(eStatus::NORMAL1);
			jump(eStatus::JUMPING);
		}
		else if (_input->isKeyPressed(DIK_S))
		{
			unHookInputEvent();
			this->addStatus(eStatus::DYING);
		}
		break;
	}
	case(eStatus::FREE):
	{
		if (_input->isKeyDown(DIK_LEFT))
		{
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::MOVING_LEFT);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::MOVING_RIGHT);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_UP))
		{
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::LOOKING_UP);
		}
		else if (_input->isKeyPressed(DIK_X)) //chém
		{
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			this->removeStatus(eStatus::FREE);
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			this->removeStatus(eStatus::FREE);
			jump(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::MOVING_LEFT):
	{
		/*this->removeStatus(eStatus::NORMAL1);
		this->removeStatus(eStatus::FREE);*/
		if (_input->isKeyPressed(DIK_C))
		{
			this->removeStatus(eStatus::MOVING_LEFT);
			jump(eStatus::JUMPING_LEFT);
		}
		if (_input->isKeyPressed(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);  //chém
		}
		break;
	}
    case(eStatus::MOVING_RIGHT):
	{
		if (_input->isKeyPressed(DIK_C))
		{
			this->removeStatus(eStatus::MOVING_RIGHT);
			jump(eStatus::JUMPING_RIGHT);
		}
		if (_input->isKeyDown(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);  //chém
		}
		break;
	}
	case (eStatus::JUMPING_RIGHT):
	{
		if (_input->isKeyDown(DIK_LEFT))
		{
			this->moveLeft();
			this->removeStatus(eStatus::JUMPING_RIGHT);
			this->addStatus(eStatus::JUMPING_LEFT);

		}
		else if (_input->isKeyPressed(DIK_Z))
		{
			this->addStatus(eStatus::THROW);
			if (_input->isKeyDown(DIK_LEFT))
			{
				this->moveLeft();

				this->removeStatus(eStatus::THROW);
				this->addStatus(eStatus::JUMPING_LEFT);

			}
		}
		else if (_input->isKeyPressed(DIK_X))
		{

			this->addStatus(eStatus::ATTACK);
			if (_input->isKeyDown(DIK_LEFT))
			{
				this->moveLeft();
				this->removeStatus(eStatus::ATTACK);
				this->removeStatus(eStatus::THROW);
				this->addStatus(eStatus::JUMPING_LEFT);

			}
		}
		break;
	}
	case (eStatus::JUMPING_LEFT):
	{
		if (_input->isKeyDown(DIK_RIGHT))
		{
			this->moveRight();
			this->removeStatus(eStatus::JUMPING_LEFT);
			this->addStatus(eStatus::JUMPING_RIGHT);
		}
		else if (_input->isKeyPressed(DIK_Z))
		{
			this->addStatus(eStatus::THROW);
			if (_input->isKeyDown(DIK_RIGHT))
			{
				this->removeStatus(eStatus::THROW);
				this->moveRight();


				this->addStatus(eStatus::JUMPING_RIGHT);

			}
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);
			if (_input->isKeyDown(DIK_RIGHT))
			{
				this->removeStatus(eStatus::ATTACK);
				this->removeStatus(eStatus::THROW);
				this->moveRight();

				this->addStatus(eStatus::JUMPING_RIGHT);

			}
		}
		break;
	}
	case (eStatus::JUMPING):
	{
		if (_input->isKeyDown(DIK_LEFT))
			this->moveLeft();
		if (_input->isKeyDown(DIK_RIGHT))
			this->moveRight();

		else if (_input->isKeyPressed(DIK_Z))
		{
			this->addStatus(eStatus::THROW);

		}
		else if (_input->isKeyPressed(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);
		}
		break;
	}
	case(eStatus::DROP):
	{
		//check cham dat hoac collision voi mot object
		break;
	}
	case(eStatus::SITTING_DOWN):
	{
		if (_animations[_currentAnimateIndex]->getIndex() >= 3)
		{
			_animations[_currentAnimateIndex]->Stop();
		}
		if (_input->isKeyDown(DIK_LEFT))
		{
			_sprite->setScaleX(-1.6);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			_sprite->setScaleX(1.6);
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			this->removeStatus(eStatus::SITTING_DOWN);
			jump(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::LOOKING_UP):
	{
		if (_animations[_currentAnimateIndex]->getIndex() >= 2)
		{
			_animations[_currentAnimateIndex]->Stop();
		}
		//left, right, down,x,c,z
		if (_input->isKeyDown(DIK_LEFT))
		{
			this->removeStatus(eStatus::LOOKING_UP);
			_sprite->setScaleX(-1.6);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->removeStatus(eStatus::LOOKING_UP);
			this->removeStatus(eStatus::ATTACK);
			_sprite->setScaleX(1.6);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			this->removeStatus(eStatus::LOOKING_UP);
			this->addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			this->removeStatus(eStatus::LOOKING_UP);
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			this->removeStatus(eStatus::LOOKING_UP);
			jump(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::CLIMB):
	{
		/*Không thể remove CLIMB vì phải có collision. */
		//left, right, down,x,c,z
		if (_input->isKeyDown(DIK_LEFT))
		{
			this->_animations[_currentAnimateIndex]->Update(dt);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->_animations[_currentAnimateIndex]->UpdatePreFrame(dt);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			//Chua OptimizeA
		}
		else if (_input->isKeyDown(DIK_UP))
		{
			//Chua optimize
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			this->addStatus(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::SWING):
	{
		if (_firstAnimateStopWatch->isStopWatch(1000))
		{
			this->addStatus(eStatus::FREE);
			_normalAnimateStopWatch->restart();
		}
		if (_input->isKeyDown(DIK_LEFT))
		{	
			this->_animations[_currentAnimateIndex]->Update(dt);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->_animations[_currentAnimateIndex]->UpdatePreFrame(dt);
		}
		else if (_input->isKeyDown(DIK_UP))
		{
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			this->addStatus(eStatus::ATTACK);
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			this->addStatus(eStatus::THROW);
		}
		else if (_input->isKeyDown(DIK_C))
		{
			this->removeStatus(eStatus::SWING);
			jump(eStatus::JUMPING);
		}
		break;
	}
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
		if (this->isInStatus(eStatus::ATTACK))
		{
			//Nếu đang trong attack thì không hủy sitting_down, hủy khi thực hiện xong hành động ngồi chém
		}
		else this->removeStatus(eStatus::SITTING_DOWN);

		if (this->isInStatus(eStatus::CLIMB))
		{
		}
		else _animations[_currentAnimateIndex]->Restart(0);
		break;
	}
	case DIK_UP:
	{
		if (this->isInStatus(eStatus::ATTACK))
		{
			//Nếu đang trong attack thì không hủy look_up, hủy khi thực hiện xong hành động
		}
		else this->removeStatus(eStatus::LOOKING_UP);
		//Chạy lại hình ảnh động muốn thực hiện. bắt đầu là 0. Phải có dòng 343
		if (this->isInStatus(eStatus::CLIMB))
		{
		}
		else _animations[_currentAnimateIndex]->Restart(0);
		break;
	}
	case DIK_X:
	{
		break;
	}
	case DIK_Z: //ném
	{
		break;

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

void Aladdin::onCollisionBegin(CollisionEventArg * collision_event)
{
	if (collision_event->_otherObject->getId() == eID::ROPE)
	{
		if (collision_event->_sideCollision == eDirection::TOP)
		{
			//Chạm đất
			auto gravity = (Gravity*)this->_componentList["Gravity"];
			gravity->setStatus(eGravityStatus::SHALLOWED);
			this->removeStatus(eStatus::JUMPING);
			this->standing();
		}
		else if (collision_event->_sideCollision == eDirection::LEFT || collision_event->_sideCollision == eDirection::RIGHT)
		{
			
		}
		else if (collision_event->_sideCollision == eDirection::BOTTOM)
		{
			//Nhảy lên đụng cái gì đó
			auto gravity = (Gravity*)this->_componentList["Gravity"]; 
			gravity->setStatus(eGravityStatus::SHALLOWED);
			this->removeStatus(eStatus::JUMPING);
			this->removeStatus(eStatus::JUMPING_LEFT);
			this->removeStatus(eStatus::JUMPING_RIGHT);
			//this->addStatus(eStatus::CLIMB);
			this->addStatus(eStatus::SWING);
		}
	}
}

void Aladdin::onCollisionEnd(CollisionEventArg * collision_event)
{
	if (collision_event->_otherObject->getId() == eID::ROPE)
	{
		this->removeStatus(eStatus::CLIMB);
		this->removeStatus((eStatus)eDirection::TOP);
		this->removeStatus((eStatus)eDirection::BOTTOM);
	}
}

float Aladdin::checkCollision(BaseObject * object, float dt)
{
	auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
	collisionBody->checkCollision(object, dt);
	return 0.0f;
}

void Aladdin::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);
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

void Aladdin::standing()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(0, 0));
}

void Aladdin::moveLeft()
{
	_sprite->setScaleX(-1.6);
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(-ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::moveRight()
{
	_sprite->setScaleX(1.6);

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

void Aladdin::swingSword()
{
	if (this->isInStatus(eStatus::JUMPING))
		return;

	this->addStatus(eStatus::JUMPING);
}

void Aladdin::climbUp(float dt)
{
	this->_animations[_currentAnimateIndex]->Update(dt);
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_CLIMB_SPEED));
}

void Aladdin::climbDown(float dt)
{
	this->_animations[_currentAnimateIndex]->UpdatePreFrame(dt);
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, -ALADDIN_CLIMB_SPEED));
}

void Aladdin::climbJump()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x,50));
}

void Aladdin::swingLeft(float dt)
{
	_sprite->setScaleX(-1.6);
	this->_animations[_currentAnimateIndex]->Update(dt);
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(-ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::swingRight(float dt)
{
	_sprite->setScaleX(1.6);
	this->_animations[_currentAnimateIndex]->UpdatePreFrame(dt);
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::swingJump()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, 50));
}

Vector2 Aladdin::getVelocity()
{
	auto move = (Movement*)this->_componentList["Movement"];
	return move->getVelocity();
}

void Aladdin::updateStatus(float dt)
{
	if (this->isInStatus(eStatus::SWING))
	{
		if (this->isInStatus(eStatus::ATTACK) || this->isInStatus(eStatus::THROW))
			return;
		if (this->isInStatus(eStatus::JUMPING))
		{
			return;
		}
		if (_input->isKeyDown(DIK_LEFT))
		{
			this->swingLeft(dt);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			this->swingRight(dt);
		}
		else
		{
			this->standing();
		}
	}
	else if (this->isInStatus(eStatus::MOVING_LEFT))
	{
		this->moveLeft();
	}
	else if (this->isInStatus(eStatus::MOVING_RIGHT))
	{
		this->moveRight();
	}
	else if (this->isInStatus(eStatus::CLIMB))
	{
		if (this->isInStatus(eStatus::ATTACK) || this->isInStatus(eStatus::THROW))
			return;
		if (this->isInStatus(eStatus::JUMPING))
		{
			
			//this->removeStatus(eStatus::JUMPING);
			return;
		}
		if (_input->isKeyDown(DIK_UP))
		{
			this->climbUp(dt);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			this->climbDown(dt);
		}	
		else
		{
			this->standing();
		}
	}
	else if (!this->isInStatus(eStatus::JUMPING_RIGHT) && !this->isInStatus(eStatus::JUMPING_LEFT) && !this->isInStatus(eStatus::JUMPING) )
	{
		this->standing();
		
	}
	else if ((this->getStatus() & eStatus::ATTACK) == eStatus::JUMPING_RIGHT)
	{
		//this->sitDown();
	}

}

void Aladdin::updateStatusOneAction(float deltatime)
{
	//Kiểm tra nếu hành động nhìn lên và chém có một phím nào nhập vào, nhưng đang thực hiện
	//hành động chém chẳng hạn. Nó sẽ hủy hành động đó và chuyển sang hành động khác

#pragma region Hủy lập tức hành động nhìn lên và chém - LOOKING_UP | ATTACK
	if (this->isInStatus(eStatus::ATTACK) && (this->isInStatus(eStatus::LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() < 20
		&& _input->isKeyPressed(DIK_LEFT))
	{
		_animations[_currentAnimateIndex]->setIndex(20);
		this->removeStatus(eStatus::ATTACK);
		this->removeStatus(eStatus::LOOKING_UP);
	}
	else if (this->isInStatus(eStatus::ATTACK) && (this->isInStatus(eStatus::LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() < 20
		&& _input->isKeyPressed(DIK_RIGHT))
	{
		_animations[_currentAnimateIndex]->setIndex(20);
		this->removeStatus(eStatus::ATTACK);
		this->removeStatus(eStatus::LOOKING_UP);
	}
	else if (this->isInStatus(eStatus::ATTACK) && (this->isInStatus(eStatus::LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() < 20
		&& _input->isKeyPressed(DIK_DOWN))
	{
		_animations[_currentAnimateIndex]->setIndex(20);
		this->removeStatus(eStatus::ATTACK);
		this->removeStatus(eStatus::LOOKING_UP);
	}
	else if (this->isInStatus(eStatus::ATTACK) && (this->isInStatus(eStatus::LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() < 20
		&& _input->isKeyPressed(DIK_C))
	{
		_animations[_currentAnimateIndex]->setIndex(20);
		this->removeStatus(eStatus::ATTACK);
		this->removeStatus(eStatus::LOOKING_UP);
	}

	//Trường hợp đặc biệt, khi Climb và jump thì sẽ cho giá trị y tăng đến khi kết thúc sprite climb_jump
	else if (this->isInStatus(eStatus::JUMPING) && this->isInStatus(eStatus::CLIMB) && _animations[_currentAnimateIndex]->getIndex() < 6)
	{
		this->climbJump();
	}
#pragma endregion

#pragma region Thực hiện hết một hành động đến totalframe của một bức ảnh sprite (thực hiện hết hành động)
	if (this->isInStatus(eStatus::THROW) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);  //Quan trọng, vì nếu không set. Nhấn phím lần 2 sẽ không nhận được index.
		this->removeStatus(eStatus::THROW);
	}
	else if (this->isInStatus(eStatus::ATTACK) && (this->isInStatus(eStatus::MOVING_LEFT))
		&& _animations[_currentAnimateIndex]->getIndex() >= 7)
	{
		_animations[_currentAnimateIndex]->setIndex(8);
		this->removeStatus(eStatus::ATTACK);
		this->removeStatus(eStatus::MOVING_LEFT);
	}
	else if (this->isInStatus(eStatus::ATTACK) && (this->isInStatus(eStatus::MOVING_RIGHT))
		&& _animations[_currentAnimateIndex]->getIndex() >= 7)
	{
		_animations[_currentAnimateIndex]->setIndex(8);
		this->removeStatus(eStatus::ATTACK);
		this->removeStatus(eStatus::MOVING_RIGHT);
	}
	else if (this->isInStatus(eStatus::ATTACK) && (this->isInStatus(eStatus::LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() >= 20)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::ATTACK);
		this->removeStatus(eStatus::LOOKING_UP);
	}
	else if (this->isInStatus(eStatus::ATTACK) && (this->isInStatus(eStatus::SITTING_DOWN))
		&& _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::ATTACK);
		this->removeStatus(eStatus::SITTING_DOWN);
	}

	//CLIMB
	else if (this->isInStatus(eStatus::THROW) && this->isInStatus(eStatus::CLIMB) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::THROW);
	}
	else if (this->isInStatus(eStatus::ATTACK) && this->isInStatus(eStatus::CLIMB) && _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::ATTACK);
	}
	else if (this->isInStatus(eStatus::JUMPING) && this->isInStatus(eStatus::CLIMB) && _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::JUMPING);
		_animations[eStatus::CLIMB]->NextFrame();
	}

	//JUMP
	else if (this->isInStatus(eStatus::THROW) && this->isInStatus(eStatus::JUMPING) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::THROW);
		this->addStatus(eStatus::JUMPING);
	}
	else if (this->isInStatus(eStatus::THROW) && this->isInStatus(eStatus::JUMPING_LEFT) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::THROW);
		this->addStatus(eStatus::JUMPING_LEFT);
	}
	else if (this->isInStatus(eStatus::THROW) && this->isInStatus(eStatus::JUMPING_RIGHT) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::THROW);
		this->addStatus(eStatus::JUMPING_RIGHT);
	}
	else if (this->isInStatus(eStatus::ATTACK) && this->isInStatus(eStatus::JUMPING) && _animations[_currentAnimateIndex]->getIndex() >= 5)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::ATTACK);
		this->addStatus(eStatus::JUMPING);
	}
	else if (this->isInStatus(eStatus::ATTACK) && this->isInStatus(eStatus::JUMPING_RIGHT) && _animations[_currentAnimateIndex]->getIndex() >= 5)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::ATTACK);
		this->addStatus(eStatus::JUMPING_RIGHT);
	}
	else if (this->isInStatus(eStatus::ATTACK) && this->isInStatus(eStatus::JUMPING_LEFT) && _animations[_currentAnimateIndex]->getIndex() >= 5)
	{
		_animations[_currentAnimateIndex]->setIndex(6);
		this->removeStatus(eStatus::ATTACK);
		this->addStatus(eStatus::JUMPING_LEFT);
	}

	//SWING đu xà đu dây
	else if (this->isInStatus(eStatus::MOVING_LEFT) && this->isInStatus(eStatus::SWING) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::MOVING_LEFT);
		this->addStatus(eStatus::SWING);
	}
	else if (this->isInStatus(eStatus::MOVING_RIGHT) && this->isInStatus(eStatus::SWING) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::MOVING_RIGHT);
		this->addStatus(eStatus::SWING);
	}

	else if (this->isInStatus(eStatus::THROW) && this->isInStatus(eStatus::SWING) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::THROW);
	}
	else if (this->isInStatus(eStatus::ATTACK) && this->isInStatus(eStatus::SWING) && _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::ATTACK);
	}
	else if (this->isInStatus(eStatus::JUMPING) && this->isInStatus(eStatus::SWING) && _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::JUMPING);
		_animations[eStatus::SWING]->NextFrame();
	}
	//Thêm hiệu ứng ATTACK thì phải thêm ngoại lệ vào đây
	else if (this->isInStatus(eStatus::ATTACK) && !this->isInStatus(eStatus::LOOKING_UP)  //chém normal
		&& !this->isInStatus(eStatus::SITTING_DOWN) && !this->isInStatus(eStatus::MOVING_LEFT)
		&& !this->isInStatus(eStatus::MOVING_RIGHT) && !this->isInStatus(eStatus::JUMPING_LEFT)
		&& !this->isInStatus(eStatus::JUMPING_RIGHT) && !this->isInStatus(eStatus::JUMPING) 
		&& !this->isInStatus(eStatus::CLIMB)
		&& !this->isInStatus(eStatus::SWING)
		&& _animations[_currentAnimateIndex]->getIndex() >= 4)

	{
		_animations[_currentAnimateIndex]->setIndex(0);
		this->removeStatus(eStatus::ATTACK);
	}
#pragma endregion
}

void Aladdin::updateCurrentAnimateIndex()
{
	//if (this->isInStatus(eStatus::JUMPING))
	//{
	//	_currentAnimateIndex = eStatus::JUMPING;
	//}
	//else if (this->isInStatus(eStatus::THROW) && (this->isInStatus(eStatus::LOOKING_UP) || this->isInStatus(eStatus::SITTING_DOWN)) 
	//										  && (this->isInStatus(eStatus::MOVING_LEFT) || this->isInStatus(eStatus::MOVING_RIGHT)))
	//{
	//	_currentAnimateIndex = (eStatus)(this->getStatus() & ~eStatus::THROW);
	//}
	/*else if (this->isInStatus(eStatus::SITTING_DOWN) && this->isInStatus(eStatus::THROW))
	{
	_currentAnimateIndex = (eStatus)(eStatus::SITTING_DOWN|eStatus::THROW);
	}
	else
	{
	_currentAnimateIndex = this->getStatus();
	}*/
	//this->removeStatus(eStatus::NORMAL1);
	//this->removeStatus(eStatus::FREE);


	if (this->isInStatus(NORMAL1) &&
		(this->isInStatus(eStatus::ATTACK) ||
			this->isInStatus(eStatus::CLIMB) ||
			this->isInStatus(eStatus::DROP) ||
			this->isInStatus(eStatus::DYING) ||
			this->isInStatus(eStatus::JUMPING) ||
			this->isInStatus(eStatus::JUMPING_LEFT) ||
			this->isInStatus(eStatus::LOOKING_UP) ||
			this->isInStatus(eStatus::MOVING_LEFT) ||
			this->isInStatus(eStatus::MOVING_RIGHT) ||
			this->isInStatus(eStatus::RUNNING) ||
			this->isInStatus(eStatus::SITTING_DOWN) ||
			this->isInStatus(eStatus::SWING) ||
			this->isInStatus(eStatus::THROW)))
	{
		this->removeStatus(eStatus::NORMAL1);
		_currentAnimateIndex = (eStatus)(this->getStatus() & ~eStatus::NORMAL1);
	}
	else _currentAnimateIndex = this->getStatus();
}

void Aladdin::unHookInputEvent()
{
	if (_input != nullptr)
	{
		__unhook(_input);
	}
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