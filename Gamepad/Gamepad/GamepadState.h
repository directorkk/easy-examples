#ifndef _GAMEPAD_STATE_H_
#define _GAMEPAD_STATE_H_

#ifndef INITGUID
#define INITGUID 

#include <Windows.h>
#include <dinput.h>
#include <dinputd.h>
#pragma comment(lib, "dinput8.lib")

#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")
#endif

#include <math.h>

class GamepadState{
public:
	GamepadState();
	GamepadState(DIJOYSTATE state);
	GamepadState(XINPUT_STATE state);
	~GamepadState();

	void UploadState(DIJOYSTATE state);
	void UploadState(XINPUT_STATE state);

	bool Button[32];
	bool DpadU, DpadR, DpadD, DpadL;
	float TriggerL, TriggerR;
	float StickLX, StickLY;
	float StickRX, StickRY;

private:
	void InitGamepadState();
	void LockValue(float &value, float threshold);
	void LockAllValue();

private:
	float m_JoystickThreshold;
};

#endif