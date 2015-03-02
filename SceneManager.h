#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

#include "D3DManager.h"
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	void Initialise(HWND g_hWnd);
	void ShutDown3D();
	void RenderFrame();
private: 
	D3DManager *d3dManager;
	Camera *camera;
	Scene *scene01;
	Scene_Node *g_rootNode;
	IDXGISwapChain* g_pSwapChain;
	ID3D11Device* g_pD3DDevice;
	ID3D11DeviceContext* g_pImmediateContext;
	ID3D11RenderTargetView* g_pBackBufferRTView;
	ID3D11DepthStencilView* g_pZBuffer;

};