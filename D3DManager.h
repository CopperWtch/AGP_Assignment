#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#include "Camera.h"

class D3DManager 
{
public:
	D3DManager();
	void Start(HWND g_hWnd);
	void ShutdownD3D();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	IDXGISwapChain* GetSwapChain();
	ID3D11RenderTargetView* GetBackBufferRTView();
	ID3D11DepthStencilView* GetZBuffer();

private:
	HRESULT initialiseD3D();
	HRESULT initialiseGraphics();
	HWND m_hWnd;
	D3D_DRIVER_TYPE g_driverType;
	D3D_FEATURE_LEVEL g_featureLevel;
	ID3D11Device* g_pD3DDevice;
	ID3D11DeviceContext* g_pImmediateContext;
	IDXGISwapChain* g_pSwapChain;
	ID3D11RenderTargetView* g_pBackBufferRTView;
	ID3D11DepthStencilView* g_pZBuffer;
	
};


