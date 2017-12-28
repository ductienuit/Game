#ifndef _STRIP_ALADDIN_H_
#define _STRIP_ALADDIN_H_

#include "../../../FrameWork/Animation.h"
#include "../../../FrameWork/StopWatch.h"
#include "../../../FrameWork/IComponent.h"
#include "../../../FrameWork/Text.h"
#include"../../../FrameWork/CollisionBody.h"
#include"../../BaseObject.h"
#include"../../../FrameWork/ReadMapEditor.h"

using namespace std;

class StripAladdin : public BaseObject
{
public:
	StripAladdin(int posX, int posY);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);
	~StripAladdin();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Text* text;
};
#endif _STRIP_ALADDIN_H_