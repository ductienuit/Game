#ifndef _SOLID_H__
#define _SOLID_H__

#include"../../../FrameWork/Animation.h"
#include "../../../FrameWork/StopWatch.h"

#include"../../BaseObject.h"
#include "../../../FrameWork/IComponent.h"
#include "../../../FrameWork/Scene.h"

using namespace std;

class Tile : public BaseObject
{
  
public:	
	Tile(float x,float y ,eID id, int left, int top, int right,int bottom);
	~Tile();
	
	// Các phương thức kế thừa từ BaseObject.
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, Viewport*) override;
	void Release() override;
	void ShowBB() override;

	// Kiểm tra va chạm.
	float checkCollision(BaseObject* object, float dt);
private:
	Animation* _animations;
};
#endif _SOLID_H__