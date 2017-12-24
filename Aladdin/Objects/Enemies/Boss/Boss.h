
#ifndef _BOSS_H
#define _BOSS_H

#include "../../FrameWork/Animation.h"
#include "../../../FrameWork/StopWatch.h"
#include "../../../FrameWork/IComponent.h"
#include "../../../FrameWork/Text.h"
#include "../BaseEnemy.h"
#include "../../GameObjects/Aladdin.h"
#include"../../Score/InforAladdin.h"
#include	<math.h>
#include"StripBoss.h"
#include"Star.h"
#include"FireBoss.h"


using namespace std;

class Boss : public BaseEnemy
{
public:
	Boss(eStatus status, int posX, int posY, Aladdin* aladdin);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);

	Vector2 distanceBetweenAladdin();
	void UpdateStatus(float dt);

	void OptimizeFire(RECT* rect);

	Text* text;
	~Boss();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	vector<BaseObject*> _listStar;
	Aladdin* _aladdin;
	bool isVersion2;
	Sprite *_divingSprite;
	vector<BaseObject*> _listFireBoss;
	StopWatch* _frequency;
	StopWatch* _frequencyFireBoss;

	bool isContain(BaseObject*object, RECT rect1);
};
#endif
