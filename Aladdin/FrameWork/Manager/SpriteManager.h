#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include<map>
#include<fstream>

#include"../define.h"
#include"../Sprite.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN
class SpriteManager
{
public:
	static SpriteManager* getInstance();
	static void Release();

	void LoadResource(LPD3DXSPRITE spriteHandle);
	Sprite* getSprite(eID id);

	RECT getSourceRect(eID id, string name);
	void LoadSpriteInfo(eID id, const char* fileInfoPath);

	//Release Sprite, dont release Texture, keep Texture to yse in another Sprite
	void ReleaseSprite(eID id);

	//Release Texture, spritem 
	//cẩn thận khi dùng hàm này, nhiều sprite có thể tham chiếu đến cùng một texture
	//Nếu release texture mà vẫn còn thể hiện nào đó tha chiếu đến thì sẽ bị lỗi
	void ReleaseTexture(eID id);

	~SpriteManager();

private:
	SpriteManager(void);
	static SpriteManager* _instance;
	map<eID, Sprite*> _listSprite;
	map<eID, map<string, RECT>> _sourceRectList;

};
GAME_FRAMEWORK_END



#endif // !__SPRITEMANAGER_H__
