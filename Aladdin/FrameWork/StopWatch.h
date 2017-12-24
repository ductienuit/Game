
#ifndef __STOP_WATCH__
#define __STOP_WATCH__

#include "GameTime.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

/*
now we have a type are called pFunction. It's just a type stores address of function.
example:
pFunction pF = &RandomFunction;
or
pFunction pF = &ClassName::Method

With RandomFunction and Method is a name of one function or method have no return value and argument
*/

typedef void(*pFunction)(void);

class StopWatch
{
public:
	StopWatch();
	~StopWatch();

	bool isFinish();
	bool isStart();
	bool isTimeLoop(float time);
	bool isStopWatch(float time);
	bool isLoopInTime();
	void timeLoopAction(float milisecond, pFunction action);
	void restart();
private:
	float	_stopwatch;
	bool	_isStart;
	bool	_isFinish;
};

GAME_FRAMEWORK_END

#endif // !__STOP_WATCH__
