#include "PlayScene.h"
#include<iostream>
extern bool Enter[3];
extern bool TurnOn[4];
extern vector<BaseObject*> _listObject;
using namespace std;
ViewPort* PlayScene::_viewport = ViewPort::getInstance();
PlayScene::PlayScene()
{
	
}

PlayScene::~PlayScene()
{
	delete _viewport;
	_viewport = nullptr;
}

void PlayScene::setViewPort(ViewPort * viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

bool PlayScene::InIt()
{
	//mMap = new ReadMapEditor("Resources/Images/mapobject.tmx", _root);

	//_activeObject = mMap->GetList(rect);
	//Chú ý: Top Left của land ở bên dưới chứ không ở trên
	//  **********(B,R)
	//	**********
	//  **********
	//  **********
	//	**********
	//  **********
	// (T,L) (x,y)
	TurnOn[0] = true;
	//Tường
	_listObject.push_back(new Land(1432, 0, 51, 110, eDirection::INSIDE, eLandType::WALL));

	//Dây và cục chặn
	_listObject.push_back(new Land(2084, 105, 10, 200, eDirection::INSIDE, eLandType::CLIMBABLE0));
	_listObject.push_back(new Land(2084, 333, 20, 20, eDirection::BOTTOM, eLandType::STOP));
	_listObject.push_back(new Land(1541, 688-333, 10, 157, eDirection::INSIDE, eLandType::CLIMBABLE0));
	_listObject.push_back(new Land(1541, 688-149, 20, 20, eDirection::BOTTOM, eLandType::STOP));

	//Thanh xà ngang
	_listObject.push_back(new Land(130, 850, 800, 30, eDirection::BOTTOM, eLandType::BAR));
	//Nền
	_listObject.push_back(new Land(1454, 12, 4771, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(5, 50, 1454, 10, eDirection::TOP, eLandType::SOLID));
	//Miến gỗ đứng rớt
	_listObject.push_back(new FallingPlatform(1641, 239, eDirection::TOP));

	//Miến gỗ đứng ko rớt
	_listObject.push_back(new Land(1757, 239, 284, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1477, 688-451, 102, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1477, 688-402, 40, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1585, 688 - 292, 685, 10, eDirection::TOP, eLandType::SOLID));
	//Bật thang 1
	_listObject.push_back(new Land(1146, 0, 43, 71, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1189, 0, 43, 79, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1229, 0, 43, 87, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1266, 0, 43, 95, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1307, 0, 43, 103, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1347, 0, 43, 111, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1387, 0, 43, 119, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1430, 110, 43, 10, eDirection::TOP, eLandType::STAIR));
	//Bật thang 2
	Enter[0] = false;  //Check 1
	CheckOn[0].push_back(new Land(2660, 688-67-591, 5, 67, eDirection::TOP, eLandType::CHECKSTAIR1));
	CheckOn[1].push_back(new Land(2645, 688 - 67 - 593, 5, 67, eDirection::TOP, eLandType::CHECKSTAIR2));
	Stair[0].push_back(new Land(2563, 688 - 9-650, 27, 9, eDirection::TOP, eLandType::STAIR));
	Stair[0].push_back(new Land(2531, 688 - 9-642, 30, 9, eDirection::TOP, eLandType::STAIR));
	Stair[0].push_back(new Land(2499, 688 - 11-635, 30, 11, eDirection::TOP, eLandType::STAIR));
	Stair[0].push_back(new Land(2466, 688 - 12-627, 30, 12, eDirection::TOP, eLandType::STAIR));
	Stair[0].push_back(new Land(2435, 688 - 9-620, 35, 9, eDirection::TOP, eLandType::STAIR));
	Stair[0].push_back(new Land(2388, 688 - 13-610, 43, 13, eDirection::TOP, eLandType::STAIR));
	Stair[0].push_back(new Land(2355, 688 - 14-603, 30, 14, eDirection::TOP, eLandType::STAIR));
	Stair[0].push_back(new Land(2322, 688 - 18-594, 32, 18, eDirection::TOP, eLandType::STAIR));
	Stair[0].push_back(new Land(2290, 688 - 13-587, 34, 13, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(2243, 688 - 14-579, 45, 14, eDirection::TOP, eLandType::SOLID));
	//Bậc thang 3
	Enter[1] = false;  //Check 2
	CheckOn[2].push_back(new Land(2245, 688 - 86 - 492, 5, 86, eDirection::TOP, eLandType::CHECKSTAIR3));
	CheckOn[3].push_back(new Land(2269, 688 - 83 - 493, 5, 83, eDirection::TOP, eLandType::CHECKSTAIR4));
	Stair[1].push_back(new Land(2289, 688 - 10 - 578, 36, 10, eDirection::TOP, eLandType::STAIR));
	Stair[1].push_back(new Land(2328, 688 -565-10, 28, 10, eDirection::TOP, eLandType::STAIR));
	Stair[1].push_back(new Land(2358, 688 -560-10, 30, 10, eDirection::TOP, eLandType::STAIR));
	Stair[1].push_back(new Land(2392, 688 -555-10, 30, 10, eDirection::TOP, eLandType::STAIR));
	Stair[1].push_back(new Land(2426, 688 -539-15, 29, 10, eDirection::TOP, eLandType::STAIR));
	Stair[1].push_back(new Land(2459, 688 -531-16, 47, 10, eDirection::TOP, eLandType::STAIR));
	Stair[1].push_back(new Land(2511, 688 -530-10, 45, 10, eDirection::TOP, eLandType::STAIR));
	Stair[1].push_back(new Land(2559, 688 -520-10, 188, 10, eDirection::TOP, eLandType::STAIR));

	//Bậc thang 4
	_listObject.push_back(new Land(4346, 688-13-650, 48, 13, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(4397, 688-643-16, 38, 16, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(4437, 688-635-16, 38, 16, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(4476, 688 -626-11, 299, 11, eDirection::TOP, eLandType::STAIR));
	////Bậc thang 5
	//_listObject.push_back(new Land(1146, 0, 43, 71, eDirection::TOP, eLandType::STAIR));
	//_listObject.push_back(new Land(1189, 0, 43, 79, eDirection::TOP, eLandType::STAIR));
	//_listObject.push_back(new Land(1229, 0, 43, 87, eDirection::TOP, eLandType::STAIR));
	//_listObject.push_back(new Land(1266, 0, 43, 95, eDirection::TOP, eLandType::STAIR));
	//_listObject.push_back(new Land(1307, 0, 43, 103, eDirection::TOP, eLandType::STAIR));
	//_listObject.push_back(new Land(1347, 0, 43, 111, eDirection::TOP, eLandType::STAIR));
	//_listObject.push_back(new Land(1387, 0, 43, 119, eDirection::TOP, eLandType::STAIR));
	//_listObject.push_back(new Land(1430, 110, 43, 10, eDirection::TOP, eLandType::STAIR));
	//platform



	//Apple
	_listObject.push_back(new EatApple(600, 100));
	//Camel - Lac da
	auto camel = new Camel(1000, 50);
	_listObject.push_back(camel);

	//Fire
	_listObject.push_back(new Fire(BEHIT, 458, 688 - 626, TOP));
	_listObject.push_back(new Fire(BEHIT, 504, 688 - 626, TOP));
	_listObject.push_back(new Fire(BEHIT, 551, 688 - 626, TOP));


	//Background
	_background = new BackGround();
	_background->InIt();

	_backgroundfront = new BackGroundFront();
	_backgroundfront->InIt();

	//Complete
	/*auto guardLu = new GuardLu(eStatus::FREE, 200, 100, eDirection::LEFT);
	guardLu->InIt();
	_listObject.push_back(guardLu);*/

	////COMPLETE throwJar but not Jar
	//auto guardThrowJar = new ThrowJar(eStatus::FREE, 300, 300);
	//guardThrowJar->InIt();
	//_listObject.push_back(guardThrowJar);

	auto knifeThrower = new KnifeThrower(eStatus::MOVING_LEFT, 500, 100, eDirection::LEFT);
	knifeThrower->InIt();
	_listObject.push_back(knifeThrower);

	////Complete
	//auto guardThin = new GuardThin(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	//guardThin->InIt();
	//_listObject.push_back(guardThin);

	//auto guardfat = new GuardFat(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	//guardfat->InIt();
	//_listObject.push_back(guardfat);

	//auto guardShort = new GuardShort(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT, 2700, 3200);
	//guardShort->InIt();
	//_listObject.push_back(guardShort);

    _aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(10,250);
	_listObject.push_back(_aladdin);



	for each (auto object in _listObject)
	{
		object->getSprite()->UpdatePosition();
	}
	return true;
}

void PlayScene::UpdateInput(float dt)
{
	_aladdin->UpdateInput(dt);
}

void PlayScene::Update(float dt)
{

	/*char str[100];
	sprintf(str, "delta time: %f", dt);
	_text->setText(str);*/
	
	
	this->UpdateViewport(_aladdin);

	Vector2 viewport_position = _viewport->getPositionWorld();
	RECT viewport_in_transform = _viewport->getBounding();
	// Hàm getlistobject của quadtree yêu cầu truyền vào một hình chữ nhật theo hệ top left, nên cần tính lại khung màn hình
	RECT screen;

	screen.left = viewport_in_transform.left / SCALEFACTOR.x;
	screen.right = viewport_in_transform.right/ SCALEFACTOR.x;
	screen.bottom = viewport_position.y / SCALEFACTOR.y;
	screen.top = screen.bottom - 480/ SCALEFACTOR.y;



	for each (auto object in _listObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY)|| object->getId()==LAND)
			continue;
		object->Update(dt);
	}

	//Cải tiến. Chia ra 2 list một cho enermy 1 cho land

	/*Check collision aladdin with land
	@i Object*/
	for (auto i : _listObject)
	{
		// i la Enermy va aladdin
		if (i == nullptr)
			continue;
		eID temp = i->getId();

		/*Fallingplatform cần kiểm tra riêng 
		aladdin với nó và ngược lại ở for dưới*/
		if (temp == eID::FALLINGPLATFORM) 
			_aladdin->checkCollision(i, dt);
		if (temp == eID::CAMEL)
			_aladdin->checkCollision(i, dt);
		if (i->getId() != eID::LAND || _aladdin->getId() == temp)
			continue;
		_aladdin->checkCollision(i, dt);
	}


	/*Check collision (*1)enermy with (*2)aladdin (chú ý thứ tự )
	@i Enermyobject*/
	for (auto obj : _listObject)
	{
		// obj la Enermy va aladdin
		if (obj == nullptr)
			continue;

		eID temp = obj->getId();
		if (temp == LAND || temp == ALADDIN || obj->getStatus()==DESTROY)
			continue;	
		obj->checkCollision(_aladdin, dt);
	}

	
	if (Enter[0])
	{
		for (auto i : Stair[0])
		{
			// i la Enermy va aladdin
			if (i == nullptr)
				continue;
			_aladdin->checkCollision(i, dt);
		}
	}
	if (Enter[1])
	{
		for (auto i : Stair[1])
		{
			// i la Enermy va aladdin
			if (i == nullptr)
				continue;
			_aladdin->checkCollision(i, dt);
		}
	}

	#pragma region TurnOn check stair
	if (TurnOn[0]) {
		_aladdin->checkCollision(CheckOn[0].back(), dt);
	}
	if (TurnOn[1]) {
		_aladdin->checkCollision(CheckOn[1].back(), dt);
	}
	if (TurnOn[2]) {
		_aladdin->checkCollision(CheckOn[2].back(), dt);
	}
	if (TurnOn[3]) {
		_aladdin->checkCollision(CheckOn[3].back(), dt);
	}

#pragma endregion
}

void PlayScene::Draw(LPD3DXSPRITE spriteHandle)
{
    _background->Draw(spriteHandle,_viewport);
	for each (auto object in _listObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY))
			continue;
		object->Draw(spriteHandle, _viewport);
		//object->ShowBB();
	}
	_backgroundfront->Draw(spriteHandle, _viewport);

	for each(auto object in Stair[0])
	{
		object->Draw(spriteHandle, _viewport);
		//object->ShowBB();
	}
	for each(auto object in Stair[1])
	{
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}

#pragma region Draw check stair
	if (TurnOn[0]) {
		CheckOn[0].back()->Draw(spriteHandle, _viewport);
		CheckOn[0].back()->ShowBB();
	}
	if (TurnOn[1]) {
		CheckOn[1].back()->Draw(spriteHandle, _viewport);
		CheckOn[1].back()->ShowBB();
	}
	if (TurnOn[2]) {
		CheckOn[2].back()->Draw(spriteHandle, _viewport);
		CheckOn[2].back()->ShowBB();
	}
	if (TurnOn[3]) {
		CheckOn[3].back()->Draw(spriteHandle, _viewport);
		CheckOn[3].back()->ShowBB();
	}

#pragma endregion
}

void PlayScene::Release()
{
	for each (auto object in _listObject)
	{
		object->Release();
	}
}

void PlayScene::UpdateViewport(BaseObject * aladdin)
{
	// Vị trí hiện tại của viewport. 
	Vector2 current_position = _viewport->getPositionWorld();
	//Kích thước của map
	Vector2 worldsize = Vector2(SIZEMAP.x, SIZEMAP.y);
	// Bám theo object.
	float y = aladdin->getPositionY() - WINDOWS_HEIGHT;
	Vector2 new_position =
		/*Khi max ở đây sẽ cho mình biết khi nào camera sẽ đi theo aladdin 
		và khi nào không*/
		Vector2(max(aladdin->getPositionX() - 320, 0),
			max(aladdin->getPositionY() + 280, WINDOWS_HEIGHT));		
	// 320 va 280 khoảng cách hardcode dựa vào test thực tế.
																		
	if (new_position.x + WINDOWS_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOWS_WIDTH;
	}
	_viewport->setPositionWorld(new_position);
}