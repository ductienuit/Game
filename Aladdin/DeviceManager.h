
#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#include "define.h"
#include "Graphics.h"

GAME_FRAMEWORK
GAME_FRAMEWORK_BEGIN

//Device and surface
class DeviceManager
{
public:

	~DeviceManager(void);
	static DeviceManager*    getInstance();
	static void				 Release();
	void					 ClearScreen();
	void					 Present();
	//Initilize direct device and surface
	bool				     Init(pGraphics);  

	LPDIRECT3DDEVICE9		 getDevice();
	LPDIRECT3DSURFACE9		 getSurface();

private:
	static DeviceManager*   _instance;
	LPDIRECT3D9			    _direct;
	LPDIRECT3DDEVICE9	    _directDevice;
	LPDIRECT3DSURFACE9	    _surface;
	DeviceManager(void);
};
typedef DeviceManager *pDeviceManager;
GAME_FRAMEWORK_END

#endif // !__DEVICE_MANAGER_H__
