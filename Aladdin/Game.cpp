#include "Game.h"

USEGAME_FRAMEWORK
using namespace std;

bool Game::isExit = false;

//Sẽ phát triển thay vì dùng này
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE	1024

void Game::Exit()
{
}

void Game::InIt()
{
	//this->InitWindows();
	graphics->InItWindow();
	gameTime->InIt();
	deviceManager->Init(graphics);

	//this->InitDevice();
	this->LoadResource();

	gameTime->InIt();
}


Game::Game(HINSTANCE hInstance, 
	LPCSTR name,
	int width,
	int height,
	int fps,
	int isFullScreen)
{
	//Engine::SethInstance(hInstance);
	//Engine::SetWindowWidth(width);
	//Engine::SetWindowHeight(height);
	//Engine::SetGameName(name);
	//Engine::SetFrameRate(fps);
	graphics = new Graphics(hInstance, name, width, height, fps, isFullScreen);
	deviceManager = DeviceManager::getInstance();
	gameTime = GameTime::getInstance();
	spriteHandle = NULL;
}

void Game::Release()
{
	//if (Engine::GetDirect() != NULL)
	//	Engine::GetDirect()->Release();
	//if (Engine::GetDirectDevice() != NULL)
	//	Engine::GetDirectDevice()->Release();
	//if (Engine::GetBackBuffer() != NULL)
	//	Engine::GetBackBuffer()->Release();
	//if (Engine::GetSpriteHandler() != NULL)
	//	Engine::GetSpriteHandler()->Release();
	if (gameTime != nullptr)
		gameTime->Release();
	if (deviceManager != NULL)
		deviceManager->Release();
	if (graphics != NULL)
		delete graphics;
	graphics = NULL;
	//Chua xoa cua so hwnd, name and sth
}

void Game::Run()
{
	MSG msg;
	while (isExit == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				isExit = true;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		gameTime->UpdateGameTime();							// gametime isn't run if dont call updateGameTime
		deltaTime = gameTime->GetTotalGameTime() - oldTime;

		if (deltaTime >= frameRate)
		{
			oldTime += frameRate;
			//input->update();
			//this->render();

            #pragma region Code test man hinh
			/*if (Engine::GetDirectDevice()->BeginScene())
			{
			Engine::GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
			Engine::GetDirectDevice()->ColorFill(
			Engine::GetBackBuffer(),
			NULL,
			D3DCOLOR_XRGB((int)deltaTime, 0, 0));
			Engine::GetSpriteHandler()->End();
			Engine::GetDirectDevice()->EndScene();
			}
			Engine::GetDirectDevice()->Present(NULL, NULL, NULL, NULL);*/
            #pragma endregion
		}
		else
			Sleep(frameRate - deltaTime);						//sleep every frame for high performance		
	}

}

/*Khởi tạo các giá trị trong Engine
Khởi tạo môi trường vẽ  Engine::SetDirect(Direct3DCreate9(D3D_SDK_VERSION));
Khởi tạo thiết bị để vẽ (CreateDevice)
Khởi tạo surface
Khởi tạo sprite vẽ lên surface
*/
//bool Game::InitDevice()
//{
//	////Sprite
//
//	//LPD3DXSPRITE sprite;
//
//	//if (D3DXCreateSprite(Engine::GetDirectDevice(), &sprite) != D3D_OK)
//	//{
//	//	MessageBox(NULL, "Can't create sprite in hwnd", "Error", MB_OK | MB_ERR_INVALID_CHARS);
//	//	return false;
//	//}
//	//Engine::SetSpriteHandler(sprite);
//
//	//return true;
//}

bool Game::LoadResource()
{
	return true;
}
