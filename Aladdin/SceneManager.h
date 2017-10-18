#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include"define.h"
#include<vector>
#include"Scene.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN


/* 
Quản lí cảnh
Quản lí các ảnh intro, menu, play ...*/
class SceneManager
{
public: 
	~SceneManager();
	static SceneManager* getInstance();

	bool InIt();
	void Update(float deltatime);
	void UpdateInput(float delta);
	void Draw(LPD3DXSPRITE spriteHandle);
	void Release();

	void AddScene(Scene* scene);
	void RemoveScene();
	void ReplaceScene(Scene* scene);
	void ClearScenes();
	Scene* getCurrentScene();

private:
	SceneManager();	
	static SceneManager* _instance;	
	vector<Scene*>	     _scenes;
	
};
GAME_FRAMEWORK_END
#endif __SCENE_MANAGER_H__