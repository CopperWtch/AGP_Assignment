/**
AGP Assignment
Input.cpp
Purpose: Manages the Inputs

@author Marcel Zobus
*/

#include "Input.h"

Input::Input(HWND _hWnd, HINSTANCE _hInst)
{
	mHWnd = _hWnd;
	mHInst = _hInst;
}

Input::~Input()
{
	if (mDirectInput) mDirectInput->Release();
	if (mKeyboardDevice) mKeyboardDevice->Release();
	mHWnd = nullptr; // TODO: do you do that to delete objects?
	mHInst = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////
//	Initialise Input
//////////////////////////////////////////////////////////////////////////////////////
HRESULT Input::InitialiseInput()
{
	HRESULT hr;
	ZeroMemory(mKeyboardKeysState, sizeof(mKeyboardKeysState));
	hr = DirectInput8Create(mHInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDirectInput, NULL);
	if (FAILED(hr)) return hr;

	hr = mDirectInput->CreateDevice(GUID_SysKeyboard, &mKeyboardDevice, NULL);
	if (FAILED(hr)) return hr;

	hr = mKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) return hr;

	hr = mKeyboardDevice->SetCooperativeLevel(mHWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) return hr;

	hr = mKeyboardDevice->Acquire();
	if (FAILED(hr)) return hr;

	return S_OK;

}

//////////////////////////////////////////////////////////////////////////////////////
//	Input Functions
//////////////////////////////////////////////////////////////////////////////////////
void Input::ReadInputStates()
{
	HRESULT hr;
	hr = mKeyboardDevice->GetDeviceState(sizeof(mKeyboardKeysState), (LPVOID)&mKeyboardKeysState);
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			mKeyboardDevice->Acquire();
		}
	}
}

bool Input::IsKeyPressed(unsigned char DI_keycode)
{
	return mKeyboardKeysState[DI_keycode] & 0x80;
}