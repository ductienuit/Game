#include "PlayScene.h"


Viewport* PlayScene::_viewport = new Viewport(0, WINDOWS_HEIGHT);

PlayScene::PlayScene()
{
	//_viewport = new Viewport(0,600);
}

PlayScene::~PlayScene()
{
	delete _viewport;
	_viewport = nullptr;
}
void PlayScene::setViewport(Viewport * viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

Viewport * PlayScene::getViewport()
{
	return _viewport;
}

bool PlayScene::InIt()
{

	//sprite = SpriteManager::getInstance()->getSprite(eID::BILL);
	//
	//auto soldier = new Soldier();
	//soldier->InIt();
	//_listobject.push_back(soldier);

	//auto falcon = new Falcon();
	//falcon->InIt();
	//_listobject.push_back(falcon);

	//auto mario = new Mario();
	//mario->InIt();
	//_listobject.push_back(mario);
	//_listControlObject.push_back(mario);

	//auto redcannon = new RedCannon(GVector2(500, 500));
	//_listobject.push_back(redcannon);

	auto rope = new Rope();
	rope->InIt();
	_listobject.push_back(rope);

	auto aladdin = new Aladdin();
    aladdin->InIt();
	aladdin->setPosition(200, 100);
	_listControlObject.push_back(aladdin);
	_listobject.push_back(aladdin);



	
	

	/*_text = new Text(L"Arial", "", 10, 25);

	auto aircraft = new AirCraft(START_POSITION, HORIZONTAL_VELOC, AIRCRAFT_AMPLITUDE, AIRCRAFT_FREQUENCY, eAirCraftType::I);
	aircraft->InIt();
	_listobject.push_back(aircraft);
	_listControlObject.push_back(aircraft);
*/
	return true;
}

void PlayScene::UpdateInput(float dt)
{
	for each (IControlable* obj in _listControlObject)
	{
		obj->UpdateInput(dt);
	}
}

void PlayScene::Update(float dt)
{

	//char str[100];
	//sprintf(str, "delta time: %f", dt);
	//_text->setText(str);

	for each (auto object in _listobject)
	{
		object->Update(dt);
	}
}

void PlayScene::Draw(LPD3DXSPRITE spriteHandle)
{
	//sprite->render(spriteHandle, _viewport);
	//_text->draw();

	for each (auto object in _listobject)
	{
		object->Draw(spriteHandle, _viewport);
	}
}

void PlayScene::Release()
{
	for each (auto object in _listobject)
	{
		object->Release();
	}
}
