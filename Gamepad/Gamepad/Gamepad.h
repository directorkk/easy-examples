#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_


#include <wbemidl.h>
#include <oleauto.h>

#include <wchar.h>

#ifndef INITGUID
#define INITGUID 

#include <Windows.h>
#include <dinput.h>
#include <dinputd.h>
#pragma comment(lib, "dinput8.lib")

#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")
#endif

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=nullptr; } }

#include "GamepadState.h"

#include <vector>

struct GamepadDevice{
	int XinputID;	// -1 for directinput device

	GUID Product, Instance;

	LPDIRECTINPUTDEVICE8 DI8Device;

	GamepadDevice(){
		XinputID = -1;
	}
};


class Gamepad{
public:
	Gamepad();
	~Gamepad();

	BOOL CALLBACK EnumJoysticksCallback(LPCDIDEVICEINSTANCE lpddi,VOID *pvRef);
	HRESULT CheckDevice();

	GamepadState GetState(unsigned int index = 0);
	GamepadDevice GetDevice(unsigned int index);	// Use Product and Instance to bind player

	unsigned int GetDeviceCount();

private:
	BOOL IsXInputDevice(const GUID* pGuidProductFromDirectInput);
	int GetUserIndex();

	bool IsDeviceExisted(const GUID _product, const GUID _instance);

private:
	int m_PlayerIndex;

	LPDIRECTINPUT8 m_DI8Object;
	std::vector<GamepadDevice> m_GamepadDevice;
};

#endif