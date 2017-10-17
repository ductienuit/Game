#include "Game.h"
#if _DEBUG
#include "debug.h"	// for print to output. call: __debugoutput()
#endif // _DEBUG
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
	_input->InIt(_graphics->getHwnd(),_graphics->gethInstance());
	this->_frameRate = 1000.0f / _graphics->getFrameRate();

	D3DXCreateSprite(_deviceManager->getDevice(), &this->_spriteHandler);
	this->LoadResource();

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
	if (_gameTime != nullptr)
		_gameTime->Release();
	if (_deviceManager != NULL)
		_deviceManager->Release();
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
			_input->Update();
			this->Render();

            #pragma region Code test man hinh
		/*	if (_deviceManager->getDevice()->BeginScene())
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

	//Main game, nơi mọi tác động đến game được xử lí
	UpdateInput(time);
	Update(time);
	Draw();

	device->getDevice()->EndScene();
	device->Present();
}

void Game::UpdateInput(float deltatime)
{
	//Chưa code, override 
}

void Game::Update(float deltatime)
{
	//Chưa code
}

void Game::Draw()
{
	//Chưa code, override
}

bool Game::LoadResource()
{
	//override
	return true;
}