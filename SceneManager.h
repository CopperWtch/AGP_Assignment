/**
AGP Assignment
SceneManager.h
Purpose: Header file for SceneManager.cpp

@author Marcel Zobus
*/

#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

#include "D3DManager.h"
#include "Scene.h"
#include "Input.h"

class SceneManager
{
public:
	SceneManager(HWND _hWnd, HINSTANCE _hInst);
	void Initialise();
	void ShutDown3D();
	void RenderFrame();

private: 
	HRESULT initialiseGraphics();
	D3DManager *mD3DManager;
	Camera *mCamera;
	Scene *mScene01;
	Input *mInput;
	HWND mHWnd;
	HINSTANCE mHInst;
	IDXGISwapChain* mSwapChain;
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	ID3D11RenderTargetView* mBackBufferRTView;
	ID3D11DepthStencilView* mZBuffer;

};