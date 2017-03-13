#include "GamepadState.h"



GamepadState::GamepadState()
{
	InitGamepadState();
}

GamepadState::GamepadState(DIJOYSTATE state)
{
	InitGamepadState();

	UploadState(state);
}

GamepadState::GamepadState(XINPUT_STATE state)
{
	InitGamepadState();

	UploadState(state);
}

GamepadState::~GamepadState()
{

}

void GamepadState::InitGamepadState()
{
	ZeroMemory(Button, 32);
	DpadU = DpadR = DpadD = DpadL = false;
	TriggerL = TriggerR = 0.f;
	StickLX = StickLY = 0.f;
	StickRX = StickRY = 0.f;

	m_JoystickThreshold = 0.15f;
}

void GamepadState::UploadState(DIJOYSTATE state)
{
	for(int i=0 ; i<32 ; i++)
		if(state.rgbButtons[i])
			Button[i] = true;

	switch(state.rgdwPOV[0]){
	case 0:
		DpadU = true;
		break;
	case 4500:
		DpadU = DpadR = true;
		break;
	case 9000:
		DpadR = true;
		break;
	case 13500:
		DpadR = DpadD = true;
		break;
	case 18000:
		DpadD = true;
		break;
	case 22500:
		DpadD = DpadL = true;
		break;
	case 27000:
		DpadL = true;
		break;
	case 31500:
		DpadL = DpadU = true;
		break;
	}

	// Should save the mapping of each joystick
	// This is PS4(DualShock 4) controller
	TriggerL = state.lRx/65565.f;
	TriggerR = state.lRy/65565.f;

	StickLX = state.lX/32768.f - 1.f;
	StickLY = -(state.lY/32768.f - 1.f);

	StickRX = state.lZ/32768.f -1.f;
	StickRY = -(state.lRz/32768.f - 1.f);

	LockAllValue();
}

void GamepadState::UploadState(XINPUT_STATE state)
{
	for(int i=4 ; i<16 ; i++){
		if(state.Gamepad.wButtons & (int)pow(2.0, i))
			Button[i] = true;
	}

	DpadU = state.Gamepad.wButtons & 0x0001 ? true : false;
	DpadD = state.Gamepad.wButtons & 0x0002 ? true : false;
	DpadL = state.Gamepad.wButtons & 0x0004 ? true : false;
	DpadR = state.Gamepad.wButtons & 0x0008 ? true : false;

	TriggerL = state.Gamepad.bLeftTrigger/255.f;
	TriggerR = state.Gamepad.bRightTrigger/255.f;
	
	Button[30] = TriggerL != 0 ? true : false;
	Button[31] = TriggerR != 0 ? true : false;

	StickLX = state.Gamepad.sThumbLX/32768.f;
	StickLY = (state.Gamepad.sThumbLY/32768.f);

	StickRX = state.Gamepad.sThumbRX/32768.f;
	StickRY = (state.Gamepad.sThumbRY/32768.f);

	LockAllValue();
}

void GamepadState::LockAllValue()
{
	LockValue(TriggerL, m_JoystickThreshold);
	LockValue(TriggerR, m_JoystickThreshold);

	LockValue(StickLX, m_JoystickThreshold);
	LockValue(StickLY, m_JoystickThreshold);

	LockValue(StickRX, m_JoystickThreshold);
	LockValue(StickRY, m_JoystickThreshold);
}

void GamepadState::LockValue(float &value, float threshold)
{
	if(value < threshold && value > -threshold)
		value = 0.f;
}
