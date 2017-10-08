#include"define.h"
#include"Graphics.h"
USEGAME_FRAMEWORK

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}


Graphics::Graphics(HINSTANCE hInstance, LPCSTR wcName, int width, int height, int fps, int isFullScreen)
{

	this->_hInstance = hInstance;
	this->_gameName = wcName;

	this->_isFullScreen = isFullScreen;

	this->_windowWidth = width;
	this->_windowHeight = height;
	this->_fps = fps;
}

bool Graphics::InItWindow()
{
	/* --- Init Window class extra --- */
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX); // hàm sizeof() trả về kích thước của một đối
										  //tượng kiểu dữ liệu đầu vào – đơn vị tính là byte
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // xác lập kiểu lớp
	wndClass.lpfnWndProc = this->WinProc; // xác lập tên hàm gọi lại callback procedure
	wndClass.cbClsExtra = 0; // xác lập số byte cấp phát thêm cho Class
	wndClass.cbWndExtra = 0; // xác lập số byte cấp phát thêm cho mỗi instance của Class
	wndClass.hInstance = this->gethInstance(); // con trỏ (handle) trỏ tới instance của ứng dụng
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);; //loại biểu tượng chương trình
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);// xác lập kiểu con trỏ chuột mặc định
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // màu nền của cửa sổ
	wndClass.lpszMenuName = NULL; // con trỏ trỏ tới object dữ liệu thực đơn ứng dụng
	wndClass.lpszClassName = _gameName; // tên lớp đăng ký với hệ thống
	wndClass.hIconSm = 0; // con trỏ tới dữ liệu biểu tượng cửa sổ ứng dụng
	if (!RegisterClassEx(&wndClass)) //gọi hàm đăng ký lớp với hệ thống
	{
		MessageBox(NULL, TEXT("The wndclass requires error"), "Aladdin", MB_ICONERROR);
		return false;
	}

	/* --- Init window --- */
	DWORD style;
	if (this->_isFullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;
	this->_hWnd = CreateWindow(
		this->_gameName, //Tên lớp đã khai báo và đăng ký
		this->_gameName,
		style,//Loại cửa số
		CW_USEDEFAULT, // Tọa độ X cửa số trên màn hình
		CW_USEDEFAULT,//Tọa độ Y
		this->getWindowWidth(),
		this->getWindowHeight(),
		NULL, //NULL là không sử dụng
		NULL,
		this->gethInstance(),
		NULL);
		if (!this->getHwnd())
		{
			MessageBox(NULL, TEXT("Create window error"), "Aladdin", MB_ICONERROR);
			return false;
		}
		ShowWindow(this->getHwnd(), SW_SHOWNORMAL);
		UpdateWindow(this->getHwnd());
		return true;
}


LRESULT CALLBACK Graphics::WinProc(HWND hWnd, UINT message,
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


int Graphics::getIsFullScreen() {
	return _isFullScreen;
}

int Graphics::getWindowWidth() {
	return _windowWidth;
}

int Graphics::getWindowHeight() {
	return _windowHeight;
}

int Graphics::getFrameRate() {
	return _fps;
}

HWND Graphics::getHwnd()
{
	return _hWnd;
}

HINSTANCE Graphics::gethInstance()
{
	return this->_hInstance;
}