// HOW TO USE
/*
Đọc ebook trang 145 để biết cách dùng macro lấy input từ bàn phím
call InputController::getInstance()->init() at Game::init
call InputController::getInstance()->update() at game loop.
if you want to check if key down use:
InputController::getInstance()->isKeydown(int keycode) at game loop or update function of an object
With key down you can hold key to keep action.
if you want to check if key is pressed:
InputController::getInstance()->_keyPress += (EventFunction)&[Insert name of function here];
if you want to check if key is released:
InputController::getInstance()->_keyReleased += (EventFunction)&[Insert name of function here];
if you dont want to refference this function any more, call:
InputController::getInstance()->_keyPress -= (EventFunction)&[Insert name of function here]
InputController::getInstance()->_keyReleased -= (EventFunction)&[Insert name of function here];
The referenced function have prototype:
void <FunctionName>(KeyEventArg* e);
Should call InputController::release() at Game::release()
Example:
void Jump(KeyEventArg* e)
{
if (e == NULL)
return;
switch (e->_keycode)
{
case [Space]:
// I'm jumping....
}
}

InputController::getInstance()->_keyPressed += (EventFunction) &Jump;
And you can press space to make me jump
*/
//EXAMPLE MACRO KEYBOARND
/*
Macro KEYDOWN cung cấp dưới đây trả về TRUE hoặc FALSE dựa trên cơ sở
phím mà bạn đang kiểm tra có được nhấn hay không..
#define KEYDOWN (name, key) { name[key]& 0x80}
sau đây là ví dụ đọc từ bàn phím.
//xác định macro cần kiểm tra trạng thái cảu phím trên bàn phím.
#define KEYDOWN (name, key) { name[key]& 0x80}
Đây là bộ nhớ đệm cần thiết của bàn p hímBeginning DirectX9 Dịch bởi TransTeam diễn đàn Gamedev.VN
146
Char buffer[256];
//đây là vòng lặp chính đọc từ Input Device của mỗi khung
while(1)
{
//kiểm tra bàn phím và xem xét phím nào hiện tại đang được nhấn
g_lpDIDevice->GetDeviceState(sizeof (buffer), (LPVOID )&buffer);
//làm việc gì đó với Input
//KEYDOWN macro ở đay kiểm tra phím mũi tên sang trái có được nhấn hay không
if (KEYDOWN(buffer, DIK_LEFT))
{
//làm gì đó vói mũi tên sang trái
}
// KEYDOWN được sử dụng một lần nữa để kiểm tra phím mũi tên lên trên
//có đựoc nhấn hay không
if(KEYDOWN(buffer, DIK_UP))
{
//làm một việc gì đó với phím mũi tên lên trên
}
}*/

#pragma once
#ifndef __INPUT_CTRL_H__
#define __INPUT_CTRL_H__

#include"define.h"
#include"Graphics.h"
#include"Event.h"
#include<vector>

#define BUTTONDOWN(name, key){name.rgbButtons[key] & 0x80} //Get status of mouse

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

#define KEYBOARD_BUFFER_SIZE  1024

typedef LPDIRECTINPUT          pGInput;
typedef LPDIRECTINPUTDEVICE8   pGKeyboard;

typedef void(*KeyEvent)(int);
class KeyEventArg :public EventArg
{
public:
	KeyEventArg(int keycode) { _key = keycode; }
	int _key;
};

class InputController
{
public:	
	~InputController();

	static InputController* getInstance();
	static void             Release();

	bool	InIt(Graphics*);                
	void	Update();
	int		isKeyDown(int keycode);             //Check if keycode is down
	bool	isKeyPressed(int keycode);
	bool	isKeyRelease(int keycode);

	Event _keyPressed;
	Event _keyReleased;

	//Dùng marco __event thì có thể trỏ được 
	//đến các hàm thành viên của các lớp. 
	//Nhưng cách sử dụng phức tạp hơn
	__event void __eventkeyPressed(KeyEventArg* e);
	__event void __eventkeyReleased(KeyEventArg* e);


private:
	static InputController* _instance;

	pGInput				_input;							 // Direct Input, các key nhấn ...
	pGKeyboard			_keyboard;						 //Thiết bị input
	BYTE				_keyBuffer[MAX_KEYS];			 //BYTE = unsigned char
	HWND				_hWnd;
	DIDEVICEOBJECTDATA  _keyEvents[KEYBOARD_BUFFER_SIZE];

	bool			    _previousKeyBuffer[MAX_KEYS];

	InputController();
};
typedef InputController *pInputController;

GAME_FRAMEWORK_END

#endif // !__INPUT_CTRL_H_
