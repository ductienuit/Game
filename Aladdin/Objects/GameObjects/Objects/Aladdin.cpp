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

	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_listComponent.clear();

	SAFE_DELETE(_sprite);
}

void Aladdin::InIt()
{
	//__hook(&InputController::__eventkeyPressed, _input, &Aladdin::onKeyPressed);
	__hook(&InputController::__eventkeyReleased, _input, &Aladdin::onKeyReleased);

	_sprite = SpriteManager::getInstance()->getSprite(eID::ALADDIN);

	auto movement = new Movement(Vector2(0, 0), Vector2(0, 0), _sprite);
	_listComponent["Movement"] = movement;
	_listComponent["Gravity"] = new Gravity(Vector2(0, -GRAVITY), movement);
	_listComponent["CollisionBody"] = new CollisionBody(this);

	__hook(&CollisionBody::onCollisionBegin, (CollisionBody*)_listComponent["CollisionBody"], &Aladdin::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, (CollisionBody*)_listComponent["CollisionBody"], &Aladdin::onCollisionEnd);

	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ALADDIN, "standing_0"));
	_sprite->setZIndex(1.0f);
	_input = InputController::getInstance();

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::ALADDIN, "standing_0", "standing_0", NULL);

	_animations[eStatus::NORMAL1] = new Animation(_sprite, 0.3f);
	_animations[eStatus::NORMAL1]->addFrameRect(eID::ALADDIN, "standing_", 7); //7 là số ảnh

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.095f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "jump_up_", 10);

	_animations[eStatus::JUMPING_RIGHT] = new Animation(_sprite, 0.15f);
	_animations[eStatus::JUMPING_RIGHT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 8);

	_animations[eStatus::JUMPING_LEFT] = new Animation(_sprite, 0.15f);
	_animations[eStatus::JUMPING_LEFT]->addFrameRect(eID::ALADDIN, "jump_left_right_", 8);

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

	_animations[eStatus::CLIMB] = new Animation(_sprite, 0.15f);
	_animations[eStatus::CLIMB]->addFrameRect(eID::ALADDIN, "climb_", 10);

	_animations[eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::THROW]->addFrameRect(eID::ALADDIN, "throw_", 5);

	_animations[eStatus::ATTACK | eStatus::SITTING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::ATTACK | eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "swing_sword_", 5);

	_animations[eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "walk_", 11);

	_animations[eStatus::MOVING_LEFT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "walk_", 11);

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
	_animations[eStatus::MOVING_RIGHT | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "run_attack_0", 6);

	_animations[eStatus::MOVING_LEFT | eStatus::ATTACK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVING_LEFT | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "run_attack_0", 6);

	_animations[eStatus::DYING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::DYING]->addFrameRect(eID::ALADDIN, "die_", 28);

	_animations[eStatus::BURN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::BURN]->addFrameRect(eID::ALADDIN, "burn_", 6);

	_animations[eStatus::SWING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING]->addFrameRect(eID::ALADDIN, "swing_0", 10);

	_animations[eStatus::SWING | eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING | eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "jump_up_", 10);

	_animations[eStatus::SWING | eStatus::THROW] = new Animation(_sprite, 0.14f);
	_animations[eStatus::SWING | eStatus::THROW]->addFrameRect(eID::ALADDIN, "climb_throw_0", 5);

	_animations[eStatus::SWING | eStatus::ATTACK] = new Animation(_sprite, 0.2f);
	_animations[eStatus::SWING | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "climb_attack_0", 7);

	_animations[eStatus::ATTACK | eStatus::LOOKING_UP] = new Animation(_sprite, 0.1f);

    #pragma region Attack-LookingUp
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

	_animations[eStatus::CLIMB] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMB]->addFrameRect(eID::ALADDIN, "climb_", 10);

	_animations[eStatus::CLIMB | eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMB | eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "climb_jump_0", 9);

	_animations[eStatus::CLIMB_JUMP] = new Animation(_sprite, 0.2f);
	_animations[eStatus::CLIMB_JUMP]->addFrameRect(eID::ALADDIN, 
		"climb_jump_00", "climb_jump_01", "climb_jump_02",
		"climb_jump_03", "climb_jump_03", "climb_jump_03",
		"climb_jump_03", "climb_jump_03",
		"climb_jump_03", "climb_jump_03",NULL);

	_animations[eStatus::CLIMB | eStatus::THROW] = new Animation(_sprite, 0.14f);
	_animations[eStatus::CLIMB | eStatus::THROW]->addFrameRect(eID::ALADDIN, "climb_throw_0", 5);

	_animations[eStatus::CLIMB | eStatus::ATTACK] = new Animation(_sprite, 0.14f);
	_animations[eStatus::CLIMB | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "climb_attack_0", 7);

	_sprite->drawBounding(false);

	//Set lại bouding cho riêng aladdin để xét va chạm
	setBounding(_sprite->getBounding());

	_canUp = true;
	setStatus(eStatus::NORMAL);
	//create stopwatch to wait time state normal or free of aladdin
	_normalAnimateStopWatch = new StopWatch();
	_firstAnimateStopWatch = new StopWatch();
	this->setScale(SCALEALADDIN);

}

void Aladdin::Update(float deltatime)
{
	updateStatus(deltatime);

	//Loc dieu kien
	updateCurrentAnimateIndex();

	//Lọc các hiệu ứng khi nhấn một lần và thực hiện toàn bộ hiệu ứng
	//Nhấn Z sẽ render toàn bộ ảnh ném táo. Nhớ xóa removeStatus ở keyRelease
	updateStatusOneAction(deltatime);

	if (isInStatus(eStatus::CLIMB) || isInStatus(eStatus::SWING))
	{
		if(isInStatus(eStatus::ATTACK) || isInStatus(eStatus::THROW)||isInStatus(eStatus::JUMPING))
			_animations[_currentAnimateIndex]->Update(deltatime);		
	}
	else _animations[_currentAnimateIndex]->Update(deltatime);

	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	for (auto it = _listComponent.begin(); it != _listComponent.end(); it++)
	{
		it->second->Update(deltatime);
	}

	//Set lại bounding của aladdin
	setBounding(_sprite->getBounding());
	float x = this->getPositionX();
	float y = this->getPositionY();
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
			addStatus(eStatus::NORMAL1);
			_normalAnimateStopWatch->restart();  //Chuyển sang trạng thái normal1 thì mình khởi động lại đồng hồ đếm
		}

		if (_input->isKeyDown(DIK_LEFT))
		{
			addStatus(eStatus::MOVING_LEFT);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			addStatus(eStatus::MOVING_RIGHT);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_UP))
		{
			addStatus(eStatus::LOOKING_UP);
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			jump(eStatus::JUMPING);
		}
		else if (_input->isKeyPressed(DIK_B))
		{
			addStatus(eStatus::BURN);
		}
		else if (_input->isKeyPressed(DIK_S))
		{
			unHookInputEvent();
			addStatus(eStatus::DYING);
		}
		break;
	}
	case(eStatus::NORMAL1):
	{
		//Line Below: Change normal to free animation after 5 second		
		if (_normalAnimateStopWatch->isStopWatch(5000))
		{
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::FREE);
		}

		if (_input->isKeyDown(DIK_LEFT))
		{
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::MOVING_LEFT);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::MOVING_RIGHT);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_UP))
		{
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::LOOKING_UP);
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			removeStatus(eStatus::NORMAL1);
			jump(eStatus::JUMPING);
		}
		else if (_input->isKeyPressed(DIK_S))
		{
			unHookInputEvent();
			addStatus(eStatus::DYING);
		}
		break;
	}
	case(eStatus::FREE):
	{
		if (_input->isKeyDown(DIK_LEFT))
		{
			removeStatus(eStatus::FREE);
			addStatus(eStatus::MOVING_LEFT);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			removeStatus(eStatus::FREE);
			addStatus(eStatus::MOVING_RIGHT);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			removeStatus(eStatus::FREE);
			addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_UP))
		{
			removeStatus(eStatus::FREE);
			addStatus(eStatus::LOOKING_UP);
		}
		else if (_input->isKeyPressed(DIK_X)) //chém
		{
			removeStatus(eStatus::FREE);
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			removeStatus(eStatus::FREE);
			addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			removeStatus(eStatus::FREE);
			jump(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::MOVING_LEFT):
	{
		if (_input->isKeyPressed(DIK_C))
		{
			removeStatus(eStatus::MOVING_LEFT);
			jump(eStatus::JUMPING_LEFT);
		}
		if (_input->isKeyPressed(DIK_X))
		{
			addStatus(eStatus::ATTACK);  //chém
		}
		break;
	}
	case(eStatus::MOVING_RIGHT):
	{
		if (_input->isKeyPressed(DIK_C))
		{
			removeStatus(eStatus::MOVING_RIGHT);
			jump(eStatus::JUMPING_RIGHT);
		}
		if (_input->isKeyDown(DIK_X))
		{
			addStatus(eStatus::ATTACK);  //chém
		}
		break;
	}
	case (eStatus::JUMPING_RIGHT):
	{
		if (_input->isKeyDown(DIK_LEFT))
		{
			moveLeft();
			removeStatus(eStatus::JUMPING_RIGHT);
			addStatus(eStatus::JUMPING_LEFT);

		}
		else if (_input->isKeyPressed(DIK_Z))
		{
			addStatus(eStatus::THROW);
			if (_input->isKeyDown(DIK_LEFT))
			{
				moveLeft();
				removeStatus(eStatus::THROW);
				addStatus(eStatus::JUMPING_LEFT);
			}
		}
		else if (_input->isKeyPressed(DIK_X))
		{

			addStatus(eStatus::ATTACK);
			if (_input->isKeyDown(DIK_LEFT))
			{
				moveLeft();
				removeStatus(eStatus::ATTACK);
				removeStatus(eStatus::THROW);
				addStatus(eStatus::JUMPING_LEFT);

			}
		}
		break;
	}
	case (eStatus::JUMPING_LEFT):
	{
		if (_input->isKeyDown(DIK_RIGHT))
		{
			moveRight();
			removeStatus(eStatus::JUMPING_LEFT);
			addStatus(eStatus::JUMPING_RIGHT);
		}
		else if (_input->isKeyPressed(DIK_Z))
		{
			addStatus(eStatus::THROW);
			if (_input->isKeyDown(DIK_RIGHT))
			{
				removeStatus(eStatus::THROW);
				moveRight();


				addStatus(eStatus::JUMPING_RIGHT);

			}
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			addStatus(eStatus::ATTACK);
			if (_input->isKeyDown(DIK_RIGHT))
			{
				removeStatus(eStatus::ATTACK);
				removeStatus(eStatus::THROW);
				moveRight();

				addStatus(eStatus::JUMPING_RIGHT);

			}
		}
		break;
	}
	case (eStatus::JUMPING):
	{
		if (_input->isKeyDown(DIK_LEFT))
			moveLeft();
		if (_input->isKeyDown(DIK_RIGHT))
			moveRight();

		else if (_input->isKeyPressed(DIK_Z))
		{
			addStatus(eStatus::THROW);

		}
		else if (_input->isKeyPressed(DIK_X))
		{
			addStatus(eStatus::ATTACK);
		}
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
			_sprite->setScaleX(-SCALEALADDIN.x);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			_sprite->setScaleX(SCALEALADDIN.x);
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			removeStatus(eStatus::SITTING_DOWN);
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
			removeStatus(eStatus::LOOKING_UP);
			_sprite->setScaleX(-SCALEALADDIN.x);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			removeStatus(eStatus::LOOKING_UP);
			removeStatus(eStatus::ATTACK);
			_sprite->setScaleX(SCALEALADDIN.x);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			removeStatus(eStatus::LOOKING_UP);
			addStatus(eStatus::SITTING_DOWN);
		}
		else if (_input->isKeyDown(DIK_X))
		{
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			removeStatus(eStatus::LOOKING_UP);
			addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			removeStatus(eStatus::LOOKING_UP);
			jump(eStatus::JUMPING);
		}
		break;
	}
	case (eStatus::CLIMB_JUMP):
	{
		auto g = (Gravity*)_listComponent["Gravity"];
		g->setStatus(eGravityStatus::FALLING__DOWN);
		if (_input->isKeyPressed(DIK_LEFT))
			climbLeft();
		if (_input->isKeyPressed(DIK_RIGHT))
			climbRight();

		else if (_input->isKeyPressed(DIK_Z))
		{
			removeStatus(eStatus::CLIMB_JUMP);
			addStatus(eStatus::JUMPING);
			addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			removeStatus(eStatus::CLIMB_JUMP);
			addStatus(eStatus::JUMPING);
			addStatus(eStatus::ATTACK);
		}
		break;
	}
	case(eStatus::CLIMB):
	{
		if (_input->isKeyDown(DIK_UP))
		{
			if (_canUp == false)
			{
				Stop();
				return;
			}
			_animations[_currentAnimateIndex]->Start();
			_animations[_currentAnimateIndex]->Update(dt);
			climbUp(dt);
		}
		else if (_input->isKeyDown(DIK_DOWN))
		{
			_canUp = true;
			_animations[_currentAnimateIndex]->Start();
			_animations[_currentAnimateIndex]->UpdatePreFrame(dt);
			climbDown(dt);
		}
		else if (_input->isKeyPressed(DIK_LEFT))
		{
			Vector2 temp = getScale();
			if (temp.x > 0)
				setScaleX(-temp.x);
		}
		else if (_input->isKeyPressed(DIK_RIGHT))
		{
			_animations[_currentAnimateIndex]->setIndex(9);
			Vector2 temp = getScale();
			if (temp.x < 0)
				setScaleX(-temp.x);
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			addStatus(eStatus::ATTACK);
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			addStatus(eStatus::THROW);
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			addStatus(eStatus::JUMPING);
			climbJump();
		}
		else standing();
		break;
	}
	case(eStatus::SWING):
	{
		if (_input->isKeyDown(DIK_LEFT))
		{
			if (_sprite->getScale() > 0)
				_animations[_currentAnimateIndex]->Update(dt);
			else _animations[_currentAnimateIndex]->UpdatePreFrame(dt);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			if (_sprite->getScale() > 0)
				_animations[_currentAnimateIndex]->Update(dt);
			else
				_animations[_currentAnimateIndex]->UpdatePreFrame(dt);
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			addStatus(eStatus::ATTACK);
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			addStatus(eStatus::THROW);
		}
		else if (_input->isKeyDown(DIK_C))
		{
			//removeStatus(eStatus::SWING);
			addStatus(eStatus::JUMPING);
			swingJump();
		}
		break;
	}
	}

	if (isInStatus(eStatus::CLIMB))
	{
		if (isInStatus(eStatus::JUMPING))
		{
			if (_input->isKeyDown(DIK_LEFT))
			{
				Vector2 temp = getScale();
				if (temp.x > 0)
					setScaleX(-temp.x);
				removeStatus(eStatus::JUMPING);
				removeStatus(eStatus::CLIMB);
				addStatus(eStatus::CLIMB_JUMP);
				climbLeft();
				_animations[_currentAnimateIndex]->Begin();
			}
			else if (_input->isKeyDown(DIK_RIGHT))
			{
				Vector2 temp = getScale();
				if (temp.x < 0)
					setScaleX(-temp.x);
				removeStatus(eStatus::JUMPING);
				removeStatus(eStatus::CLIMB);
				addStatus(eStatus::CLIMB_JUMP);
				climbRight();
				_animations[_currentAnimateIndex]->Begin();
			}
		}
	}
	if (isInStatus(eStatus(SWING | JUMPING)))
	{
		if (_input->isKeyDown(DIK_LEFT))
			moveLeft();
		if (_input->isKeyDown(DIK_RIGHT))
			moveRight();
	}
}

void Aladdin::onKeyReleased(KeyEventArg * key_event)
{
	switch (key_event->_key)
	{
	case DIK_RIGHT:
	{
		removeStatus(eStatus::MOVING_RIGHT);
		standing();
		break;
	}
	case DIK_LEFT:
	{
		removeStatus(eStatus::MOVING_LEFT);
		standing();
		break;
	}
	case DIK_DOWN:
	{
		removeStatus(eStatus::SITTING_DOWN);

		if (isInStatus(eStatus::CLIMB))
		{
		}
		else _animations[_currentAnimateIndex]->Restart(0);
		break;
	}
	case DIK_UP:
	{
		if (isInStatus(eStatus::ATTACK))
		{
			//Nếu đang trong attack thì không hủy look_up, hủy khi thực hiện xong hành động
			break;
		}
		else removeStatus(eStatus::LOOKING_UP);
		//Chạy lại hình ảnh động muốn thực hiện. bắt đầu là 0. Phải có dòng 343
		if (isInStatus(eStatus::CLIMB))
		{
		}
		else _animations[_currentAnimateIndex]->Restart(0);
		standing();
		break;
	}
	case DIK_X:
	{
		//standing();
		break;
	}
	case DIK_Z: //ném
	{
		//standing();
		break;

	}
	/*case DIK_C:
	{
	removeStatus(eStatus::JUMPING);
	break;
	}*/
	default:
		break;
	}
	if (isInStatus(eStatus::NORMAL))  //Restart stop watch to count time change state normal2 of Aladdin
	{
		_firstAnimateStopWatch->restart();
	}
}

void Aladdin::onCollisionBegin(CollisionEventArg * collision_event)
{
	switch (collision_event->_otherObject->getId())
	{
	case eID::LAND:
	{

		auto land = (Land*)collision_event->_otherObject;
		eLandType type = land->getType();
		switch (collision_event->_sideCollision)
		{
			case(eDirection::TOP):
			{
				switch (type)
				{
					case (eLandType::SOLID):
					{
						//Chạm đất
						clearStatus();
						auto gravity = (Gravity*)_listComponent["Gravity"];
						gravity->setStatus(eGravityStatus::SHALLOWED);
						standing();
						break;
					}
				}
				break;
			}
			case(eDirection::BOTTOM):
			{
				switch (type)
				{
					case (eLandType::BAR):
					{
						
						if (isInStatus(eStatus(JUMPING|SWING)))
							return;
						//_preObjectColli = collision_event->_otherObject;
						clearStatus();
						addStatus(eStatus::SWING);
						float y = land->getBounding().top;
						setPositionY(y-150); //set cứng khi va chạm với Bar thì cho giảm y
						swing();
						break;
					}
					case (eLandType::STOP):
					{
						_canUp = false;
						break;
					}
					case (eLandType::CLIMBABLE0):
					{
						_canUp = true;
						clearStatus();
						addStatus(eStatus::CLIMB);
						climb();
						float x = land->getPositionX();
						setPositionX(x);
						break;
					}
				}
				break;
			}
			case(eDirection::LEFT):
			{
				switch (type)
				{
					case (eLandType::CLIMBABLE0):
					{
						clearStatus();
						_canUp = true;
						addStatus(eStatus::CLIMB);
						climb();
						float x = land->getPositionX();
						setPositionX(x);
						break;
					}
				}
				break;
			}
			case(eDirection::RIGHT):
			{
				switch (type)
				{
				case (eLandType::CLIMBABLE0):
				{
					clearStatus();
					_canUp = true;
					addStatus(eStatus::CLIMB);
					climb();
					float x = land->getPositionX();
					setPositionX(x);
					break;
				}
				}
				break;
			}
		}
		break;
	}
	}
}

void Aladdin::onCollisionEnd(CollisionEventArg * collision_event)
{

	switch (collision_event->_otherObject->getId())
	{
	case eID::LAND:
	{
		auto land = (Land*)collision_event->_otherObject;
		switch (land->getType())
		{
		case (eLandType::CLIMBABLE0):
		{
			if (isInStatus(eStatus::JUMPING))
			{
				removeStatus(CLIMB_JUMP);
				return;
			}
			removeStatus(eStatus::CLIMB);
			addStatus(eStatus::CLIMB_JUMP);
			auto g = (Gravity*)_listComponent["Gravity"];
			g->setStatus(eGravityStatus::FALLING__DOWN); 
			break;
		}
		case (eLandType::SOLID):
		{
			auto g = (Gravity*)_listComponent["Gravity"];
			g->setStatus(eGravityStatus::FALLING__DOWN);
			break;
		}
		case( eLandType::STOP):
		{
			_animations[_currentAnimateIndex]->Start();
			_canUp = true;
		}
		}
		break;
	}
	}
}

float Aladdin::checkCollision(BaseObject * object, float dt)
{
	if (object == this)
		return 0.0f;
	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	collisionBody->checkCollision(object, dt);

	return 0.0f;
}

void Aladdin::updateStatus(float dt)
{
	if (isInStatus(eStatus::SWING))
	{
		if (isInStatus(eStatus::ATTACK) || isInStatus(eStatus::THROW))
			return;
		if (isInStatus(eStatus::JUMPING))
		{
			return;
		}
		if (_input->isKeyDown(DIK_LEFT))
		{
			swingLeft(dt);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			swingRight(dt);
		}
		else
		{
			standing();
		}
	}
	else if (isInStatus(eStatus::MOVING_LEFT))
	{
		moveLeft();
	}
	else if (isInStatus(eStatus::MOVING_RIGHT))
	{
		moveRight();
	}
}

void Aladdin::updateStatusOneAction(float deltatime)
{
	//Kiểm tra nếu hành động nhìn lên và chém có một phím nào nhập vào, nhưng đang thực hiện
	//hành động chém chẳng hạn. Nó sẽ hủy hành động đó và chuyển sang hành động khác

#pragma region Hủy lập tức hành động nhìn lên và chém - LOOKING_UP | ATTACK - SWING FREE
	if (isInStatus(eStatus(ATTACK | LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() < 20
		&& _input->isKeyPressed(DIK_LEFT))
	{
		_animations[_currentAnimateIndex]->setIndex(20);
		removeStatus(eStatus::ATTACK);
		removeStatus(eStatus::LOOKING_UP);
	}
	else if (isInStatus(eStatus(ATTACK | LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() < 20
		&& _input->isKeyPressed(DIK_RIGHT))
	{
		_animations[_currentAnimateIndex]->setIndex(20);
		removeStatus(eStatus::ATTACK);
		removeStatus(eStatus::LOOKING_UP);
	}
	else if (isInStatus(eStatus(ATTACK | LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() < 20
		&& _input->isKeyPressed(DIK_DOWN))
	{
		_animations[_currentAnimateIndex]->setIndex(20);
		removeStatus(eStatus::ATTACK);
		removeStatus(eStatus::LOOKING_UP);
	}
	else if (isInStatus(eStatus(ATTACK | LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() < 20
		&& _input->isKeyPressed(DIK_C))
	{
		_animations[_currentAnimateIndex]->setIndex(20);
		removeStatus(eStatus::ATTACK);
		removeStatus(eStatus::LOOKING_UP);
	}
	//Trường hợp đặc biệt, khi Climb và jump thì sẽ cho giá trị y tăng đến khi kết thúc sprite climb_jump
	else if (isInStatus(eStatus(JUMPING | CLIMB)) && _animations[_currentAnimateIndex]->getIndex() < 6)
	{
		climbJump();
	}
#pragma endregion


	//Có các hiêu ứng trong temp trừ ATTACK
	eStatus temp = (eStatus)((LOOKING_UP | SITTING_DOWN | MOVING_LEFT
		| MOVING_RIGHT | JUMPING_LEFT | JUMPING_RIGHT
		| JUMPING | CLIMB | SWING));



#pragma region Thực hiện hết một hành động đến totalframe của một bức ảnh sprite (thực hiện hết hành động)
	if (isInStatus(eStatus::THROW) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);  //Quan trọng, vì nếu không set. Nhấn phím lần 2 sẽ không nhận được index.
		removeStatus(eStatus::THROW);
	}
	else if (isInStatus(eStatus(ATTACK | MOVING_LEFT))
		&& _animations[_currentAnimateIndex]->getIndex() >= 7)
	{
		_animations[_currentAnimateIndex]->setIndex(8);
		removeStatus(eStatus::ATTACK);
		removeStatus(eStatus::MOVING_LEFT);
	}
	else if (isInStatus(eStatus(ATTACK | MOVING_RIGHT))
		&& _animations[_currentAnimateIndex]->getIndex() >= 7)
	{
		_animations[_currentAnimateIndex]->setIndex(8);
		removeStatus(eStatus::ATTACK);
		removeStatus(eStatus::MOVING_RIGHT);
	}
	else if (isInStatus(eStatus(ATTACK | LOOKING_UP))
		&& _animations[_currentAnimateIndex]->getIndex() >= 20)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::ATTACK);
		removeStatus(eStatus::LOOKING_UP);
	}
	else if (isInStatus(eStatus(ATTACK | SITTING_DOWN))
		&& _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::ATTACK);
		removeStatus(eStatus::SITTING_DOWN);
	}

	//CLIMB
	else if (isInStatus(eStatus(THROW | CLIMB)) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::THROW);
	}
	else if (isInStatus(eStatus(ATTACK | CLIMB)) && _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::ATTACK);
	}
	else if (isInStatus(eStatus(JUMPING | CLIMB)) && _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::JUMPING);
		auto g = (Gravity*)_listComponent["Gravity"];
		g->setStatus(eGravityStatus::SHALLOWED);
		_animations[eStatus::CLIMB]->NextFrame();
	}
	//SWING
	if (isInStatus(eStatus(THROW | SWING)) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::THROW);
	}
	else if (isInStatus(eStatus(ATTACK | SWING)) && _animations[_currentAnimateIndex]->getIndex() >= 6)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::ATTACK);
	}
	//else if (isInStatus(eStatus(JUMPING | SWING)) && _animations[_currentAnimateIndex]->getIndex() >= 6)
	//{
	//	_animations[_currentAnimateIndex]->setIndex(0);
	//	removeStatus(eStatus::JUMPING);
	//}



	//JUMP
	else if (isInStatus(eStatus(THROW | JUMPING)) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::THROW);
		addStatus(eStatus::JUMPING);
	}
	else if (isInStatus(eStatus(THROW | JUMPING_LEFT)) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::THROW);
		addStatus(eStatus::JUMPING_LEFT);
	}
	else if (isInStatus(eStatus(THROW | JUMPING_RIGHT)) && _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::THROW);
		addStatus(eStatus::JUMPING_RIGHT);
	}
	else if (isInStatus(eStatus(ATTACK | JUMPING)) && !isInStatus(CLIMB_JUMP) && _animations[_currentAnimateIndex]->getIndex() >= 5)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::ATTACK);
		addStatus(eStatus::JUMPING);
	}
	else if (isInStatus(eStatus(ATTACK | JUMPING_RIGHT)) && _animations[_currentAnimateIndex]->getIndex() >= 5)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::ATTACK);
		addStatus(eStatus::JUMPING_RIGHT);
	}
	else if (isInStatus(eStatus(ATTACK | JUMPING_LEFT)) && _animations[_currentAnimateIndex]->getIndex() >= 5)
	{
		_animations[_currentAnimateIndex]->setIndex(6);
		removeStatus(eStatus::ATTACK);
		addStatus(eStatus::JUMPING_LEFT);
	}




	//XỬ LÍ NGOẠI LỆ
	//Thêm hiệu ứng ATTACK thì phải thêm ngoại lệ vào đây
	else if (isInStatus(eStatus::ATTACK) 
		&& !isExist(temp) 
		&& _animations[_currentAnimateIndex]->getIndex() >= 4)
	{
		_animations[_currentAnimateIndex]->setIndex(0);
		removeStatus(eStatus::ATTACK);
	}
#pragma endregion
}

void Aladdin::updateCurrentAnimateIndex()
{

	eStatus temp = (eStatus)(LOOKING_UP	 | SITTING_DOWN | MOVING_LEFT
						| MOVING_RIGHT	 | JUMPING_LEFT | JUMPING_RIGHT
						| JUMPING		 | CLIMB		| SWING
						| ATTACK		 | DROP			| DYING| THROW);
	if (isInStatus(NORMAL1) && isExist(temp))
	{
		removeStatus(eStatus::NORMAL1);
		_currentAnimateIndex = (eStatus)(getStatus() & ~eStatus::NORMAL1);
	}
	else _currentAnimateIndex = getStatus();
}

void Aladdin::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);
}

RECT Aladdin::getBounding()
{
	return _boundAla;
}

void Aladdin::setBounding(RECT r)
{
	float distancex = abs(r.right - r.left)/4.0f;
	float distancey = abs(r.top - r.bottom)/10.0f;
	RECT temp;
	temp.left = r.left + distancex;
	temp.right = r.right - distancex;
	temp.top = r.top - distancey;
	temp.bottom = r.bottom + distancey;
	_boundAla = temp;
}

void Aladdin::Stop()
{
	this->_animations[_currentAnimateIndex]->Stop();
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::SHALLOWED);
}

void Aladdin::Draw(LPD3DXSPRITE spriteHandle, ViewPort* viewport)
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
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(0, 0));
}

void Aladdin::moveLeft()
{
	_sprite->setScaleX(-SCALEALADDIN.x);
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(-ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::moveRight()
{
	_sprite->setScaleX(SCALEALADDIN.x);

	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::jump(eStatus status)
{
	if (isInStatus(status))
		return;

	addStatus(status);

	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_JUMP_VEL));

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Aladdin::sitDown()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(0, move->getVelocity().y));
}

void Aladdin::swingSword()
{
	if (isInStatus(eStatus::JUMPING))
		return;

	addStatus(eStatus::JUMPING);
}

void Aladdin::climb()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::SHALLOWED);
}

void Aladdin::climbUp(float dt)
{
	//_animations[_currentAnimateIndex]->Update(dt);
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_CLIMB_SPEED));
}

void Aladdin::climbDown(float dt)
{
	//_animations[_currentAnimateIndex]->UpdatePreFrame(dt);
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, -ALADDIN_CLIMB_SPEED));
}

void Aladdin::climbJump()
{

	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_CLIMB_JUMP_VEL));

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Aladdin::climbLeft()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(-ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::climbRight()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::swing()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::SHALLOWED);
}

void Aladdin::swingLeft(float dt)
{
	_sprite->setScaleX(-SCALEALADDIN.x);
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(-ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::swingRight(float dt)
{
	_sprite->setScaleX(SCALEALADDIN.x);
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(ALADDIN_MOVE_SPEED, move->getVelocity().y));
}

void Aladdin::swingJump()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_JUMP_VEL));

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

Vector2 Aladdin::getVelocity()
{
	auto move = (Movement*)_listComponent["Movement"];
	return move->getVelocity();
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
	setStatus(eStatus(getStatus() | status));
}

void Aladdin::removeStatus(eStatus status)
{
	setStatus(eStatus(getStatus() & ~status));
}

bool Aladdin::isInStatus(eStatus status)
{
	return (_status & status) == status;
}

bool Aladdin::isExist(eStatus status)
{
	if (int(_status & status) != 0)
		return true;
	return false;
}
