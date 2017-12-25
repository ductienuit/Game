#include "InforAladdin.h"

USEGAME_FRAMEWORK

InforAladdin* InforAladdin::_instance = nullptr;
int InforAladdin::_score = 100;
int InforAladdin::_health = 120;
int InforAladdin::_life = 3;
int InforAladdin::_coin = 0;
int InforAladdin::_apple = 15;
bool InforAladdin::_infinity = false;

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
	if (_infinity)
	{
		_health = 120;
		return;
	}
	_health += value;
	if (_health>120)
	{
		_health = 120;
	}
	if (_health<0)
	{
		_health = 0;
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

void InforAladdin::plusCoin(int value)
{
	_coin += value;
	if (_coin < 0)
		_coin = 0;
}

int InforAladdin::getCoin()
{
	return _coin;
}

void InforAladdin::plusApple(int value)
{
	if (_infinity)
	{
		_apple = 99;
		return;
	}
	_apple += value;
	if (_apple < 0)
		_apple = 0;
}

int InforAladdin::getApple()
{
	return _apple;
}

void InforAladdin::Infinity()
{
	_infinity = true;
}

void InforAladdin::NonInfinity()
{
	_infinity = false;
	_score = 100;
	InforAladdin::_health = 120;
	InforAladdin::_life = 3;
	InforAladdin::_coin = 0;
	InforAladdin::_apple = 15;
}

void InforAladdin::Release()
{
	delete _instance;
	_instance = nullptr;
}
