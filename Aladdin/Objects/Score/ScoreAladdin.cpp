#include "ScoreAladdin.h"

USEGAME_FRAMEWORK

ScoreAladdin* ScoreAladdin::_instance = nullptr;
int ScoreAladdin::_score = 100;
int ScoreAladdin::_health = 100;
ScoreAladdin::~ScoreAladdin()
{
}

ScoreAladdin * ScoreAladdin::getInstance()
{
	if (_instance == NULL)
		_instance = new ScoreAladdin();
	return _instance;
}

void ScoreAladdin::plusScore(int value)
{
	_score += value;
}

void ScoreAladdin::plusHealth(int value)
{
	_health += value;
}

int ScoreAladdin::getHealth()
{
	return _health;
}

int ScoreAladdin::getScore()
{
	return _score;
}

ScoreAladdin::ScoreAladdin(void)
{
}

void ScoreAladdin::Release()
{
	delete _instance;
	_instance = nullptr;
}
