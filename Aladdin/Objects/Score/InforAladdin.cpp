#include "InforAladdin.h"

USEGAME_FRAMEWORK

InforAladdin* InforAladdin::_instance = nullptr;
int InforAladdin::_score = 100;
int InforAladdin::_health = 120;
int InforAladdin::_life = 3;
InforAladdin::~InforAladdin()
{
}

InforAladdin * InforAladdin::getInstance()
{
	if (_instance == NULL)
		_instance = new InforAladdin();
	return _instance;
}

void InforAladdin::plusScore(int value)
{
	_score += value;
}

void InforAladdin::plusHealth(int value)
{
	_health += value;
	if (_health>120)
	{
		_health = 120;
	}
}

void InforAladdin::setHealth(int value)
{
	_health = value;
}

int InforAladdin::getHealth()
{
	return _health;
}

void InforAladdin::plusLife(int value)
{
	_life += value;
}

int InforAladdin::getLife()
{
	return _life;
}

int InforAladdin::getScore()
{
	return _score;
}

InforAladdin::InforAladdin(void)
{
}

void InforAladdin::Release()
{
	delete _instance;
	_instance = nullptr;
}