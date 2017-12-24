#ifndef __SCORE_ALADDIN_H__
#define __SCORE_ALADDIN_H__

#include "../../FrameWork/define.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

#define MAXAPPLE 100
#define MAXLIFE 20


class InforAladdin
{
public:
	InforAladdin(void);
	~InforAladdin(void);
	static InforAladdin*    getInstance();
	static void				plusScore(int value);
	static int				getScore();

	static void				plusHealth(int value);
	static void				setHealth(int value);
	static int			    getHealth();

	static void				plusLife(int value);
	static int				getLife();

	static void				plusCoin(int value);
	static int				getCoin();

	static void				plusApple(int value);
	static int				getApple();

	static void				Infinity();
	static void				NonInfinity();

	void					Release();
private:
	static InforAladdin*    _instance;
	static int _health;
	static int _score;
	static int _coin;
	static int _apple;
	static int _life;
	static bool _infinity;
};
typedef InforAladdin *pInforAladdin;
GAME_FRAMEWORK_END

#endif //!__SCORE_ALADDIN_H__
