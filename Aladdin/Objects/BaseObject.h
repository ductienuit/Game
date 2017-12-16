#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__
#include"../FrameWork/define.h"
#include"../FrameWork/Manager/SpriteManager.h"
#include"../FrameWork/Sprite.h"
#include"../FrameWork/ViewPort.h"
#include"../FrameWork/InputController.h"

USEGAME_FRAMEWORK
class IControlable
{
public:
	IControlable();
	virtual void UpdateInput(float deltatime) = 0;
protected:
	InputController* _input;
};

class BaseObject
{
public:
	BaseObject();
	BaseObject(eID id);
	virtual ~BaseObject();

	virtual void InIt() = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Draw(LPD3DXSPRITE, ViewPort*) = 0;
	virtual void Release() = 0;

	virtual eID	 getId();
	eStatus		 getStatus();
	virtual void setStatus(eStatus status);
	virtual void addStatus(eStatus status);
	virtual void removeStatus(eStatus status);
	virtual bool isInStatus(eStatus status);
	virtual void clearStatus();
	virtual void savePreStatus();

	virtual Vector2 getPosition();
	virtual float   getPositionX();
	virtual float   getPositionY();

	virtual void setPosition(Vector3 vector);
	virtual void setPosition(Vector2 position);
	virtual void setPosition(float x, float y, float z);
	virtual void setPosition(float x, float y);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

	virtual Vector2 getScale();
	virtual void setScale(Vector2 scale);
	virtual void setScale(float scale);
	virtual void setScaleX(float sx);
	virtual void setScaleY(float sy);

	virtual float getRotate();
	virtual void  setRotate(float degree);

	virtual Vector2 getOrigin();
	virtual void    setOrigin(Vector2 origin);

	virtual void    setZIndex(float z);
	virtual float	getZIndex();

	virtual void	setOpacity(float opacity);
	virtual float	getOpacity();

	virtual void	  setColor(D3DXCOLOR color);
	virtual D3DXCOLOR getColor();

	virtual void	setCanUp(bool);

	virtual Vector2	  getAnchorPoint();

	Sprite*		 getSprite();

	virtual RECT getBounding();

	virtual float checkCollision(BaseObject* object, float dt);
	virtual float checkCollision(BaseObject* object, eDirection& direction);

	// vật nào cũng có vận tốc, mặc định là đứng yên sẽ return 0
	// nếu vật có chuyển động phải override lại để lấy vận tốc.
	virtual Vector2		getVelocity();
	virtual void		Stop();

	virtual void		setPhysicsBodySide(eDirection side);
	virtual eDirection  getPhysicsBodySide();
	virtual void		ShowBB();
	virtual void		StopUp();
	virtual int			getIndex(); //Index of Animations
protected:
	Sprite*		_sprite;
	// nếu muốn dùng animation thì class kế thừa khai báo animation
	// khởi tạo animation thì reference đến sprite
	eID			_id;
	eStatus		_status;
	eStatus		_preStatus;
	eDirection	_physicsSide;
	//FLAG
	bool		_canUp;
};
#endif __BASEOBJECT_H__

