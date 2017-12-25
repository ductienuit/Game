﻿#pragma once
#ifndef  _GameALADDIN_H_
#define _GameALADDIN_H
#include"../Aladdin/FrameWork/Game.h"
#include"../Aladdin/FrameWork/Manager/SceneManager.h"
#include"Scenes\PlayScene.h"
#include"Scenes\IntroScene.h"
#include"Scenes\BossScene.h"
#include"Scenes\EndScene.h"
#include"Scenes\DefeatScene.h"

using namespace std;
USEGAME_FRAMEWORK


class AladdinGame:public Game
{
public:
	AladdinGame(HINSTANCE hInstance,LPCSTR Name):Game(hInstance,Name){}
	~AladdinGame();

	void	InIt();   //Khởi tạo đối tượng
	void	Release();
	void	UpdateInput(float deltatime);  //override update input
	void	Update(float deltatime);       //override update your object
	void	Draw();                        //Draw your Object
	void	LoadResource();
};
#endif _GAMEALADDIN_H_


