/**
AGP Assignment
D3DManager.cpp
Purpose: Manages the DirectX initialisation

@author Marcel Zobus
*/

#include "D3DManager.h"


D3DManager::D3DManager()
{
	mDriverType = D3D_DRIVER_TYPE_NULL;
	mFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	mD3DDevice = NULL;
	mImmediateContext = NULL;
	mSwapChain = NULL;
	mBackBufferRTView = NULL;
}

void D3DManager::Start(HWND _hWnd)
{
	mHWnd = _hWnd;
	if (FAILED(initialiseD3D()))
	{
		DXTRACE_MSG("Failed to create Device");
	}
}


//////////////////////////////////////////////////////////////////////////////////////
// Create D3D device and swap chain
//////////////////////////////////////////////////////////////////////////////////////
HRESULT D3DManager::initialiseD3D()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(mHWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, // comment out this line if you need to test D3D 11.0 functionality on hardware that doesn't support it
		D3D_DRIVER_TYPE_WARP, // comment this out also to use reference device
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mHWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		mDriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, mDriverType, NULL,
			createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &mSwapChain,
			&mD3DDevice, &mFeatureLevel, &mImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr))
		return hr;

	// Get pointer to back buffer texture
	ID3D11Texture2D *pBackBufferTexture;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBufferTexture);

	if (FAILED(hr)) return hr;

	// Use the back buffer texture pointer to create the render target view
	hr = mD3DDevice->CreateRenderTargetView(pBackBufferTexture, NULL,
		&mBackBufferRTView);
	pBackBufferTexture->Release();

	if (FAILED(hr)) return hr;

	//create a z buffer texture
	D3D11_TEXTURE2D_DESC tex2dDesc;

	ZeroMemory(&tex2dDesc, sizeof(tex2dDesc));
	tex2dDesc.Width = width;
	tex2dDesc.Height = height;
	tex2dDesc.ArraySize = 1;
	tex2dDesc.MipLevels = 1;
	tex2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2dDesc.SampleDesc.Count = sd.SampleDesc.Count;
	tex2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2dDesc.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D *pZBufferTexture;
	hr = mD3DDevice->CreateTexture2D(&tex2dDesc, NULL, &pZBufferTexture);

	if (FAILED(hr)) return hr;

	//create the z buffer
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));

	dsvDesc.Format = tex2dDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	mD3DDevice->CreateDepthStencilView(pZBufferTexture, &dsvDesc, &mZBuffer);
	pZBufferTexture->Release();

	// Set the render target view
	mImmediateContext->OMSetRenderTargets(1, &mBackBufferRTView, mZBuffer);

	// Set the viewport
	D3D11_VIEWPORT viewport;

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	mImmediateContext->RSSetViewports(1, &viewport);

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////////////
// Clean up D3D objects
//////////////////////////////////////////////////////////////////////////////////////
void D3DManager::ShutdownD3D()
{
	if (mSwapChain) mSwapChain->Release();
	if (mImmediateContext) mImmediateContext->Release();
	if (mD3DDevice) mD3DDevice->Release();
	if (mBackBufferRTView) mBackBufferRTView->Release();
}


ID3D11Device* D3DManager::GetDevice()
{
	return mD3DDevice;
}
ID3D11DeviceContext* D3DManager::GetContext()
{
	return mImmediateContext;
}

IDXGISwapChain* D3DManager::GetSwapChain()
{
	return mSwapChain;
}
ID3D11RenderTargetView* D3DManager::GetBackBufferRTView()
{
	return mBackBufferRTView;
}

ID3D11DepthStencilView* D3DManager::GetZBuffer()
{
	return mZBuffer;
}
