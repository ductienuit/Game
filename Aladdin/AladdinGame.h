#pragma once
#ifndef  _GameALADDIN_H_
#define _GameALADDIN_H
#include"Engine.h"
#include"Game.h"

using namespace std;
USEGAME_FRAMEWORK


class AladdinGame:public Game
{
public:
	AladdinGame(HINSTANCE hInstance,LPCSTR Name);
	~AladdinGame();

	void InIt();
	void Run();

};
#endif _GAMEALADDIN_H_


