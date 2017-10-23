#ifndef __TRANSFORMABLE_H__
#define __TRANSFORMABLE_H__

#include "define.h"

/*Quản lí vị trí, góc xoay, độ phóng to, vị trí hiện tại, điểm neo sprite*/
class Transformable
{
public:
	Transformable();
	~Transformable();

	virtual Vector2 getPosition();
	virtual float   getPositionX();
	virtual float   getPositionY();

	virtual void	setPosition(Vector3 vector);
	virtual void	setPosition(float x, float y, float z);
	virtual void	setPosition(Vector2 position);
	virtual void	setPosition(float x, float y);
	virtual void	setPositionX(float x);
	virtual void	setPositionY(float y);

	virtual Vector2 getScale();
	virtual void    setScale(Vector2 scale);
	virtual void    setScale(float scale);
	virtual void    setScaleX(float sx);
	virtual void    setScaleY(float sy);

	virtual float   getRotate();
	virtual void    setRotate(float degree);

	virtual Vector2 getOrigin();
	virtual void    setOrigin(Vector2 origin);

	virtual void    setZIndex(float z);
	virtual float   getZIndex();

	Vector2			getAnchorPoint();

protected:
	Vector2			_position;				// Vị trí của sprite,gốc là hình chỉnh giữa  Texture
	Vector2			_scale;					// Độ phóng đại theo chiều dài và rộng
	float			_rotate;				// Góc quay theo độ 0-360
	Vector2			_origin;				// Điểm gốc của Transform, dùng để xoay, scale (anchor: điểm neo)
	Vector2			_anchorPoint;			// Tâm sprite
	float			_zIndex;
};

#endif // !__TRANSFORMABLE_H__
