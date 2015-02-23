#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

#include "D3DManager.h"

class SceneManager
{
public:
	SceneManager();
	void Initialise(HWND g_hWnd);
	void ShutDown3D();
	void RenderFrame();
private: 
	D3DManager *d3dManager;
};