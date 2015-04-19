/**
AGP Assignment
Input.h
Purpose: Header file for Input.cpp

@author Marcel Zobus
*/

#include <dinput.h>

class Input
{
public:
	Input(HWND _hWnd, HINSTANCE _hInst);
	~Input();
	HRESULT InitialiseInput();
	void ReadInputStates();
	bool IsKeyPressed(unsigned char DI_keycode);
	bool IsKeyReleased(unsigned char DI_keycode);
private:
	HWND mHWnd;
	HINSTANCE mHInst;
	IDirectInput8 *mDirectInput;
	IDirectInputDevice8 *mKeyboardDevice;
	unsigned char mKeyboardKeysState[256];
};