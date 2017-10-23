/*
HOW TO USE
the Texture is used in Sprite and SpriteManager.
you dont have to use Texture manually, just use Sprite or SpriteManager.
IMPORTANT:
if Texture instance is deleted by destructor, LPDIRECT3DTEXTURE9 is kept in memory => LEAK MEMORY
call release before delete to avoid LEAK
*/
#ifndef __texture_H__
#define __texture_H__

#include "define.h"
#include "DeviceManager.h"
#include"ViewPort.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

class Texture
{
public:
	Texture(void);
	~Texture(void);

	// release the image from memory
	void Release();

	/*
	load image from file and store in LPDIRECT3DTEXTURE9
	@spriteHandle: sprite handle managed by directX, it work for load content.
	@filePath: the path of file
	@color: back color
	*/
	HRESULT LoadFromFile(LPD3DXSPRITE spriteHandle, LPCSTR filePath, D3DXCOLOR color = C_WHITE, D3DXCOLOR colorkey = COLOR_KEY);

	/*
	draw LPDIRECT3DTEXTURE9 to screen, directX manage draw to buffer, we dont care about buffer anymore.
	@spriteHandle: sprite handle managed by directX, it work for load content.
	@rect: a part of image want to draw, remmember RECT is defined: {top, left, right, bot} (4 lines)
	@center: a center of frame to draw:
	- if you chose NULL, topleft of image will be drawn at @position
	- if you chose x,y of frame, topleft of image will be drawn at @position - (x ,y)
	@postion: position to draw
	*/
	void Render(LPD3DXSPRITE spriteHandle, const RECT* rect, const Vector3* center, const Vector3* position);

	/*
	render texture với các tham số tranform, gốc tọa độ top-left
	@position: vị trí
	@scale:
	@rotate: góc xoay theo số độ (0-360)
	@origin: điểm neo để transform
	@zIndex: độ sâu
	*/
	void Render(LPD3DXSPRITE spriteHandle, RECT* srcRect, Vector2 position, Vector2 scale, float rotate, Vector2 origin, float zIndex = 0);

	/*
	render texture với các tham số tranform, trong viewport
	@viewport:
	@position: vị trí
	@scale:
	@rotate: góc xoay theo số độ (0-360)
	@origin: điểm neo để transform
	@zIndex: độ sâu
	*/
	void Render(LPD3DXSPRITE spriteHandle, RECT* srcRect, Viewport viewport, Vector2 position, Vector2 scale, float rotate, Vector2 origin, float zIndex = 0);

	void setColor(D3DXCOLOR);
	D3DXCOLOR getColor();

	// get width of image
	int getWidth();
	//get height of image
	int getHeight();
private:
	LPDIRECT3DTEXTURE9	_texture;		// contain the image laoded from file
	D3DXIMAGE_INFO		_imageInfo;		// contain info such as width, height, extention of file...

	D3DXCOLOR			_color;			// usually, image file have back color, it is ignore when draw. We use WHITE
};

typedef Texture* pTexture;

GAME_FRAMEWORK_END

#endif // !__texture_H__

