#ifndef _ROPE_H__
#define _ROPE_H__

#include "../Aladdin/FrameWork/Animation.h"
#include "../Aladdin/FrameWork/StopWatch.h"

#include "../Aladdin/Objects/GameObjects/BaseObject.h"
#include "../Aladdin/FrameWork/IComponent.h"
#include "../Aladdin/FrameWork/Scene.h"

using namespace std;

class Rope : public BaseObject
{
  
public:	
	Rope();
	~Rope();
	
	// Các phương thức kế thừa từ BaseObject.
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, Viewport*) override;
	void Release() override;

	// Kiểm tra va chạm.
	float checkCollision(BaseObject* object, float dt);
private:
	Animation* _animations;
};
#endif _ROPE_H__