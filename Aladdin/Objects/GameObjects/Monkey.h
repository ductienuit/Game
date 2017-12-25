#pragma once
#ifndef _MONKEY_H
#define _MONKEY_H
#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include "../BaseObject.h"
#include"../GameObjects/Aladdin.h"

#define MONKEY_SPEED 120

using namespace std;

class Monkey : public BaseObject
{
public:
	Monkey(eStatus status, int posX, int posY, eDirection direction);

	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void movingLeft();
	void standing();

	IComponent* getComponent(string componentName);
	Text* text;
	~Monkey();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Sprite *_divingSprite;
	Vector2 _originPosition;
};
#endif
