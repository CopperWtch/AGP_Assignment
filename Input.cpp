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
	if (mMouse.mMouseDevice) mMouse.mMouseDevice->Release();
	mHWnd = nullptr; // TODO: do you do that to delete objects?
	mHInst = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////
//	Initialise Input
//////////////////////////////////////////////////////////////////////////////////////
HRESULT Input::InitialiseInput()
{
	//Initialise mouse data
	mMouse.pin = 0;
	mMouse.pinstate = 0;

	mMouse.x = 0;
	mMouse.y = 0;

	//Initialise Keyboard input
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

	//Initialise mouse input
	mDirectInput->CreateDevice(GUID_SysMouse, &mMouse.mMouseDevice, NULL);
	if (FAILED(hr)) return hr;

	hr = mMouse.mMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) return hr;

	hr = mMouse.mMouseDevice->SetCooperativeLevel(mHWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) return hr;

	hr = mMouse.mMouseDevice->Acquire();
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

	//Sarah Bulk
	//read mouse input
	hr = mMouse.mMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&(mMouse.mMouseState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			mMouse.mMouseDevice->Acquire();
		}
	}

	//update values only if the cursor is inside the window
	if (bIsInWindow)
	{
		mMouse.x += mMouse.mMouseState.lX;
		mMouse.y += mMouse.mMouseState.lY;
	}


	// Ensure the mouse location doesn't exceed the window width or height.
	if (mMouse.x < 0)  { mMouse.x = 0; }
	if (mMouse.y < 0)  { mMouse.y = 0; }

	//get window size
	RECT rc;
	GetClientRect(mHWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	if (mMouse.x > width)  { mMouse.x = width; }
	if (mMouse.y > height) { mMouse.y = height; }

	if (mMouse.x != 0)
		bool stopHere = true;

	mMouse.pin = 0;

	// has a single-click occured?
	if (mMouse.mMouseState.rgbButtons[0] && !mMouse.pinstate) {
		mMouse.pinstate = 1;
		mMouse.pin = 1;
	}

	// reset 'pin' state
	if (!mMouse.mMouseState.rgbButtons[0])
		mMouse.pinstate = 0;
	///////////////////////////////////////////
}

bool Input::IsKeyPressed(unsigned char DI_keycode)
{
	return mKeyboardKeysState[DI_keycode] & 0x80;
}


// not working yet
bool Input::IsKeyReleased(unsigned char DI_keycode)
{
	return !((mKeyboardKeysState[DI_keycode]) & 0x80);
}


//////////////////////////////////////////////////////////////////////////////////////
// Sarah Bulk
// Return is click event occured
//////////////////////////////////////////////////////////////////////////////////////
bool Input::IsMouseClicked()
{
	if (mMouse.pin == 1)
		return true;
	else
		return false;

}

//////////////////////////////////////////////////////////////////////////////////////
// Sarah Bulk
// Access modifiers
//////////////////////////////////////////////////////////////////////////////////////
bool Input::IsInWindow()
{ 
	return bIsInWindow; 
}

void Input::SetIsInWindow(bool b)
{ 
	bIsInWindow = b; 
}

HWND Input::GetMHWnd()
{ 
	return mHWnd; 
}

mouseData Input::GetMouseData()
{ 
	return mMouse; 
}