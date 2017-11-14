
#ifndef __ICOMPONENT_H__
#define __ICOMPONENT_H__
#include "define.h"
#include "Sprite.h"
#include <numeric>
#include <map>
using namespace std;
USEGAME_FRAMEWORK 
// = using namespace framework


			 /*
			 base component
			 các hiệu ứng nào có ảnh hưởng đến object suốt game thì kế thừa lại.
			 hãy chắc rằng bạn kiểm soát được hoàn toàn khả năng update của class kế thừa
			 (nên test bằng cách update rời trước)
			 Component được khai báo trong đối tượng chứ không được khai báo trong BaseObject.

			 bên trong object nếu muốn sử dụng Component thi có thê sử dụng vector, map hoặc pair, tuỳ thích.
			 Nhưng hãy chắc rằng bận hiểu cách sử dụng container.
			 seemore about container:

			 http://www.cplusplus.com/reference/map/map

			 Xem ví dụ class Mario, file mario.h
			 */
class IComponent
{
public:
	virtual void Update(float deltatime) = 0;
};

/*
Hiệu ứng chuyển động theo gia tốc và vận tốc.
Khi không chuyển động thì gia tốc và vận tốc bằng 0
Khi sử dụng:
Khởi tạo bên trong init của object.
Truyền refSprite = Sprite của object đó.
*/
class Movement : public IComponent
{
public:
	Movement(Vector2 accel, Vector2 veloc, Sprite* refSprite);
	void Update(float deltatime);

	void setAccelerate(Vector2 accel);
	void setVelocity(Vector2 veloc);
	Vector2 getAccelerate();
	Vector2 getVelocity();

private:
	Vector2 _accelerate;
	Vector2 _velocity;
	Sprite* _refSprite;
};


enum eGravityStatus
{
	FALLING__DOWN,
	SHALLOWED
};
class Gravity : public IComponent
{
public:
	// khởi tạo trọng lực của đối tượng, tham chiếu đến movement conponent của đối 
	// @gravity: vector trọng lực của đối tượng. sẽ không đổi theo thời gian
	// @movement: tham chiếu đến movement của đối tượng
	Gravity(Vector2 gravity, Movement *movement);

	// khi muốn nhảy. set lại status cho gravity là FALLING_DOWN
	// khi va chạm với đất set lại status cho gravity là  SHALLOWED
	void setStatus(eGravityStatus status);
	void Update(float deltatime);
	void setGravity(Vector2 gravity);
private:
	Vector2 _gravity;
	Vector2 _additionalVeloc;
	Movement* _refmovement;
	eGravityStatus _status;
};

// chuyển động hình sin
class SinMovement : public IComponent
{
public:
	/*
	chuyển động hình sin
	@amplitude :  biên độ
	@frequency : tần số chuyển động
	@Axis : hướng chuyển động ( = X hoặc Y)
	throw exception nếu Axis khác x hoặc y
	*/
	SinMovement(Vector2 amplitude, float frequency, Sprite* refSprite);

	void Update(float deltatime);
	void setAmplitude(Vector2 amplitude);
	void setFrequency(float freq);

private:
	Sprite* _refSprite;

	float _radianVeloc;			// vận tốc góc (= ω)
	float _radian;				// góc xoay (= φ) biến thiên theo thời gian

	Vector2 _amplitude;		// biên độ		(= A)
	Vector2 _linearVeloc;		// vận tốc tuyến tính (= ωA)

};

class RoundMovement : public IComponent
{
public:

	RoundMovement(float radius, float frequency, float radian, Sprite* refSprite);

	void Update(float deltatime);
	void setRadius(float r);
	void setAngularVeloc(float frequency);
	float getRadius();
	float getAngularVeloc();
	~RoundMovement();

private:
	Sprite* _refSprite;
	float _radius;				// Bán Kính.
	Vector2 _roundposition;
	float _radianVeloc;			// vận tốc góc (= ω)
	float _radian;				// góc xoay (= φ) biến thiên theo thời gian
};

#endif // !__ICOMPONENT_H__
