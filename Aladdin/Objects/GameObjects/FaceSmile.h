#ifndef _FACE_SMILE_H_
#define _FACE_SMILE_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Text.h"
#include"../../FrameWork/CollisionBody.h"
#include"../Score/InforAladdin.h"
#include "../BaseObject.h"

using namespace std;

class FaceSmile : public BaseObject
{
public:
	FaceSmile(int posX, int posYBase);
	FaceSmile(int posX, int posY, bool isBoss);
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, ViewPort*) override;
	void Release() override;

	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);
	~FaceSmile();
private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	Text* text;
};
#endif _FACE_SMILE_H