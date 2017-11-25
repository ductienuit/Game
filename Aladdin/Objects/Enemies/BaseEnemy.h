#ifndef _BASE_ENEMY_H
#define _BASE_ENEMY_H

#include "../BaseObject.h"
#include "../../FrameWork/CollisionBody.h"

#define ENEMY_GRAVITY 500

class BaseEnemy : public BaseObject
{
public:
	BaseEnemy();
	BaseEnemy(eID);

	int getHitpoint();
	void setHitpoint(int);
	int getScore();
	void setScore(int);
	virtual void dropHitpoint();
	virtual void dropHitpoint(int damage);

	virtual ~BaseEnemy();
protected:
	void gainScore();
	int _hitpoint;
	int _score;
};
#endif