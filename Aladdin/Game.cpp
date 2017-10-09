#include "Game.h"

USEGAME_FRAMEWORK
using namespace std;

bool Game::isExit = false;
Graphics* Game::_graphics = NULL;


//Sẽ phát triển thay vì dùng này
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE	1024

void Game::Exit()
{
	isExit = 1;
}

Graphics * Game::getWindow()
{
	return _graphics;
}



void Game::InIt()
{
	if (this->_graphics==NULL)
		//MessageBox(NULL, TEXT("hWnd requires error "),"Error Aladdin",);
		throw;
	_graphics->InItWindow();
	_gameTime->InIt();
	_deviceManager->Init(_graphics);
	_input->InIt(_graphics);
	this->_frameRate = 1000.0f / _graphics->getFrameRate();

	D3DXCreateSprite(_deviceManager->getDevice(), &this->_spriteHandler);
	//this->LoadResource();

	_oldTime = _gameTime->getTotalGameTime();
	_deltaTime = 0.0f;
}


Game::Game(HINSTANCE hInstance, 
	LPCSTR name,
	int width,
	int height,
	int fps,
	int isFullScreen)
{
	_graphics = new Graphics(hInstance, name, width, height, fps, isFullScreen);
	_gameTime = GameTime::getInstance(); 
	_deviceManager = DeviceManager::getInstance();
	_input = InputController::getInstance();
	_spriteHandler = NULL;
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
	if (_gameTime != nullptr)
		_gameTime->Release();
	if (_deviceManager != NULL)
		_deviceManager->Release();
	if (_graphics != NULL)
		delete _graphics;
	_graphics = NULL;
	//Chua xoa cua so hwnd, name and sth
}

void Game::UpdateInput(float deltatime)
{
	//Chưa code
}

void Game::Update(float deltatime)
{
	//Chưa code
}

void Game::Draw()
{
	//Chưa code
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
		_gameTime->UpdateGameTime();							// gametime isn't run if dont call updateGameTime
		_deltaTime = _gameTime->getTotalGameTime() - _oldTime;

		if (_deltaTime >= _frameRate)
		{
			_oldTime += _frameRate;
			//input->update();
			//this->render();

            #pragma region Code test man hinh
			/*if (_deviceManager->getDevice()->BeginScene())
			{
			this->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
			_deviceManager->getDevice()->ColorFill(
			_deviceManager->getSurface(),
			NULL,
			D3DCOLOR_XRGB((int)_deltaTime, (int)_deltaTime, 0));
			this->_spriteHandler->End();
			_deviceManager->getDevice()->EndScene();
			}
			_deviceManager->getDevice()->Present(NULL, NULL, NULL, NULL);*/
            #pragma endregion
		}
		else
			Sleep(_frameRate - _deltaTime);						//sleep every frame for high performance		
	}

}

//Draw after updated
void Game::Render()
{
	//Kiểm tra nếu cửa sổ đang focus không phải game thì không cập nhật
	if (GetActiveWindow() != _graphics->getHwnd())
	   return;
	auto device = _deviceManager->getInstance();
	float time = _gameTime->getElapsedGameTime();   //Thời gian 1 vòng lặp

	//xử lí không dồn frame
	//thời gian vòng lặp cao hơn dự tính thì set
	//cứng nó bằng fps để không đồn frame
	if (time > this->_frameRate * 2)
		time = _frameRate;

	if (device->getDevice()->BeginScene() != DI_OK)
		return;

	device->ClearScreen();
	UpdateInput(time);
	Update(time);
	Draw();

	device->getDevice()->EndScene();
	device->Present();
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
