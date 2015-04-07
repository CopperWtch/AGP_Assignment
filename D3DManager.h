/**
AGP Assignment
D3DManager.h
Purpose: Header file for D3DManager.cpp

@author Marcel Zobus
*/

#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

class D3DManager 
{
public:
	D3DManager();
	void Start(HWND _hWnd);
	void ShutdownD3D();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	IDXGISwapChain* GetSwapChain();
	ID3D11RenderTargetView* GetBackBufferRTView();
	ID3D11DepthStencilView* GetZBuffer();

private:
	HRESULT initialiseD3D();
	HRESULT initialiseGraphics();
	HWND mHWnd;
	D3D_DRIVER_TYPE mDriverType;
	D3D_FEATURE_LEVEL mFeatureLevel;
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	IDXGISwapChain* mSwapChain;
	ID3D11RenderTargetView* mBackBufferRTView;
	ID3D11DepthStencilView* mZBuffer;
	
};


