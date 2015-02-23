#include "SceneManager.h"


SceneManager::SceneManager()
{

}

void SceneManager::Initialise(HWND g_hWnd)
{
	d3dManager = new D3DManager();
	d3dManager->Start(g_hWnd);
}

void SceneManager::ShutDown3D()
{
	d3dManager->ShutdownD3D();
}

void SceneManager::RenderFrame()
{
	// Clear the back buffer - choose a colour you like
	float rgba_clear_colour[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
	d3dManager->GetContext()->ClearRenderTargetView(d3dManager->GetBackBufferRTView(), rgba_clear_colour);

	// RENDER HERE

	// Display what has just been rendered
	d3dManager->GetSwapChain()->Present(0, 0);

}