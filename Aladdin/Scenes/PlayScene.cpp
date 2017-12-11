#include "PlayScene.h"
#include<iostream>
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
	//Chú ý: Top Left của land ở bên dưới chứ không ở trên
	//  **********(B,R)
	//	**********
	//  **********
	//  **********
	//	**********
	//  **********
	// (T,L)


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
	_listObject.push_back(new Land(1641, 239, 36, 10, eDirection::TOP, eLandType::SOLID));
	//Miến gỗ đứng ko rớt
	_listObject.push_back(new Land(1757, 239, 284, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1477, 688-451, 102, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1477, 688-402, 40, 10, eDirection::TOP, eLandType::SOLID));
	_listObject.push_back(new Land(1585, 688 - 292, 685, 10, eDirection::TOP, eLandType::SOLID));
	//Bật thang
	_listObject.push_back(new Land(1146, 0, 43, 71, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1189, 0, 43, 79, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1229, 0, 43, 87, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1266, 0, 43, 95, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1307, 0, 43, 103, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1347, 0, 43, 111, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1387, 0, 43, 119, eDirection::TOP, eLandType::STAIR));
	_listObject.push_back(new Land(1430, 110, 43, 10, eDirection::TOP, eLandType::STAIR));
	//platform

	//Fire
	/*_listObject.push_back(new Land(458, 688-626, 42, 55, eDirection::TOP, eLandType::FIRE));
	_listObject.push_back(new Land(504, 688 - 627, 38, 56, eDirection::TOP, eLandType::FIRE));
	_listObject.push_back(new Land(551, 688 - 625, 31, 55, eDirection::TOP, eLandType::FIRE));
*/

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

	//COMPLETE throwJar but not Jar
	//auto guardThrowJar = new ThrowJar(eStatus::FREE, 300, 300);
	//guardThrowJar->InIt();
	//_listObject.push_back(guardThrowJar);

	/*auto knifeThrower = new KnifeThrower(eStatus::MOVING_RIGHT, 200, 100, eDirection::LEFT);
	knifeThrower->InIt();
	_listObject.push_back(knifeThrower);*/

	//Complete
	/*auto guardThin = new GuardThin(eStatus::MOVING_LEFT, 200, 100, eDirection::LEFT);
	guardThin->InIt();
	_listObject.push_back(guardThin);*/

	auto guardShort = new GuardShort(eStatus::MOVING_LEFT, 3100, 50, eDirection::LEFT, 2700, 3200);
	guardShort->InIt();
	_listObject.push_back(guardShort);

    _aladdin = new Aladdin();
	_aladdin->InIt();
	_aladdin->setPosition(2000,250);
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
}

void PlayScene::Draw(LPD3DXSPRITE spriteHandle)
{
	_background->Draw(spriteHandle,_viewport);
	for each (auto object in _listObject)
	{
		if (object == nullptr || object->isInStatus(DESTROY))
			continue;
		object->Draw(spriteHandle, _viewport);
		object->ShowBB();
	}
	//_backgroundfront->Draw(spriteHandle, _viewport);
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
		Vector2(max(aladdin->getPositionX() - 420, 0),
			max(aladdin->getPositionY() + 500, WINDOWS_HEIGHT));		// 420 va 500 khoảng cách tối đa giữa object và map -> hardcode
																		// Không cho đi quá map.
	if (new_position.x + WINDOWS_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOWS_WIDTH;
	}
	_viewport->setPositionWorld(new_position);
}