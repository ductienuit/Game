#include "DeviceManager.h"
USEGAME_FRAMEWORK

DeviceManager* DeviceManager::_instance = nullptr;

DeviceManager::DeviceManager(void)
{
	_direct		  = NULL;
	_directDevice = NULL;
	_surface	  = NULL;
}

bool DeviceManager::Init(pGraphics window)
{
	_direct = Direct3DCreate9(D3D_SDK_VERSION);
	if (_direct == NULL)
	{
		MessageBox(NULL, TEXT("Device direct can't create"), "Aladdin", MB_ICONERROR);
		return false;
	}
	D3DPRESENT_PARAMETERS	d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = window->getIsFullScreen() ? FALSE : TRUE;
	d3dpp.hDeviceWindow = window->getHwnd();

	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = window->getWindowHeight();
	d3dpp.BackBufferWidth = window->getWindowWidth();

	_direct->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window->getHwnd(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&_directDevice);

	if (_directDevice == NULL)
		MessageBox(NULL, TEXT("The directdevice requires error"), "Aladdin", MB_ICONERROR);

	//Initilize Surface
	_directDevice->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &_surface);

}

DeviceManager* DeviceManager::getInstance()
{
	if (_instance == NULL)
		_instance = new DeviceManager();
	return _instance;
}

DeviceManager::~DeviceManager(void)
{
	if (_direct != NULL)
		_direct->Release();
	if (_directDevice != NULL)
		_directDevice->Release();
	if (_surface != NULL)
		_surface->Release();
}

void DeviceManager::Release()
{
	delete _instance;
	_instance = NULL;
}

void DeviceManager::Present()
{
	this->_directDevice->Present(0, 0, 0, 0);
}


void DeviceManager::ClearScreen()
{
	this->_directDevice->ColorFill(_surface, NULL, D3DCOLOR_XRGB(0, 0, 0));
}

LPDIRECT3DDEVICE9 DeviceManager::getDevice()
{
	return _directDevice;
}

LPDIRECT3DSURFACE9 DeviceManager::getSurface()
{
	return _surface;
}
