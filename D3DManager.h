#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

class D3DManager 
{
public:
	void Start(HWND g_hWnd);
	void ShutdownD3D();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	IDXGISwapChain* GetSwapChain();
	ID3D11RenderTargetView* GetBackBufferRTView();
private:
	HRESULT initialiseD3D();
	HRESULT initialiseGraphics();
	HWND m_hWnd;
	D3D_DRIVER_TYPE g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device* g_pD3DDevice = NULL;
	ID3D11DeviceContext* g_pImmediateContext = NULL;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_pBackBufferRTView = NULL;
	
};


