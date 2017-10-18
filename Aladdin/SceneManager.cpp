#include "SceneManager.h"

USEGAME_FRAMEWORK

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

SceneManager * SceneManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SceneManager();
	}
	return _instance;
}

bool SceneManager::InIt()
{
	if (!_scenes.empty())
	{
		_scenes.back()->InIt(); //Chạy scene cuối trong vector
	}
	return true;
}

void SceneManager::Update(float deltatime)
{
	if (!_scenes.empty())
		_scenes.back()->Update(deltatime);
}

void SceneManager::UpdateInput(float delta)
{
	if (!_scenes.empty())
		_scenes.back()->UpdateInput(delta);
}

void SceneManager::Draw(LPD3DXSPRITE spriteHandle)
{
	if (!_scenes.empty())
		_scenes.back()->Draw(spriteHandle);
}

void SceneManager::Release()
{
	if (!_scenes.empty())
	{
		_scenes.back()->Release();
		
	}
}

void SceneManager::AddScene(Scene * scene)
{
	_scenes.push_back(scene);
	_scenes.back()->InIt();
}

void SceneManager::RemoveScene()
{
	if (!_scenes.empty())
	{
		//Release trong class, rồi xóa con trỏ, rồi mới xóa trong vector
		_scenes.back()->Release();   
		delete _scenes.back();
		_scenes.pop_back();
	}
}

void SceneManager::ReplaceScene(Scene * scene)
{
	this->RemoveScene();
	this->AddScene(scene);
}

void SceneManager::ClearScenes()
{
	while (!_scenes.empty())
	{
		_scenes.back()->Release();
		delete _scenes.back();
		_scenes.pop_back();
	}
}

Scene * SceneManager::getCurrentScene()
{
	if (!_scenes.empty())
	{
		return _scenes.back();
	}
	return nullptr;
}
