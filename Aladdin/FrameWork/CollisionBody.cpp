#include "CollisionBody.h"

CollisionBody::CollisionBody(BaseObject * target)
{
	_target = target;
	_collidePosition = Vector2(0, 0);
}

CollisionBody::~CollisionBody()
{
}

void CollisionBody::checkCollision(BaseObject * otherObject, float dt)
{
	eDirection direction;
	RECT myRect = _target->getSprite()->getBounding();
	myRect.left += 15;
	myRect.right -= 15;
	myRect.top -= 30;
	RECT otherRect = otherObject->getSprite()->getBounding();
#pragma region Visualize collision
	RECT BBox = myRect;
	float top = WINDOWS_HEIGHT - BBox.top;
	float left = BBox.left;
	float right = BBox.right;
	float bottom = WINDOWS_HEIGHT - BBox.bottom;

	LPD3DXLINE line;
	auto dv = DeviceManager::getInstance()->getDevice();
	D3DXCreateLine(dv, &line);
	D3DXVECTOR2 lines[] = { D3DXVECTOR2(left, top),
	D3DXVECTOR2(right, top),
	D3DXVECTOR2(right, bottom),
	D3DXVECTOR2(left, bottom),
	D3DXVECTOR2(left, top),
	D3DXVECTOR2(right, bottom) };
	line->SetWidth(1);
	line->Begin();
	line->Draw(lines, 6, 0xffffffff);
	line->End();
	line->Release();
#pragma endregion
	/*Có được thời gian rồi thì mình bắt đầu xét va chạm:

	time > 1.0f: frame tiếp theo nó vẫn chưa thể va chạm.
	time < 0.0f: 2 hình chữ nhật đang đi ra xa nhau.
	Thời gian để kết thúc va chạm phải lớn hơn thời gian để va chạm (va chạm xong rồi thì sau đó mới hết chứ đúng không).
	Khi có thể va chạm mình sẽ trả về thời gian va chạm đó, còn không trả về 1.0f*/
	float time = isCollide(myRect, otherRect, direction, dt);
	if (time < 1.0f)
	{
		CollisionEventArg* e = new CollisionEventArg(otherObject);
		e->_sideCollision = direction;
		__debugoutput<int>(1);
		__raise onCollisionBegin(e);
		_isColliding = true;
	}
	else if (_isColliding)
	{
		float x, y;
		if (!AABB(myRect, otherRect))
		{
			CollisionEventArg* e = new CollisionEventArg(otherObject);
			e->_sideCollision = eDirection::NONE;
			__debugoutput<int>(2);
			__raise onCollisionEnd(e);
			_isColliding = false;
		}
	}
	/*Chỉ cần dùng AABB*/
	//if (AABB(_target->getBounding(), otherObject->getBounding())==true)
	//{
	//	CollisionEventArg* e = new CollisionEventArg(otherObject);
	//	//e->_sideCollision = direction;
	//	__debugoutput<int>(1);
	//	__raise onCollisionBegin(e);
	//	_isColliding = true;
	//}
	//else if (_isColliding)
	//{
	//	float x, y;
	//	if (!AABB(_target->getSprite()->getBounding(), otherObject->getSprite()->getBounding()))
	//	{
	//		CollisionEventArg* e = new CollisionEventArg(otherObject);
	//		e->_sideCollision = eDirection::NONE;
	//		__debugoutput<int>(2);
	//		__raise onCollisionEnd(e);
	//		_isColliding = false;
	//	}
	//}
}

float CollisionBody::isCollide(RECT myRect, RECT otherRect, eDirection & direction, float dt)
{
	/*25/11 Sửa bởi Tiến */

	// sử dụng Broadphase rect để kt vùng tiếp theo có va chạm ko
	RECT broadphaseRect = getSweptBroadphaseRect(_target, dt);
	if (AABB(broadphaseRect, otherRect))
	{
		return 0.5f;
	}

	float entryTime = SweptAABB(myRect, otherRect, direction, dt);

	return entryTime;
}

bool CollisionBody::isColliding(BaseObject * otherObject, float & moveX, float & moveY, float dt)
{
	moveX = moveY = 0.0f;
	auto myRect = _target->getSprite()->getBounding();
	auto otherRect = otherObject->getSprite()->getBounding();
	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	// kt coi có va chạm không
	//  CÓ va chạm khi 
	//  left < 0 && right > 0 && top > 0 && bottom < 0
	//
	if (left > 0 || right < 0 || top < 0 || bottom > 0)
		return false;

	// tính offset x, y để đi hết va chạm
	// lấy khoảng cách nhỏ nhất
	moveX = abs(left) < right ? left : right;
	moveY = abs(top) < bottom ? top : bottom;

	// chỉ lấy offset nhỏ nhất
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}
//Đúng
bool CollisionBody::AABB(RECT myRect, RECT otherRect)
{
	/*25/11 Đức Tiến đã sửa*/
	float left = otherRect.left - myRect.right;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;
	float top = otherRect.top - myRect.bottom;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}
//Đúng
float CollisionBody::SweptAABB(RECT myRect, RECT otherRect, eDirection & direction, float dt)
{
	//Đọc để biết chi tiết
	https://luuthevinh.me/2016/11/xet-va-xu-ly-va-cham-bang-swept-aabb
	http://levohuutri.blogspot.com/2013/11/kiem-tra-va-xu-ly-va-cham-voi-swept.html
	//SweptAABB
	//Khoảng di chuyển giữa mỗi frame
	Vector2 velocity = Vector2(_target->getVelocity().x*dt / 1000, _target->getVelocity().y*dt / 1000);
	// tìm khoảng cách giữa cạnh gần nhất, xa nhất 2 object dx, dy
	// dx
	if (velocity.x > 0)
	{
		_dxEntry = otherRect.left - myRect.right;
		_dxExit = otherRect.right - myRect.left;
	}
	else
	{
		_dxEntry = otherRect.right - myRect.left;
		_dxExit = otherRect.left - myRect.right;
	}

	// dy
	if (velocity.y > 0)
	{
		_dyEntry = otherRect.bottom - myRect.top;
		_dyExit = otherRect.top - myRect.bottom;
	}
	else
	{
		_dyEntry = otherRect.top - myRect.bottom;
		_dyExit = otherRect.bottom - myRect.top;
	}

	// tìm thời gian va chạm 
	if (velocity.x == 0)
	{
		// chia cho 0 ra vô cực
		_txEntry = -std::numeric_limits<float>::infinity();
		_txExit = std::numeric_limits<float>::infinity();
	}

	else
	{
		_txEntry = _dxEntry / velocity.x;
		_txExit = _dxExit / velocity.x;
	}

	if (velocity.y == 0)
	{
		_tyEntry = -std::numeric_limits<float>::infinity();
		_tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		_tyEntry = _dyEntry / velocity.y;
		_tyExit = _dyExit / velocity.y;
	}

	// thời gian va chạm
	// thời gian va chạm là thời gian lớn nhất của 2 trục(2 trục phải cùng tiếp xúc thì mới va chạm)
	float entryTime = max(_txEntry, _tyEntry);
	// thời gian hết va chạm là thời gian của 2 trục, (1 cái ra khỏi là object hết va chạm)
	float exitTime = min(_txExit, _tyExit);

	// object không va chạm khi:
	// nếu thời gian bắt đầu va chạm hơn thời gian kết thúc va chạm
	// thời gian va chạm x, y nhỏ hơn 0 (chạy qua luôn, 2 thằng đang đi xa ra nhau)
	// thời gian va chạm x, y lớn hơn 1 (còn xa quá chưa thể va chạm) 
	if (entryTime > exitTime ||
		_txEntry < 0.0f && _tyEntry < 0.0f ||
		_txEntry > 1.0f ||
		_tyEntry > 1.0f)
	{
		//Không va chạm
		return 1.0f;
	}

	//khi va chạm được xác nhận diễn ra,
	//vận tốc sẽ được biến đổi để thể hiện 
	//được phản ứng của đối tượng với va chạm.
	else
	{
		if (_txEntry > _tyEntry)
		{
			// xét x
			// khoảng cách gần nhất mà nhỏ hơn 0 nghĩa là 
			//thằng kia đang nằm bên trái object này 
			//=> va chạm bên phải nó
			if (_dxEntry > 0.0f)
			{
				direction = eDirection::RIGHT;
				//__debugoutput<int>(1);
			}
			else
			{
				direction = eDirection::LEFT;
				//__debugoutput<int>(2);
			}
		}
		if (_txEntry < _tyEntry)
		{
			// xét y
			if (_dyEntry > 0.0f)
			{
				direction = eDirection::TOP;
				//__debugoutput<int>(3);
			}
			else
			{
				direction = eDirection::BOTTOM;
				//__debugoutput<int>(4);
			}
		}
	}
	return entryTime;
}
//Đúng
RECT CollisionBody::getSweptBroadphaseRect(BaseObject* object, float dt)
{
	auto velocity = Vector2(object->getVelocity().x * dt / 1000, object->getVelocity().y * dt / 1000);
	auto myRect = object->getBounding();
	myRect.left += 40;
	myRect.right -= 40;
	myRect.top -= 40;


	RECT rect;
	rect.top = velocity.y > 0 ? myRect.top + velocity.y : myRect.top;
	rect.bottom = velocity.y > 0 ? myRect.bottom : myRect.bottom + velocity.y;
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.right = velocity.x > 0 ? myRect.right + velocity.x : myRect.right;

#pragma region Visualize collision
	/*RECT BBox = rect;
	float top = WINDOWS_HEIGHT - BBox.top;
	float left = BBox.left;
	float right = BBox.right;
	float bottom = WINDOWS_HEIGHT - BBox.bottom;

	LPD3DXLINE line;
	auto dv = DeviceManager::getInstance()->getDevice();
	D3DXCreateLine(dv, &line);
	D3DXVECTOR2 lines[] = { D3DXVECTOR2(left, top),
		D3DXVECTOR2(right, top),
		D3DXVECTOR2(right, bottom),
		D3DXVECTOR2(left, bottom),
		D3DXVECTOR2(left, top),
		D3DXVECTOR2(right, bottom) };
	line->SetWidth(1);
	line->Begin();
	line->Draw(lines, 6, 0xffffffff);
	line->End();
	line->Release();*/
#pragma endregion
		
	return rect;
}

bool CollisionBody::isColliding()
{
	return _isColliding;
}

void CollisionBody::Update(float dt)
{

}