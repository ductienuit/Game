#include "Game.h"


bool Game::isExit = false;

void Game::Exit()
{
}

void Game::Init()
{
	this->InitWindows();
	this->InitDevice();
	this->LoadResource();

	gameTime->init();
}


Game::Game(HINSTANCE hInstance, 
	LPCSTR name,
	int width,
	int height,
	int fps,
	int isFullScreen)
{
	Engine::SethInstance(hInstance);
	Engine::SetWindowWidth(width);
	Engine::SetWindowHeight(height);
	Engine::SetGameName(name);
	Engine::SetFrameRate(fps);

	gameTime = GameTime::getInstance();
}

void Game::Release()
{
	if (Engine::GetDirect() != NULL)
		Engine::GetDirect()->Release();
	if (Engine::GetDirectDevice() != NULL)
		Engine::GetDirectDevice()->Release();
	if (Engine::GetBackBuffer() != NULL)
		Engine::GetBackBuffer()->Release();
	if (Engine::GetSpriteHandler() != NULL)
		Engine::GetSpriteHandler()->Release();
	if (gameTime != nullptr)
		gameTime->release();
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
		gameTime->updateGameTime();							// gametime isn't run if dont call updateGameTime
		deltaTime = gameTime->getTotalGameTime() - oldTime;

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
//Khởi tạo cửa sổ
bool Game::InitWindows()
{
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX); // hàm sizeof() trả về kích thước của một đối
										  //tượng kiểu dữ liệu đầu vào – đơn vị tính là byte
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // xác lập kiểu lớp
	wndClass.lpfnWndProc = Game::WndProc; // xác lập tên hàm gọi lại callback procedure
	wndClass.cbClsExtra = 0; // xác lập số byte cấp phát thêm cho Class
	wndClass.cbWndExtra = 0; // xác lập số byte cấp phát thêm cho mỗi instance của Class
	wndClass.hInstance = Engine::GethInstance(); // con trỏ (handle) trỏ tới instance của ứng dụng
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);; //loại biểu tượng chương trình
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);// xác lập kiểu con trỏ chuột mặc định
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // màu nền của cửa sổ
	wndClass.lpszMenuName = NULL; // con trỏ trỏ tới object dữ liệu thực đơn ứng dụng
	wndClass.lpszClassName = Engine::GetGameName(); // tên lớp đăng ký với hệ thống
	wndClass.hIconSm = 0; // con trỏ tới dữ liệu biểu tượng cửa sổ ứng dụng
	if (!RegisterClassEx(&wndClass)) //gọi hàm đăng ký lớp với hệ thống
	{
		MessageBox(NULL, TEXT("The wndclass requires error"), "Aladdin", MB_ICONERROR);
		return false;
	}
	Engine::SetHwnd(CreateWindow(
		Engine::GetGameName(), //Tên lớp đã khai báo và đăng ký
		"Aladdin",
		WS_OVERLAPPEDWINDOW,//Loại cửa số
		CW_USEDEFAULT, // Tọa độ X cửa số trên màn hình
		CW_USEDEFAULT,//Tọa độ Y
		Engine::GetWindowWidth(),
		Engine::GetWindowHeight(),
		NULL, //NULL là không sử dụng
		NULL,
		Engine::GethInstance(),
		NULL));
	if (!Engine::GetHwnd())
	{
		MessageBox(Engine::GetHwnd(), TEXT("Create window error"), "Aladdin", MB_ICONERROR);
		return false;
	}
	ShowWindow(Engine::GetHwnd(), SW_SHOW);
	UpdateWindow(Engine::GetHwnd());
	return true;
}
/*Khởi tạo các giá trị trong Engine
Khởi tạo môi trường vẽ  Engine::SetDirect(Direct3DCreate9(D3D_SDK_VERSION));
Khởi tạo thiết bị để vẽ (CreateDevice)
Khởi tạo surface
Khởi tạo sprite vẽ lên surface
*/
bool Game::InitDevice()
{


	Engine::SetDirect(Direct3DCreate9(D3D_SDK_VERSION));
	if (Engine::GetDirect() == NULL)
	{
		MessageBox(Engine::GetHwnd(), TEXT("Device direct can't create"), "Aladdin", MB_ICONERROR);
		return false;
	}
	D3DPRESENT_PARAMETERS d3dpp; //Tham số điều khiển khung hiển thị
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;;

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = Engine::GetWindowHeight();
	d3dpp.BackBufferWidth = Engine::GetWindowWidth();

	d3dpp.hDeviceWindow = Engine::GetHwnd();

	LPDIRECT3DDEVICE9 deviceDirect;

	if (FAILED(Engine::GetDirect()->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		Engine::GetHwnd(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&deviceDirect)))
	{
		MessageBox(NULL, "Can't create Direct Device", "Error", MB_OK | MB_ERR_INVALID_CHARS);
		return false;
	}

	Engine::SetDirectDevice(deviceDirect);

	//Surface
	LPDIRECT3DSURFACE9 backbuffer;

	Engine::GetDirectDevice()->GetBackBuffer(0, // giá trị thể hiện kiểu cháo đổi
		0, // chỉ số của bộ đệm
		   // 0 nếu chỉ có một bộ đệm được sử dụng
		D3DBACKBUFFER_TYPE_MONO, // một đối số định kiểu
		&backbuffer); // đối tượng trả về có kiểu IDirect3DSurface9

	Engine::SetBackBuffer(backbuffer);

	//Sprite

	LPD3DXSPRITE sprite;

	if (D3DXCreateSprite(Engine::GetDirectDevice(), &sprite) != D3D_OK)
	{
		MessageBox(NULL, "Can't create sprite in hwnd", "Error", MB_OK | MB_ERR_INVALID_CHARS);
		return false;
	}

	Engine::SetSpriteHandler(sprite);

	return true;
}

bool Game::LoadResource()
{
	return true;
}

//Hàm bắt sự kiện
//Sẽ mở rộng
LRESULT CALLBACK Game::WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	// Kiểm tra xem có thông điệp nào được gửi tới hàng đợi cửa ứng dụng không
	switch (message) //lọc các thông điệp
	{
	case WM_CREATE:
		return 0;
	case WM_DESTROY: //bắt thông điệp yêu cầu kết thúc ứng dụng
		PostQuitMessage(0); //gọi hàm xử lý
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
