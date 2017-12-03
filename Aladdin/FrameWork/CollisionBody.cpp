#include "CollisionBody.h"

CollisionBody::CollisionBody(BaseObject * target)
{
	_target = target;
	_collidePosition = Vector2(0, 0);
	_flagEnd = false;
}

CollisionBody::~CollisionBody()
{
}

void CollisionBody::checkCollision(BaseObject * otherObject, float dt)
{
	eDirection direction;
	RECT myRect = _target->getBounding();
	RECT otherRect;
	if (otherObject->getId() == eID::LAND)
	{
		auto land = (Land*)otherObject;
		otherRect = land->getBounding();
	}
	else otherRect = otherObject->getBounding();
	/*Có được thời gian rồi thì mình bắt đầu xét va chạm:

	time > 1.0f: frame tiếp theo nó vẫn chưa thể va chạm.
	time < 0.0f: 2 hình chữ nhật đang đi ra xa nhau.
	Thời gian để kết thúc va chạm phải lớn hơn thời gian để va chạm (va chạm xong rồi thì sau đó mới hết chứ đúng không).
	Khi có thể va chạm mình sẽ trả về thời gian va chạm đó, còn không trả về 1.0f*/

	RECT broadphaseRect = getSweptBroadphaseRect(_target, dt);
	if (AABB(broadphaseRect, otherRect)==true)
	{
		float time = SweptAABB(myRect, otherRect, direction, dt);
		auto land = (Land*)otherObject;
		//Ưu tiên
		if (1 - time > 0)
		{
			CollisionEventArg* e = new CollisionEventArg(otherObject);
			e->_sideCollision = direction;
			_preObject = otherObject;
			__raise onCollisionBegin(e);
			_flagEnd = true;
		}
		if (land->getType() == eLandType::STOP)
		{
			_target->StopUp();
		}
		_isColliding = true;
	}
	else
	{
		if (_preObject == NULL)
			return;
		if (AABB(_target->getSprite()->getBounding(),_preObject->getBounding()) == false )
		{
			_isColliding = false;
		}
	}

	if (_isColliding == false && _flagEnd==true)
	 {
			CollisionEventArg* e = new CollisionEventArg(_preObject); //Đối số PreObject thứ 2 không sử dụng

			__raise onCollisionEnd(e);
			_flagEnd = false;
	}
}

/*Code này không sử dụng*/
float CollisionBody::isCollide(RECT myRect, RECT otherRect, eDirection & direction, float dt)
{
	/*25/11 Sửa bởi Tiến */

	// sử dụng Broadphase rect để kt vùng tiếp theo có va chạm ko
	RECT broadphaseRect = getSweptBroadphaseRect(_target, dt);
	if (AABB(broadphaseRect, otherRect)==false)
	{
		return 1.0f; //Khong va cham
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
bool CollisionBody::AABB(RECT rect1, RECT rect2)
{
	/*25/11 Đức Tiến đã sửa*/
	return !(rect2.left > rect1.right||	rect2.right < rect1.left ||	rect2.top < rect1.bottom  ||rect2.bottom > rect1.top);
}
#pragma region SweptAABB version 1
//float CollisionBody::SweptAABB(RECT myRect, RECT otherRect, eDirection & direction, float dt)
//{
//	//Đọc để biết chi tiết
//https://luuthevinh.me/2016/11/xet-va-xu-ly-va-cham-bang-swept-aabb
//http://levohuutri.blogspot.com/2013/11/kiem-tra-va-xu-ly-va-cham-voi-swept.html
//	 //SweptAABB
//	 //Khoảng di chuyển giữa mỗi frame
//	Vector2 velocity = Vector2(_target->getVelocity().x, _target->getVelocity().y);
//	// tìm khoảng cách giữa cạnh gần nhất, xa nhất 2 object dx, dy
//	// dx
//	if (velocity.x > 0)
//	{
//		_dxEntry = otherRect.left - myRect.right;
//		_dxExit = otherRect.right - myRect.left;
//	}
//	else
//	{
//		_dxEntry = otherRect.right - myRect.left;
//		_dxExit = otherRect.left - myRect.right;
//	}
//
//	// dy
//	if (velocity.y > 0)
//	{
//		_dyEntry = otherRect.top - myRect.bottom;  //dm lỗi ở đây nề
//		_dyExit = otherRect.bottom - myRect.top;
//	}
//	else
//	{
//		_dyEntry = otherRect.bottom - myRect.top;
//		_dyExit = otherRect.top - myRect.bottom;
//	}
//
//	// tìm thời gian va chạm 
//	if (velocity.x == 0)
//	{
//		// chia cho 0 ra vô cực
//		_txEntry = -std::numeric_limits<float>::infinity();
//		_txExit = std::numeric_limits<float>::infinity();
//	}
//
//	else
//	{
//		_txEntry = _dxEntry / velocity.x;
//		_txExit = _dxExit / velocity.x;
//	}
//
//	if (velocity.y == 0)
//	{
//		_tyEntry = -std::numeric_limits<float>::infinity();
//		_tyExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		_tyEntry = _dyEntry / velocity.y;
//		_tyExit = _dyExit / velocity.y;
//	}
//
//	// thời gian va chạm
//	// thời gian va chạm là thời gian lớn nhất của 2 trục(2 trục phải cùng tiếp xúc thì mới va chạm)
//	float entryTime = max(_txEntry, _tyEntry);
//	// thời gian hết va chạm là thời gian của 2 trục, (1 cái ra khỏi là object hết va chạm)
//	float exitTime = min(_txExit, _tyExit);
//
//	// object không va chạm khi:
//	// nếu thời gian bắt đầu va chạm hơn thời gian kết thúc va chạm
//	// thời gian va chạm x, y nhỏ hơn 0 (chạy qua luôn, 2 thằng đang đi xa ra nhau)
//	// thời gian va chạm x, y lớn hơn 1 (còn xa quá chưa thể va chạm) 
//	if (entryTime > exitTime ||
//		_txEntry < 0.0f && _tyEntry < 0.0f
//		|| _txEntry>1.0f || _tyEntry>1.0f)
//	{
//		//Không va chạm		
//		return 1.0f;
//	}
//
//	//khi va chạm được xác nhận diễn ra,
//	//vận tốc sẽ được biến đổi để thể hiện 
//	//được phản ứng của đối tượng với va chạm.
//	else
//	{
//		if (_txEntry > _tyEntry)
//		{
//			// xét x
//			// khoảng cách gần nhất mà nhỏ hơn 0 nghĩa là 
//			//thằng kia đang nằm bên trái object này 
//			//=> va chạm bên phải nó
//			if (_dxEntry > 0.0f)
//			{
//				direction = eDirection::RIGHT;
//				//__debugoutput<int>(1);
//			}
//			else
//			{
//				direction = eDirection::LEFT;
//				//__debugoutput<int>(2);
//			}
//		}
//		if (_txEntry < _tyEntry)
//		{
//			// xét y
//
//
//			if (_dyEntry > 0.0f)
//			{
//				direction = eDirection::TOP;
//				//__debugoutput<int>(3);
//			}
//			else
//			{
//				direction = eDirection::BOTTOM;
//				//__debugoutput<int>(4);
//			}
//		}
//	}
//	return entryTime;
//}
#pragma endregion

#pragma region SweptAABB version 2
float CollisionBody::SweptAABB(RECT b1, RECT b2, eDirection & direction, float dt)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	Vector2 velocity = Vector2(_target->getVelocity().x, _target->getVelocity().y);
	// find the distance between the objects on the near and far sides for both x and y
	if (velocity.x > 0.0f)
	{
		xInvEntry = b2.left - (b1.right);
		xInvExit = (b2.right) - b1.left;
	}
	else
	{
		xInvEntry = (b2.right) - b1.left;
		xInvExit = b2.left - (b1.right);
	}

	if (velocity.y < 0.0f)
	{
		yInvEntry = b2.top - (b1.bottom);
		yInvExit = (b2.bottom) - b1.top;
	}
	else
	{
		yInvEntry = (b2.bottom) - b1.top;
		yInvExit = b2.top - (b1.bottom);
	}
	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (velocity.x==0)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / velocity.x;
		xExit = xInvExit / velocity.x;
	}

	if (velocity.y == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / velocity.y;
		yExit = yInvExit / velocity.y;
	}
	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		direction = NONE;
		return 1.0f;
	}

	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				direction = RIGHT;
			}
			else
			{
				direction = LEFT;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				direction = TOP;
			}
			else
			{
				direction = BOTTOM;
			}
		}
		// return the time of collision
		return entryTime;
	}

}
#pragma endregion

//Đúng
RECT CollisionBody::getSweptBroadphaseRect(BaseObject* object, float dt)  //object day la Aladdin
{
	/*Tại sao không chia 1000 mà chia 500 ?
		+	Chia 500 sẽ tạo ra BroadPhaseRect có tỷ lệ to hơn, 
		check collision sẽ đúng không bị overlaprect  */
	auto velocity = Vector2(object->getVelocity().x * dt/400, object->getVelocity().y * dt/400 );
	//__debugoutput(velocity.y);
	auto myRect = object->getBounding();
	RECT rect;
	DrawRect(myRect);
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.right = velocity.x > 0 ? myRect.right + velocity.x : myRect.right;
	rect.top = velocity.y > 0 ? velocity.y + myRect.top: myRect.top;
	rect.bottom = velocity.y > 0 ? myRect.bottom : myRect.bottom + velocity.y;
	DrawRect(rect);
	return rect;
}

bool CollisionBody::isColliding()
{
	return _isColliding;
}

void CollisionBody::Update(float dt)
{

}

void DrawRect(RECT otherRect)
{
#pragma region Visualize collision
	RECT BBox = otherRect;
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
}