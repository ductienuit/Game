#ifndef __SCORE_ALADDIN_H__
#define __SCORE_ALADDIN_H__

#include "../../FrameWork/define.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN


class ScoreAladdin
{
public:
	ScoreAladdin(void);
	~ScoreAladdin(void);
	static ScoreAladdin*    getInstance();
	static void				plusScore(int value);
	static void				plusHealth(int value);
	static int			    getHealth();
	static int				getScore();
	void					Release();
private:
	static ScoreAladdin*    _instance;
	static int _health;
	static int _score;
};
typedef ScoreAladdin *pScoreAladdin;
GAME_FRAMEWORK_END

#endif //!__SCORE_ALADDIN_H__
