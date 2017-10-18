#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <list>
#include "define.h"
#include "DeviceManager.h"
#include "Texture.h"
#include "Transformable.h"
//#include "Viewport.h"



using namespace std;

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

class Sprite : public Transformable
{
public:
	/*
	@filePath: đường dẫn hình ảnh
	@totalFrames: số frame ảnh trên một file
	@cols: số frame trên một cột
	Nếu không truyền số frame, số cột (= 1) sẽ vẽ hết hình. Để vẽ một vị trí cụ thể trên hình thì dùng setFrameRect().
	*/
	Sprite(LPD3DXSPRITE spriteHandle, LPCSTR filePath, int totalFrames = 1, int cols = 1);

	~Sprite();

	/*
	Hủy các biến
	*/
	void Release();

	/*
	vẽ hình
	*/
	void Render(LPD3DXSPRITE spriteHandle);

	void setPosition(float x, float y, float z = 1);
	void setPosition(Vector3 vector);
	void setPosition(Vector2 position);
	void setPositionX(float x);
	void setPositionY(float y);

	void setScale(Vector2 scale);
	void setScale(float scale);
	void setScaleX(float sx);
	void setScaleY(float sy);

	void setRotate(float degree);

	void setOrigin(Vector2 origin);

	void setZIndex(float z);

	RECT getBounding();

	void setFrameRect(RECT rect);
	void setFrameRect(float top, float right, float bottom, float left);
	void setFrameRect(float x, float y, int width, int height);
	RECT getFrameRect();
	RECT getFrameRectByIndex(int index);
	/*
	Chuyển qua frame kế tiếp
	*/
	void nextFrame();

	/*
	Truyền thứ tự frame cụ thể
	*/
	void setIndex(int index);

	/*
	Lấy chiều ngang của frame
	*/
	int getFrameWidth();

	/*
	Lấy chiều dọc của frame
	*/
	int getFrameHeight();

	/*
	Lấy chiều ngang của nguyên tấm hình
	*/
	int getTextureWidth();

	/*
	Lấy chiều dọc của nguyên tấm texture
	*/
	int		getTextureHeight();

	void	drawBounding(bool draw);

	void	setOpacity(float opacity);
	float	getOpacity();

	/*
	Màu vẽ sprite
	*/
	void		setColor(D3DXCOLOR color);
	D3DXCOLOR   getColor();

private:
	Texture				_texture;
	float				_opacity;						// Độ mờ khi bị thương, từ 0.0f đến 1.0f thôi
	D3DXCOLOR			_color;							// Màu ảnh, set cứng 255 255 255

	RECT				_bound;							// Vùng vẽ trong texture, source rect

	int					_totalFrames;					// tổng số frame
	int					_columns;						// số cột
	int					_index;
	Vector2				_currentFrame;					// frame hiện tại

	RECT				_frameRect;
	int					_frameWidth;
	int					_frameHeight;
	int					_textureWidth;
	int					_textureHeight;

	void				setFrameRect();
	void				setCurrentFrame();
	void				UpdateBounding();                

	Vector2				RotatePointAroundOrigin(Vector2 point, float angle, Vector2 origin);

	//surface để vẽ bounding
	LPDIRECT3DSURFACE9	_surface;
	bool				_isDrawBounding;
};

GAME_FRAMEWORK_END

#endif // !__SPRITE_H__
