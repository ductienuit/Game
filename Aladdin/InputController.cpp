#include "InputController.h"
USEGAME_FRAMEWORK

InputController* InputController::_instance = nullptr;

InputController::InputController()
{
	_input = NULL;
	_keyboard = NULL;
	ZeroMemory(_keyBuffer, MAX_KEYS);
}


InputController::~InputController()
{
	if (_input != NULL)
		this->_input->Release();
	if (_keyboard != NULL)
		this->_keyboard->Release();
}

InputController * InputController::getInstance()
{
	if (_instance == nullptr)
		_instance = new InputController();
	return _instance;
}

void InputController::Release()
{
	delete _instance;
	_instance = nullptr;
}

bool InputController::InIt(HWND hwnd, HINSTANCE hInstance)
{
	this->_hWnd =hwnd;
	HRESULT directInput;
	//Init DirectInput
	directInput = DirectInput8Create(
		hInstance,							 //Trường hợp ứng dụng tạo DirectInput object
		DIRECTINPUT_VERSION,				 //Số phiên bản DirectInput
		IID_IDirectInput8,					 //Định dạng giao diện cần thiết, cho giá trị mặc định luôn
		(void**)&_input,					 //Con trỏ chứa directinput được tạo
		NULL);								 //không quan tâm - chí dân

	if (directInput != DI_OK)
		return false;

	//directInput = _input->CreateDevice(GUID_SysKeyboard, (LPDIRECTINPUTDEVICEW*)&_keyboard, NULL);
	directInput = _input->CreateDevice(GUID_SysKeyboard, (LPDIRECTINPUTDEVICEA*)&_keyboard, NULL); //tạo thết bị dựa trên bàn phím
	if (directInput != DI_OK)
		return false;

	directInput = _keyboard->SetDataFormat(&c_dfDIKeyboard);    //Thiết lập định dạng dữ liệu lấy được
	if (directInput != DI_OK)
		return false;

	//Cài đặt truy cập	độc quyền hoặc truy cập không độc quyền.
	directInput = _keyboard->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);//
	if (directInput != DI_OK)
		return false;

	//---- Set Property for keyboard buffer  ----

	//Thông số cả keyboard buffer
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.diph.dwObj = 0;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	//thiết lập phạm vi cho trục(ebook ghi dậy)
	directInput = _keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (directInput != DI_OK)
		return false;

	//Xác nhận chương trình đã sẵn sàn nhận lệnh từ bàn phím
	directInput = _keyboard->Acquire();
	if (directInput != DI_OK)
		return false;
	return true;
}

void InputController::Update()
{
	for(int i=0;i<MAX_KEYS;i++)
	{
		_previousKeyBuffer[i] = ((_keyBuffer[i] & 0x80) > 0);      //Kiểm tra 256 ký tự, cái nào được nhấn.
	}

	//Lấy trạng thái của toàn bộ các keys
	_keyboard->GetDeviceState(sizeof(this->_keyBuffer), _keyBuffer);
	if (isKeyDown(DIK_ESCAPE)) //ESC pressed -> Quit game
	{
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	DWORD dw = KEYBOARD_BUFFER_SIZE; 
	HRESULT directInput = _keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _keyEvents, &dw, 0);

	int keycode, keystate;
	for (DWORD i = 0; i < dw; i++)
	{
		keycode = _keyEvents[i].dwOfs;
		keystate = _keyEvents[i].dwData;

		if ((keystate & 0x80) > 0)
		{
			KeyEventArg* arg = new KeyEventArg(keycode);
			_keyPressed.fireEvent(arg);
			__raise __eventkeyPressed(arg);
			delete arg;
		}
		else
		{
			KeyEventArg* arg = new KeyEventArg(keycode);
			_keyReleased.fireEvent(arg);
			__raise __eventkeyReleased(arg);
			delete arg;
		}
	}
}

int InputController::isKeyDown(int keycode)
{
	return ((_keyBuffer[keycode] & 0x80) > 0);
}

bool InputController::isKeyPressed(int keycode)
{
	//Chưa thử.
	return isKeyDown(keycode) && !(_previousKeyBuffer[keycode]);
}

bool InputController::isKeyRelease(int keycode)
{
	return isKeyDown(keycode) && (_previousKeyBuffer[keycode]);
}

