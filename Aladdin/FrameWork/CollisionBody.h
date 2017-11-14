#ifndef __COLLISION_BODY__
#define __COLLISION_BODY__


#include "../Objects/GameObjects/BaseObject.h"
#include "IComponent.h"

/*
Sử dụng cho đối tượng muốn xét va chạm
*/

class CollisionEventArg : public EventArg
{
public:
	CollisionEventArg(BaseObject* object)
	{
		_otherObject = object;
		_sideCollision = eDirection::NONE;
	}

	BaseObject* _otherObject;
	eDirection _sideCollision;
private:

};

[event_source(native)]
class CollisionBody : public IComponent
{
public:
	CollisionBody(BaseObject* target);
	~CollisionBody();

	/*
	ki?m tra va ch?m v?i object khác
	@otherObject: ??i t??ng kt va ch?m v?i nó
	@dt: delta time c?a c?a m?i frame
	*/
	void checkCollision(BaseObject* otherObject, float dt);
	bool isColliding();

	void Update(float dt);

	__event void onCollisionBegin(CollisionEventArg* e);
	__event void onCollisionEnd(CollisionEventArg* e);

private:
	BaseObject* _target;
	float _dxEntry, _dyEntry, _dxExit, _dyExit;
	float _txEntry, _tyEntry, _txExit, _tyExit;

	bool _isCollide;
	bool _isColliding;
	Vector2 _collidePosition;
	eDirection _collideSide;

	float isCollide(BaseObject* otherObject, eDirection& direction, float dt);
	bool isColliding(RECT myRect, RECT otherRect);
	bool isColliding(BaseObject* otherObject, float& moveX, float& moveY, float dt);

	RECT getSweptBroadphaseRect(BaseObject* object, float dt);
};

#endif // !__COLLISION_BODY__
