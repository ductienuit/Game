#ifndef __COLLISION_BODY__
#define __COLLISION_BODY__


#include "../Objects/BaseObject.h"
#include "IComponent.h"
#include"Text.h"
#include"../Objects/GameObjects/Objects/Land.h"

/*Sử dụng cho đối tượng muốn kt va chạm
- Thêm nó như là một Component vào object
- Có 2 Event là :
@onCollisionBegin: sẽ được gọi khi bắt đầu va chạm
@onCollisionEnd: sẽ được gọi khi kết thúc va chạm
- Đối tượng sử dụng Collision body muốn dùng event thì gán 2 event trên để sử dụng
- Thêm[event_receiver(native)] vào trước class định nghĩa object
- Viết hàm có THAM SỐ như sau :
+void onCollisionBegin(CollisionEventArg* collision_event);
+void onCollisionEnd(CollisionEventArg* collision_event);
-Gán hàm cho Collision Body
+ __hook(&CollisionBody::onCollisionBegin, <collision body của object>, &<tên lớp>::<tên hàm>);
-Việc kiểm tra và sử lý va chạm cho đối tượng đó sẽ làm bên trong 2 hàm BEGIN và END.
- CollisionEventArg:
+Đối tượng va chạm với đối tượng hiện tại.
+ _sideCollision : phía va chạm của đối tượng kia.
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
	kiểm tra va chạm ala với land
	@otherObject: đối tượng land va chạm với aladdin
	@dt: delta time thời gian vòng lặp trước
	*/
	void checkCollision(BaseObject* otherObject, float dt);

	/*
	Kiểm tra va chạm ala với enermy
	@otherObject: đối tượng va chạm với this
	*/
	void checkCollision(BaseObject* otherObject, float dt,bool isEnermy);

	bool isColliding();

	void Update(float dt);

	__event void onCollisionBegin(CollisionEventArg* e);
	__event void onCollisionEnd(CollisionEventArg* e);
	Text *text;
private:
	BaseObject* _target;
	BaseObject* _preObject;
	float	_dxEntry, //Khoảng cách cần đi để bắt đầu va chạm
			_dyEntry, //Khoảng cách cần đi để bắt đầu va chạm
			_dxExit,  // Khoảng cách cần đi kể từ lúc này để khi hết va chạm
			_dyExit;  // Khoảng cách cần đi kể từ lúc này để khi hết va chạm
	float _txEntry, _tyEntry, _txExit, _tyExit;

	bool _isCollide;
	bool _isColliding;
	bool _flagEnd;
	Vector2 _collidePosition;
	eDirection _collideSide;

	float isCollide(RECT myRect, RECT otherRect, eDirection& direction, float dt);
	bool AABB(RECT myRect, RECT otherRect);
	float SweptAABB(RECT myRect,RECT otherRect, eDirection & direction, float dt);
	bool isColliding(BaseObject* otherObject, float& moveX, float& moveY, float dt);

	RECT getBroadphaseRect(BaseObject* object, float dt);
};
void DrawRect(RECT otherRect);
#endif // !__COLLISION_BODY__
