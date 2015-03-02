#include "SceneManager.h"


SceneManager::SceneManager()
{

}

void SceneManager::Initialise(HWND g_hWnd)
{
	d3dManager = new D3DManager();
	d3dManager->Start(g_hWnd);
	camera = new Camera(1.0f, 0.1f, -9.0f, -0.5f);
	scene01 = new Scene(d3dManager->GetDevice(), d3dManager->GetContext());
	scene01->Create();
	g_rootNode = scene01->GetRootNode();
	g_pSwapChain = d3dManager->GetSwapChain();
	g_pImmediateContext = d3dManager->GetContext();
	g_pD3DDevice = d3dManager->GetDevice();
	g_pBackBufferRTView = d3dManager->GetBackBufferRTView();
	g_pZBuffer = d3dManager->GetZBuffer();
}

void SceneManager::ShutDown3D()
{
	d3dManager->ShutdownD3D();
}

void SceneManager::RenderFrame()
{
	// Clear the back buffer - choose a colour you like
	float rgba_clear_colour[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
	g_pImmediateContext->ClearRenderTargetView(g_pBackBufferRTView, rgba_clear_colour);
	g_pImmediateContext->ClearDepthStencilView(g_pZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	XMMATRIX projection, view;
	view = camera->GetViewMatrix();
	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0), 640.0 / 480.0, 1.0, 100.0);

	scene01->RenderScene(view, projection);

	// RENDER HERE


	// Display what has just been rendered
	g_pSwapChain->Present(0, 0);

}