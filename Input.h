/**
AGP Assignment
Input.h
Purpose: Header file for Input.cpp

@author Marcel Zobus
*/

#include <dinput.h>

class Input
{
private:
	HWND mHWnd;
	HINSTANCE mHInst;
	IDirectInput8 *mDirectInput;
	IDirectInputDevice8 *mKeyboardDevice;
	unsigned char mKeyboardKeysState[256];

	bool bIsInWindow;
	//Sarah Bulk
	//struct to store the mouse data
	struct mouseData
	{
		IDirectInputDevice8 *mMouseDevice;
		int x, y,
			pinstate,
			pin;
		DIMOUSESTATE mMouseState;
	};
	mouseData mMouse;
	/////////////////////////////////

public:
	Input(HWND _hWnd, HINSTANCE _hInst);
	~Input();
	HRESULT InitialiseInput();
	void ReadInputStates();
	bool IsKeyPressed(unsigned char DI_keycode);
	bool IsKeyReleased(unsigned char DI_keycode);

	//Sarah Bulk
	//struct to store the mouse data
	bool IsMouseClicked();
	mouseData GetMouseData();

	bool IsInWindow();
	void SetIsInWindow(bool b);
	HWND GetMHWnd();
	/////////////////////////////////
};