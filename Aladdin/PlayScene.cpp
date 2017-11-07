#include "PlayScene.h"

#if _DEBUG
#include <time.h>
#endif

PlayScene::PlayScene()
{
	_viewport = new Viewport(0, WINDOWS_HEIGHT, WINDOWS_WIDTH, WINDOWS_HEIGHT);
}


PlayScene::~PlayScene()
{
	delete _viewport;
	_viewport = nullptr;
}

void PlayScene::setViewport(Viewport * viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

bool PlayScene::InIt()
{
	auto aladdin = new Aladdin();
	return true;
}

void PlayScene::UpdateInput(float dt)
{

}


