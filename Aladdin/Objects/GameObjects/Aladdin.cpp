#include "ALADDIN.h"
bool Enter[3];
bool TurnOn[4];
vector<BaseObject*> _listObject;
vector<BaseObject*> listApple;

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

	_animations[eStatus::STOPWALK] = new Animation(_sprite, 0.1f);
	_animations[eStatus::STOPWALK]->addFrameRect(eID::ALADDIN, "standing_0", "standing_0", NULL);

	_animations[eStatus::NORMAL1] = new Animation(_sprite, 0.3f);
	_animations[eStatus::NORMAL1]->addFrameRect(eID::ALADDIN, "standing_", 7); //7 là số ảnh

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.095f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "jump_up_", 10);

	_animations[eStatus::AEROBATIC] = new Animation(_sprite, 0.1f);
	_animations[eStatus::AEROBATIC]->addFrameRect(eID::ALADDIN, "Aerobatic_0", 7);

	_animations[eStatus::DROP] = new Animation(_sprite, 0.095f);
	_animations[eStatus::DROP]->addFrameRect(eID::ALADDIN, "jump_up_5", "jump_up_6", "jump_up_7", "jump_up_8", "jump_up_9", NULL);

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

	_animations[eStatus::FREE] = new Animation(_sprite, 0.2f);
	_animations[eStatus::FREE]->addFrameRect(eID::ALADDIN, "free_", 32);

	_animations[eStatus::CLIMB] = new Animation(_sprite, 0.15f);
	_animations[eStatus::CLIMB]->addFrameRect(eID::ALADDIN, "climb_", 10);

	_animations[eStatus::THROW] = new Animation(_sprite, 0.06f);
	_animations[eStatus::THROW]->addFrameRect(eID::ALADDIN, "throw_0", 5);

	_animations[eStatus::ATTACK | eStatus::SITTING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::ATTACK | eStatus::SITTING_DOWN]->addFrameRect(eID::ALADDIN, "swing_sword_", 5);

	_animations[eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.08f);
	_animations[eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "walk_", 11);

	_animations[eStatus::MOVING_LEFT] = new Animation(_sprite, 0.08f);
	_animations[eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "walk_", 11);

	_animations[eStatus::THROW | eStatus::MOVING_LEFT] = new Animation(_sprite, 0.06f);
	_animations[eStatus::THROW | eStatus::MOVING_LEFT]->addFrameRect(eID::ALADDIN, "run_throw_0", 6);

	_animations[eStatus::THROW | eStatus::MOVING_RIGHT] = new Animation(_sprite, 0.06f);
	_animations[eStatus::THROW | eStatus::MOVING_RIGHT]->addFrameRect(eID::ALADDIN, "run_throw_0", 6);

	//cầm kiếm chém
	_animations[eStatus::ATTACK] = new Animation(_sprite, 0.07f);
	_animations[eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "attack_0", 5);
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

	_animations[eStatus::BEHIT] = new Animation(_sprite, 0.05f);
	_animations[eStatus::BEHIT]->addFrameRect(eID::ALADDIN, "burn_", 6); //6

	_animations[eStatus::SWING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING]->addFrameRect(eID::ALADDIN, "swing_0", 10);

	_animations[eStatus::SWING | eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::SWING | eStatus::JUMPING]->addFrameRect(eID::ALADDIN, "jump_up_", 10);

	_animations[eStatus::SWING | eStatus::THROW] = new Animation(_sprite, 0.06f);
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
		"climb_jump_03", "climb_jump_03", "climb_jump_03", NULL);

	_animations[eStatus::CLIMB | eStatus::THROW] = new Animation(_sprite, 0.06f);
	_animations[eStatus::CLIMB | eStatus::THROW]->addFrameRect(eID::ALADDIN, "climb_throw_0", 5);

	_animations[eStatus::CLIMB | eStatus::ATTACK] = new Animation(_sprite, 0.14f);
	_animations[eStatus::CLIMB | eStatus::ATTACK]->addFrameRect(eID::ALADDIN, "climb_attack_0", 7);

	_animations[REVIVAL] = new Animation(_sprite, 0.12f);
	_animations[REVIVAL]->addFrameRect(eID::ALADDIN, "restart_point_", 14);

	_sprite->drawBounding(false);

	//Set lại bouding cho riêng aladdin để xét va chạm
	setBounding(_sprite->getBounding());

	_canUp = true;
	setStatus(eStatus::NORMAL);


	//create stopwatch to wait time state normal or free of aladdin
	_normalAnimateStopWatch = new StopWatch();
	_firstAnimateStopWatch  = new StopWatch();
	_beAttackSW				= new StopWatch();
	_EnableFlashes			= new StopWatch();

	this->setScale(SCALEALADDIN);
	_restartPoint = nullptr;
}

void Aladdin::Update(float deltatime)
{
	updateStatus(deltatime);

	#pragma region UpdateListApple
	for (int i = 0; i < listApple.size(); i++)
	{
		if (listApple[i]->isInStatus(DESTROY))
		{
			listApple[i]->Release();
			delete listApple[i];
			listApple.erase(listApple.begin() + i);
		}
		else
			listApple[i]->Update(deltatime);
	}
	#pragma endregion

	//Loc dieu kien
	updateCurrentAnimateIndex();

	//Lọc các hiệu ứng khi nhấn một lần và thực hiện toàn bộ hiệu ứng
	//Nhấn Z sẽ render toàn bộ ảnh ném táo. Nhớ xóa removeStatus ở keyRelease
	updateStatusOneAction(deltatime);

	if (isInStatus(eStatus::CLIMB) || isInStatus(eStatus::SWING))
	{
		if (isInStatus(eStatus::ATTACK) || isInStatus(eStatus::THROW) || isInStatus(eStatus::JUMPING))
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

	
	//Kiểm tra thời gian nhấp nháy khi bị đánh
	if (_EnableFlashes->isTimeLoop(700))
	{
		_animations[_currentAnimateIndex]->EnableFlashes(true);
	}
	else
	{
		_animations[_currentAnimateIndex]->EnableFlashes(false);
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
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav",0);
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			jump(eStatus::JUMPING);
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
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			removeStatus(eStatus::NORMAL1);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
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
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			removeStatus(eStatus::FREE);
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			removeStatus(eStatus::FREE);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			removeStatus(eStatus::FREE);
			jump(eStatus::JUMPING);
		}
		break;
	}
	case(eStatus::STOPWALK):
	{
		if (_sideColliWall == RIGHT)
		{
			if (_input->isKeyDown(DIK_LEFT))
			{
				/*1. Nhấn LeftArrow
				2. Hướng aladdin là right
				=> scale.x > 0
				3. Hủy StopWalk và chuyển sang moving left*/
				if (getScale().x > 0)
				{
					removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
					_sideColliWall = NONE;
					addStatus(eStatus::MOVING_LEFT);
				}
			}
			else if (_input->isKeyDown(DIK_RIGHT))
			{
				/*1. Nhấn RightArrow
				2. Hướng aladdin là left
				=> scale.x < 0
				3. Hủy StopWalk và chuyển sang moving right*/
				if (getScale().x < 0)
				{
					removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
					addStatus(eStatus::MOVING_RIGHT);
				}
			}
			else if (_input->isKeyDown(DIK_DOWN))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::SITTING_DOWN);
			}
			else if (_input->isKeyDown(DIK_UP))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::LOOKING_UP);
			}
			else if (_input->isKeyPressed(DIK_X)) //chém
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::ATTACK);  //chém

			}
			else if (_input->isKeyDown(DIK_Z)) //ném
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::THROW);
				Vector2 position = getPosition();

				int apple = InforAladdin::getInstance()->getApple();
				if (apple > 0)
				{
					listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
					InforAladdin::getInstance()->plusApple(-1);
				}
			}
			else if (_input->isKeyPressed(DIK_C))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				jump(eStatus::JUMPING);
			}
		}
		else if (_sideColliWall == LEFT)
		{
			if (_input->isKeyDown(DIK_LEFT))
			{
				/*1. Nhấn LeftArrow
				2. Hướng aladdin là right
				=> scale.x > 0
				3. Hủy StopWalk và chuyển sang moving left*/
				if (getScale().x > 0)
				{
					removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
					_sideColliWall = NONE;
					addStatus(eStatus::MOVING_LEFT);
				}
			}
			else if (_input->isKeyDown(DIK_RIGHT))
			{
				/*1. Nhấn RightArrow
				2. Hướng aladdin là RIGHT
				=> scale.x > 0
				3. Hủy StopWalk và chuyển sang moving right*/
				if (getScale().x < 0)
				{
					removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
					addStatus(eStatus::MOVING_RIGHT);
				}
			}
			else if (_input->isKeyDown(DIK_DOWN))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::SITTING_DOWN);
			}
			else if (_input->isKeyDown(DIK_UP))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::LOOKING_UP);
			}
			else if (_input->isKeyPressed(DIK_X)) //chém
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::ATTACK);  //chém

			}
			else if (_input->isKeyDown(DIK_Z)) //ném
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::THROW);
				Vector2 position = getPosition();

				int apple = InforAladdin::getInstance()->getApple();
				if (apple > 0)
				{
					listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
					InforAladdin::getInstance()->plusApple(-1);
				}
			}
			else if (_input->isKeyPressed(DIK_C))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				jump(eStatus::JUMPING);
			}
		}
		else
		{
			if (_input->isKeyDown(DIK_LEFT))
			{
				/*1. Nhấn LeftArrow
				2. Hướng aladdin là right
				=> scale.x > 0
				3. Hủy StopWalk và chuyển sang moving left*/
				if (getScale().x > 0)
				{
					removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
					addStatus(eStatus::MOVING_LEFT);
				}
			}
			else if (_input->isKeyDown(DIK_RIGHT))
			{
				/*1. Nhấn RightArrow
				2. Hướng aladdin là left
				=> scale.x < 0
				3. Hủy StopWalk và chuyển sang moving right*/
				if (getScale().x < 0)
				{
					removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
					addStatus(eStatus::MOVING_RIGHT);
				}
			}
			else if (_input->isKeyDown(DIK_DOWN))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::SITTING_DOWN);
			}
			else if (_input->isKeyDown(DIK_UP))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::LOOKING_UP);
			}
			else if (_input->isKeyPressed(DIK_X)) //chém
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::ATTACK);  //chém

			}
			else if (_input->isKeyDown(DIK_Z)) //ném
			{
				//âm thanh
				SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				addStatus(eStatus::THROW);
				Vector2 position = getPosition();

				int apple = InforAladdin::getInstance()->getApple();
				if (apple > 0)
				{
					listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
					InforAladdin::getInstance()->plusApple(-1);
				}
			}
			else if (_input->isKeyPressed(DIK_C))
			{
				removeStatus(eStatus::STOPWALK); _sideColliWall = NONE;
				jump(eStatus::JUMPING);
			}
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
			addStatus(eStatus::ATTACK);
		}
		if (_input->isKeyPressed(DIK_Z))
		{
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
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
		if (_input->isKeyPressed(DIK_Z))
		{
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
		}
		break;
	}
	case (eStatus::JUMPING_RIGHT):
	{
		if (_input->isKeyDown(DIK_LEFT))
		{
			if (_input->isKeyDown(DIK_RIGHT))
			{
				break;
			}
			moveLeftJump();
			removeStatus(eStatus::JUMPING_RIGHT);
			addStatus(eStatus::JUMPING_LEFT);
		}
		else if (_input->isKeyPressed(DIK_Z))
		{
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::ATTACK);
			/*if (_input->isKeyDown(DIK_LEFT))
			{
				moveLeft();
				removeStatus(eStatus::ATTACK);
				removeStatus(eStatus::THROW);
				addStatus(eStatus::JUMPING_LEFT);
			}*/
		}
		break;
	}
	case (eStatus::JUMPING_LEFT):
	{
		if (_input->isKeyDown(DIK_RIGHT))
		{
			if (_input->isKeyDown(DIK_LEFT))
			{
				break;
			}
			moveRightJump();
			removeStatus(eStatus::JUMPING_LEFT);
			addStatus(eStatus::JUMPING_RIGHT);
		}
		else if (_input->isKeyPressed(DIK_Z))
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
			/*if (_input->isKeyDown(DIK_RIGHT))
			{
				removeStatus(eStatus::THROW);
				moveRight();
				addStatus(eStatus::JUMPING_RIGHT);

			}*/
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
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
				moveLeftJump();
			if (_input->isKeyDown(DIK_RIGHT))
				moveRightJump();

		else if (_input->isKeyPressed(DIK_Z))
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}

		}
		else if (_input->isKeyPressed(DIK_X))
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::ATTACK);
		}
		break;
	}
	case(eStatus::DROP):
	{
		if (_input->isKeyDown(DIK_LEFT))
			moveLeftJump();
		else if (_input->isKeyDown(DIK_RIGHT))
			moveRightJump();
		else if (_input->isKeyPressed(DIK_Z))
		{
			removeStatus(DROP);
			setStatus((eStatus)(JUMPING|THROW));
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			removeStatus(DROP);
			setStatus((eStatus)(JUMPING | ATTACK));
		}
		break;
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
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyPressed(DIK_Z)) //ném
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
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
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::ATTACK);  //chém
		}
		else if (_input->isKeyDown(DIK_Z)) //ném
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			removeStatus(eStatus::LOOKING_UP);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
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
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			removeStatus(eStatus::CLIMB_JUMP);
			addStatus(eStatus::JUMPING);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
		}
		else if (_input->isKeyPressed(DIK_X))
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
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
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::ATTACK);
		}
		else if (_input->isKeyPressed(DIK_Z))
		{
			//âm thanh
			SoundManager::getInstance()->PlaySound("Resources/Audio/HighSword.wav", 0);
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
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
		else if (_input->isKeyPressed(DIK_Z))
		{
			addStatus(eStatus::THROW);
			Vector2 position = getPosition();
			

			int apple = InforAladdin::getInstance()->getApple();
			if (apple > 0)
			{
				listApple.push_back(new AppleThrow(position.x, position.y, (getScale().x < 0)));
				InforAladdin::getInstance()->plusApple(-1);
			}
		}
		else if (_input->isKeyPressed(DIK_C))
		{
			//removeStatus(eStatus::SWING);
			addStatus(eStatus::JUMPING);
			swingJump();
		}
		break;
	}
	case(eStatus::BEHIT):
	{
		//Tự hủy khi đế một bức ảnh thứ n
		_EnableFlashes->restart();
		if (_animations[_currentAnimateIndex]->getIndex() >= 4)
		{
			_animations[_currentAnimateIndex]->setIndex(0);
			setStatus(NORMAL);	
		}
		break;
	}
	case(eStatus::AEROBATIC):
	{
		if (_input->isKeyDown(DIK_LEFT))
		{
			moveLeft();
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			moveRight();
		}
	}
	case(eStatus::REVIVAL):
	{
		if (_animations[REVIVAL]->getIndex() >= 13)
		{
			_animations[_currentAnimateIndex]->setIndex(0);
			setPosition(_restartPoint->getPosition().x, _restartPoint->getPosition().y + 15);
			_restartPoint->setStatus(NORMAL);

			__hook(&CollisionBody::onCollisionBegin, (CollisionBody*)_listComponent["CollisionBody"], &Aladdin::onCollisionBegin);
			__hook(&CollisionBody::onCollisionEnd, (CollisionBody*)_listComponent["CollisionBody"], &Aladdin::onCollisionEnd);

			auto g = (Gravity*)_listComponent["Gravity"];
			g->setStatus(eGravityStatus::FALLING__DOWN);
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
				setStatus(eStatus::CLIMB_JUMP);
				climbLeft();
				_animations[_currentAnimateIndex]->Begin();
			}
			else if (_input->isKeyDown(DIK_RIGHT))
			{
				Vector2 temp = getScale();
				if (temp.x < 0)
					setScaleX(-temp.x);
				setStatus(eStatus::CLIMB_JUMP);
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
	
	
	
	if (_input->isKeyPressed(DIK_Q))
		InforAladdin::getInstance()->plusHealth(100);
	if (_input->isKeyPressed(DIK_9))
		clearStatus();
}

void Aladdin::onKeyReleased(KeyEventArg * key_event)
{
	switch (key_event->_key)
	{
	case DIK_RIGHT:
	{
		removeStatus(eStatus::MOVING_RIGHT);
		if (!isInStatus(JUMPING_LEFT) && !isInStatus(CLIMB_JUMP))
			standing();
		break;
	}
	case DIK_LEFT:
	{
		removeStatus(eStatus::MOVING_LEFT);
		if (!isInStatus(JUMPING_RIGHT) && !isInStatus(CLIMB_JUMP))
			this->standing();
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
		//standing();
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
		
		if (type == VICTORY)
		{
			Enter[2] = true;
		}


		switch (collision_event->_sideCollision)
		{
		case(eDirection::TOP):
		{
			switch (type)
			{
			case(eLandType::WALL):
			{
				if (type == eLandType::WALL)
				{
					auto move = (Movement*)_listComponent["Movement"];
					move->setVelocity(Vector2(0, move->getVelocity().y));
					if (isInStatus(SWING))
					{
						_stopLeft = true;
						break;
					}
					//set trạng thái chỉ khi đi ngược hướng va chạm mới set lại trạng thái khác
					this->setStatus(eStatus::STOPWALK);
					break;
				}
				break;
			}
			case (eLandType::SOLID):
			{
				//Chạm đất
				clearStatus();
				auto gravity = (Gravity*)_listComponent["Gravity"];
				gravity->setStatus(eGravityStatus::SHALLOWED);
				standing();
				break;
			}
			case (eLandType::STAIR):
			{
				//Chạm đất
				clearStatus();
				auto gravity = (Gravity*)_listComponent["Gravity"];
				gravity->setStatus(eGravityStatus::SHALLOWED);
				standing();
				break;
			}
			case (eLandType::BAR):
			{
				if (isInStatus(eStatus(JUMPING | SWING)))
					return;
				setStatus(SWING);
				float y = land->getPositionY();
				setPositionY(y - 150); //set cứng khi va chạm với Bar thì cho giảm y
				swing();
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
				setStatus(SWING);
				float y = land->getPositionY();
				setPositionY(y - 100); //set cứng khi va chạm với Bar thì cho giảm y
				swing();
				break;
			}
			case (eLandType::STOP):
			{
				_canUp = false;
				break;
			}
			case (eLandType::ROPE):
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
			case(eLandType::WALL):
			{
				auto move = (Movement*)_listComponent["Movement"];
				move->setVelocity(Vector2(0, move->getVelocity().y));
				if (isInStatus(SWING))
				{
					_stopLeft = true;
					break;
				}
				_sideColliWall = LEFT;
				//set trạng thái chỉ khi đi ngược hướng va chạm mới set lại trạng thái khác
				this->setStatus(eStatus::STOPWALK);
				break;
			}
			case (eLandType::ROPE):
			{
				clearStatus();
				_canUp = true;
				addStatus(eStatus::CLIMB);
				climb();
				float x = land->getPositionX();
				setPositionX(x);
				break;
			}
			case (eLandType::STAIR):
			{
				/*auto move = (Movement*)_listComponent["Movement"];
				move->setVelocity(Vector2(0, 170));*/
				setPositionY(this->getPositionY() + 10);
				break;
			}
			}
			break;
		}
		case(eDirection::RIGHT):
		{
			switch (type)
			{
			case(eLandType::WALL):
			{

				auto move = (Movement*)_listComponent["Movement"];
				move->setVelocity(Vector2(0, move->getVelocity().y));
				if (isInStatus(SWING))
				{
					_stopLeft = true;
					break;
				}
				_sideColliWall = RIGHT;
				//set trạng thái chỉ khi đi ngược hướng va chạm mới set lại trạng thái khác
				this->setStatus(eStatus::STOPWALK);
				break;
			}
			case (eLandType::ROPE):
			{
				clearStatus();
				_canUp = true;
				addStatus(eStatus::CLIMB);
				climb();
				float x = land->getPositionX();
				setPositionX(x);
				break;
			}
			case (eLandType::STAIR):
			{
				/*auto move = (Movement*)_listComponent["Movement"];
				move->setVelocity(Vector2(0, 170));*/
				setPositionY(this->getPositionY() + 10);
				break;
			}
			}
			break;
		}
		}
		break;
	}
	case eID::FALLINGPLATFORM:
	{
		switch (collision_event->_sideCollision)
		{
		case(eDirection::TOP):
		{
			auto temp = (FallingPlatform*)collision_event->_otherObject;
			temp->startCount();
			//Chạm đất
			clearStatus();
			auto gravity = (Gravity*)_listComponent["Gravity"];
			gravity->setStatus(eGravityStatus::SHALLOWED);
			standing();
			break;
		}
		break;
		}
	}
	}

	switch (collision_event->_otherObject->getId())
	{
	case eID::LAND:
	{
		auto land = (Land*)collision_event->_otherObject;
		eLandType type = land->getType();
		switch (collision_event->_sideCollision)
		{
		case(eDirection::LEFT):
		{
			switch (type)
			{
			case (eLandType::CHECKSTAIR1):
			{
				Enter[0] = true;
				Enter[1] = false;
				TurnOn[0] = false;
				TurnOn[1] = true;
				TurnOn[2] = true;
				TurnOn[3] = false;
				break;
			}
			case (eLandType::CHECKSTAIR2):
			{
				Enter[0] = false;
				Enter[1] = false;
				TurnOn[0] = true;
				TurnOn[1] = false;
				TurnOn[2] = false;
				TurnOn[3] = false;
				break;
			}
			}
			break;
		}
		case(eDirection::RIGHT):
		{
			switch (type)
			{
			case (eLandType::CHECKSTAIR3):
			{
				Enter[0] = false;//đi xuống không được
				Enter[1] = true; //đi lên được
				TurnOn[1] = true;
				TurnOn[2] = false;
				TurnOn[3] = true;
				break;
			}
			case (eLandType::CHECKSTAIR4):
			{
				Enter[0] = true;
				Enter[1] = false;
				TurnOn[2] = true;
				TurnOn[3] = false;
				auto gravity = (Gravity*)_listComponent["Gravity"];
				gravity->setStatus(eGravityStatus::FALLING__DOWN);
				break;
			}
			}
			break;
		}
		}
		break;
	}
	case eID::CAMEL:
	{
		switch (collision_event->_sideCollision)
		{
			case TOP:
			{
				collision_event->_otherObject->setStatus(eStatus::BEHIT);
				jumpDouble();
				return;
			}
		}
		break;
	}

	case eID::SPRING:
	{
		switch (collision_event->_sideCollision)
		{
			case TOP:
			{
				collision_event->_otherObject->setStatus(eStatus::BEHIT);
				SoundManager::getInstance()->PlaySound("Resources/Audio/CamelSpit.wav", 0);

				aerobatic();
				return;
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
		auto type = land->getType();
		eDirection side = collision_event->_sideCollision;
			switch (type)
			{
				case (eLandType::ROPE):
				{
					_status;
					if (isInStatus(eStatus::JUMPING) || isInStatus(eStatus::SWING))
					{
						removeStatus(CLIMB_JUMP);
						return;
					}
					setStatus(eStatus::CLIMB_JUMP);
					auto g = (Gravity*)_listComponent["Gravity"];
					g->setStatus(eGravityStatus::FALLING__DOWN); 
					break;
				}
				case (eLandType::SOLID):
				{
					switch (side)
					{
					case TOP:
					{
						eStatus temp = (eStatus)(JUMPING | JUMPING_LEFT | JUMPING_RIGHT);
						if (!isExist(temp))
							setStatus(DROP);
						auto g = (Gravity*)_listComponent["Gravity"];
						g->setStatus(eGravityStatus::FALLING__DOWN);
						break; 
					}
					case BOTTOM:
					{
						break;
					}
					case LEFT:
					{
						break; 
					}
					case RIGHT:
					{
						break;
					}
					default:
						break;
					}
					break;
				}
				case( eLandType::STOP):
				{
					_animations[_currentAnimateIndex]->Start();
					_canUp = true;
					break;
				}
				case (eLandType::STAIR):
				{
					auto g = (Gravity*)_listComponent["Gravity"];
					g->setStatus(eGravityStatus::FALLING__DOWN);
					break;
				}
				case(eLandType::BAR):
				{
					eStatus temp = (eStatus)(JUMPING | JUMPING_LEFT | JUMPING_RIGHT);
					_status;
					if (!isExist(temp))
						setStatus(DROP);
					auto g = (Gravity*)_listComponent["Gravity"];
					g->setStatus(eGravityStatus::FALLING__DOWN);
					break;
				}
			}
			break;
		}
		case eID::FALLINGPLATFORM:
		{
			auto g = (Gravity*)_listComponent["Gravity"];
			g->setStatus(eGravityStatus::FALLING__DOWN);
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


	for (int i = 0; i < listApple.size(); i++)
		listApple[i]->checkCollision(object, dt);

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
			if(!_stopLeft)
				swingLeft(dt);
		}
		else if (_input->isKeyDown(DIK_RIGHT))
		{
			swingRight(dt);
			_stopLeft = false;
		}
		else
		{
			standing();
		}
	}
	else if (isInStatus(eStatus::MOVING_LEFT))
	{
		moveLeft();
		if (isInStatus(eStatus::THROW) && isInStatus(ATTACK))
			removeStatus(THROW);
	}
	else if (isInStatus(eStatus::MOVING_RIGHT))
	{
		moveRight();

		if (isInStatus(eStatus::THROW) && isInStatus(ATTACK))
			removeStatus(THROW);
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
	//Thêm hiệu ứng ATTACK thì phải thêm ngoại lệ vào temp
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
						| ATTACK		 | DROP			| DYING| THROW |AEROBATIC);
	if (isInStatus(NORMAL1) && isExist(temp))
	{
		removeStatus(eStatus::NORMAL1);
		_currentAnimateIndex = (eStatus)(getStatus() & ~eStatus::NORMAL1);
	}
	else _currentAnimateIndex = getStatus();
}

RECT Aladdin::getBounding()
{
	return _boundAla;
}

void Aladdin::setBounding(RECT r)
{
	float distancex = abs(r.right - r.left) / 4.0f;
	float distancey = abs(r.top - r.bottom) / 10.0f;
	RECT temp;
	temp.left = r.left + distancex;
	temp.right = r.right - distancex;
	if (isExist((eStatus)(CLIMB | CLIMB_JUMP | JUMPING |SWING)))
	{
		distancey = 170;

		temp.top = r.bottom+ distancey;
		temp.bottom = r.bottom;
	}
	else
	{

		temp.top = r.top - distancey;
		temp.bottom = r.bottom + distancey;
	}

	_boundAla = temp;
}

int Aladdin::getIndex()
{
	//_currentAnimateIndex is in eStatus::ATTACK
	if (isInStatus(ATTACK))
		return _animations[_currentAnimateIndex]->getIndex();
	else return 0;
}

void Aladdin::Stop()
{
	this->_animations[_currentAnimateIndex]->Stop();
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(VECTOR2ZERO);

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::SHALLOWED);
}

void Aladdin::Stop(bool stopanimation)
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(0,this->getVelocity().y));
}

void Aladdin::SetRestartPoint(BaseObject *restartpoint)
{
	_restartPoint = restartpoint;
}

void Aladdin::Revival()
{
	if (_restartPoint == NULL)
	{
		setPosition(100,100);
	}
	else
	{
		_restartPoint->clearStatus();

		__unhook((CollisionBody*)_listComponent["CollisionBody"]);
		__unhook((CollisionBody*)_listComponent["CollisionBody"]);
		swing();
		setPosition(_restartPoint->getPosition());
		setStatus(eStatus::REVIVAL);
	}
}

void Aladdin::Draw(LPD3DXSPRITE spriteHandle, ViewPort* viewport)
{
	_animations[_currentAnimateIndex]->Draw(spriteHandle, viewport);
	for (int i = 0; i < listApple.size(); i++)
	{
		if (listApple[i]->isInStatus(DESTROY))
		{
			listApple[i]->Release();
			delete listApple[i];
			listApple.erase(listApple.begin() + i);
		}
		else
			listApple[i]->Draw(spriteHandle, viewport);
	}
}

void Aladdin::Release()
{
	_sprite->Release();
	_animations.clear();
	for (int i = 0; i < listApple.size(); i++)
	{
		listApple[i]->Release();
		delete listApple[i];
	}
	listApple.clear();

	auto _input = InputController::getInstance();
	if (_input != nullptr)
		__unhook(_input);
}

void Aladdin::standing()
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(0, 0));
}

void Aladdin::StartFlash()
{
	_EnableFlashes->restart();
}

bool Aladdin::isFlashing()
{
	return !_EnableFlashes->isFinish();
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

void Aladdin::jumpDouble()
{
	setStatus(JUMPING);

	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_JUMP_DOUBLE_VEL));

	auto g = (Gravity*)_listComponent["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Aladdin::aerobatic()
{
	setStatus(AEROBATIC);

	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x, ALADDIN_AEROBATIC_VEL));

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

void Aladdin::moveLeftJump()
{
	_sprite->setScaleX(-SCALEALADDIN.x);
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(-ALADDIN_MOVE_JUMP_SPEED, move->getVelocity().y));
}

void Aladdin::moveRightJump()
{
	_sprite->setScaleX(SCALEALADDIN.x);

	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(ALADDIN_MOVE_JUMP_SPEED, move->getVelocity().y));
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

void Aladdin::addVelocity(float value)
{
	auto move = (Movement*)_listComponent["Movement"];
	move->setVelocity(Vector2(move->getVelocity().x +value, move->getVelocity().y));
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

bool Aladdin::isExist(eStatus status)
{
	if (int(_status & status) != 0)
		return true;
	return false;
}
