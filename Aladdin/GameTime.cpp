#include "GameTime.h"
USEGAME_FRAMEWORK

GameTime* GameTime::_instance = nullptr;

GameTime::GameTime(void)
{
}

GameTime::GameTime(TimeSpan& elapsedGameTime)
{
	this->_elapsedGameTime = elapsedGameTime;
}

GameTime::~GameTime(void)
{
}

GameTime* GameTime::getInstance()
{
	if (_instance == nullptr)
		_instance = new GameTime();
	return _instance;
}

void GameTime::Release()
{
	delete _instance;
	_instance = NULL;
}

void GameTime::InIt()
{
	
	QueryPerformanceFrequency(&this->_Query);

	this->_freQuery = (float)_Query.QuadPart / 10000000;
	// 10000000 nghĩa là dùng microsecond.
	// nếu dùng milisecond thì 1000
	// nếu dùng second     thì 1

	//Lấy thời gian hiện tại
	QueryPerformanceCounter(&_Query);
	lastTicks = _Query.QuadPart;
	_totalGameTime = (TimeSpan)0;
}

void GameTime::ResetLastTick()
{
	lastTicks = 0;
	curTicks = 0;
	_totalGameTime = (TimeSpan)0;
}

void GameTime::UpdateGameTime()
{
	QueryPerformanceCounter(&_Query);
	curTicks = _Query.QuadPart;
	if ((UINT64)((float)(curTicks - lastTicks) / _freQuery)   <  TimeSpan::TicksPerMilisecond * Engine::GetFrameRate())
	{
		//Cập nhật các hiệu ứng không yêu cầu nhiều fps
		return;
	}
	auto gt = ((float)(curTicks - lastTicks)) / _freQuery;
	this->setTotalGameTime(_totalGameTime + gt);
	this->setElapsedGameTime(
		TimeSpan((UINT64)gt)
	);
	lastTicks = curTicks;
}

float GameTime::GetElapsedGameTime()
{
	return this->_elapsedGameTime.getMiliSeconds();
}
float GameTime::GetTotalGameTime()
{
	return this->_totalGameTime.getMiliSeconds();
}
void GameTime::setElapsedGameTime(TimeSpan& elapsedgametime)
{
	this->_elapsedGameTime = elapsedgametime;
}
void GameTime::setTotalGameTime(TimeSpan& totalGametime)
{
	this->_totalGameTime = totalGametime;
}