/**
AGP Assignment
SceneManager.cpp
Purpose: A Controller to manage different scenes and the initialisation of the game

@author Marcel Zobus
*/

#include "SceneManager.h"

static SceneManager* instance = NULL;

SceneManager::SceneManager()
{
	//constructor
}

SceneManager::~SceneManager()
{
	//destructor
}

//////////////////////////////////////////////////////////////////////////////////////
//	Initialise
//////////////////////////////////////////////////////////////////////////////////////
void SceneManager::Initialise(HWND _hWnd, HINSTANCE _hInst)
{
	data = SceneData::GetInstance();
	mHWnd = _hWnd;
	mHInst = _hInst;
	mInput = new Input(mHWnd, mHInst);
	if (FAILED(mInput->InitialiseInput()))
	{
		DXTRACE_MSG("Failed to initialise input");
	}

	// create mD3DManager
	mD3DManager = new D3DManager();
	// call the start method 
	mD3DManager->Start(mHWnd);

	if (FAILED(initialiseGraphics()))
	{
		DXTRACE_MSG("Failed to initialise graphics");
	}
}

// initialise camera, scenes and get the directX pointers
HRESULT SceneManager::initialiseGraphics()
{
	// get all neccessary pointer from the d3dmanger
	mSwapChain = mD3DManager->GetSwapChain();
	mImmediateContext = mD3DManager->GetContext();
	//mD3DDevice = 
	mBackBufferRTView = mD3DManager->GetBackBufferRTView();
	mZBuffer = mD3DManager->GetZBuffer();

	data->SetDevice(mD3DManager->GetDevice());
	data->SetImmediateContext(mImmediateContext);


	// create camera
	mCamera = new Camera(1.0f, 0.1f, -9.0f, -0.5f);
	data->SetCamera(mCamera);
	
	// create particlegenerator;
	/*mParticle = new ParticleGenerator(mD3DDevice, mImmediateContext);
	mParticle->InitialiseGenerator();*/

	// create scene 01
	mScene = TestScene::create();


	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Render
//////////////////////////////////////////////////////////////////////////////////////
void SceneManager::RenderFrame()
{
	mInput->ReadInputStates();
	if (mInput->IsKeyPressed(DIK_ESCAPE)) DestroyWindow(mHWnd);
	if (mInput->IsKeyPressed(DIK_W)) mCamera->Forward(0.0005);
	// Clear the back buffer - choose a colour you like
	float rgba_clear_colour[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
	mImmediateContext->ClearRenderTargetView(mBackBufferRTView, rgba_clear_colour);
	mImmediateContext->ClearDepthStencilView(mZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	mImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	mView = mCamera->GetViewMatrix();
	mProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0), 640.0 / 480.0, 1.0, 100.0);

	data->SetView(&mView);
	data->SetProjection(&mProjection);
	//mParticle->Draw(&mView, &mProjection, mCamera->GetPosition());

	mScene->RenderScene();

	// Display what has just been rendered
	mSwapChain->Present(0, 0);

}

//////////////////////////////////////////////////////////////////////////////////////
//	Shutdown
//////////////////////////////////////////////////////////////////////////////////////
void SceneManager::ShutDown3D()
{
	mD3DManager->ShutdownD3D();
}


