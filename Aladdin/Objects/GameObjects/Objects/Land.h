
#ifndef __LAND_H__
#define __LAND_H__

#include "../../../FrameWork/define.h"
#include "../../BaseObject.h"
#include "../../../FrameWork/IComponent.h"
#include"../../../FrameWork/CollisionBody.h"

class Land : public BaseObject
{
public:
	Land(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type);
	~Land();

	// Các phương thức kế thừa từ BaseObject.
	void InIt() override;
	void Update(float deltatime) override;
	void Draw(LPD3DXSPRITE, Viewport*) override;
	void Release() override;

	Vector2 getPosition() override;
	void setPosition(Vector2 position) override;
	Vector2 getOrigin() override;
	RECT getBounding() override;
	eID getId() override;

	float getPositionX() override;
	float getPositionY() override;
	float getPositionBottom();
	void setPosition(Vector3 vector) override;
	void setPosition(float x, float y, float z) override;
	void setPosition(float x, float y) override;
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	eLandType getType();

	void		ShowBB() override;
protected:


	eLandType _type;
	LPDIRECT3DSURFACE9 _surface;

#pragma region Hide all
	// Đặt những hàm này ở private để giấu chúng đi. Vì lớp này có sprite bằng NULL nên hạn chế những tác động đến sprite.

	void setOrigin(Vector2 origin) override;

	Vector2 getScale() override;
	void setScale(Vector2 scale) override;
	void setScale(float scale) override;
	void setScaleX(float sx) override;
	void setScaleY(float sx) override;

	float getRotate() override;
	void setRotate(float degree) override;
	Vector2 getAnchorPoint() override;

	void setZIndex(float z) override;
	float getZIndex() override;
#pragma endregion
private:
	map<string, IComponent*> _listComponent;

	// Hình chữ nhật bao lấy land.
	RECT _bound;
};


#endif // !__LAND_H__