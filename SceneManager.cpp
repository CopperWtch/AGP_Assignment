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
	mD3DDevice = mD3DManager->GetDevice();
	mBackBufferRTView = mD3DManager->GetBackBufferRTView();
	mZBuffer = mD3DManager->GetZBuffer();

	data->SetDevice(mD3DManager->GetDevice());
	data->SetImmediateContext(mImmediateContext);


	// create camera
	mCamera = new Camera(0, 5, -35.0f, 0);
	data->SetCamera(mCamera);
	
	// create particlegenerator;
	/*mParticle = new ParticleGenerator(mD3DDevice, mImmediateContext);
	mParticle->InitialiseGenerator();*/

	mLight = new Light();
	mLight->SetAmbientLight(XMVectorSet(1.0f, 1.0f, 1.0f, 0.5f));

	data->SetLight(mLight);

	initPlayer();

	mLevel = 1;

	mScene = TestScene::create();

	mGameScene = GameScene::create();

	mLevelTwo = LevelTwo::create();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Render
//////////////////////////////////////////////////////////////////////////////////////
float positionY = 0;     // Position of the character
float velocityY = 0;     // Velocity of the character
float gravity = 45.0f;
bool isJump = false;

void SceneManager::RenderFrame(float dt)
{
	mInput->ReadInputStates();
	if (mInput->IsKeyPressed(DIK_ESCAPE)) DestroyWindow(mHWnd);
	if (mInput->IsKeyPressed(DIK_W)) mCamera->Forward(0.005);
	if (mInput->IsKeyPressed(DIK_S)) mCamera->Forward(-0.005);
	if (mInput->IsKeyPressed(DIK_A)) mCamera->MoveLeftRight(-0.005);
	if (mInput->IsKeyPressed(DIK_D)) mCamera->MoveLeftRight(0.005);

	float velociy =  10;

	if (mInput->IsKeyPressed(DIK_LEFTARROW)) mRootNodePlayer->SetXPos(mRootNodePlayer->GetXPos() - dt * velociy);
	if (mInput->IsKeyPressed(DIK_RIGHTARROW)) mRootNodePlayer->SetXPos(mRootNodePlayer->GetXPos() + dt * velociy);
	if (mInput->IsKeyPressed(DIK_SPACE))
	{
		if (!isJump)
		{
			velocityY = 14;
			isJump = true;
		}
			
	}
	if (mInput->IsKeyPressed(DIK_END))
	{
		if (mLevel < MAXLEVELCOUNT)
		{
			mLevel++;
			mRootNodePlayer->SetXPos(0);
			mRootNodePlayer->SetYPos(1);
		}	
	}

	// just for debug
	if (mInput->IsKeyPressed(DIK_HOME))
	{
		mLevel = 1;
		mRootNodePlayer->SetXPos(0);
		mRootNodePlayer->SetYPos(1);
	}

	// Clear the back buffer - choose a colour you like
	float rgba_clear_colour[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
	mImmediateContext->ClearRenderTargetView(mBackBufferRTView, rgba_clear_colour);
	mImmediateContext->ClearDepthStencilView(mZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	mImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	// jump
	positionY += velocityY * dt;     
	velocityY -= gravity * dt;        
	mRootNodePlayer->SetYPos(positionY);

	// if on ground
	if (mRootNodePlayer->GetYPos() <= 1)
	{
		velocityY = 0.0f;
		positionY = 1.0f;
		mRootNodePlayer->SetYPos(positionY);
		isJump = false;
	}

	


	mView = mCamera->GetViewMatrix();
	mProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0), 640.0 / 480.0, 1.0, 100.0);

	data->SetView(&mView);
	data->SetProjection(&mProjection);
	//mParticle->Draw(&mView, &mProjection, mCamera->GetPosition());

	mRootNodePlayer->execute(&XMMatrixIdentity(), &mView, &mProjection);

	// render correct scene depending on level
	switch (mLevel)
	{
	case 1:
		mGameScene->RenderScene(dt);
		break;
	case 2:
		mLevelTwo->RenderScene(dt);
		break;
	}

	// Display what has just been rendered
	mSwapChain->Present(0, 0);

}


void SceneManager::initPlayer()
{
	Model* mPlayerModel = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/chuck.bmp", NULL, NULL, &mTexture, NULL);

	mPlayerModel->LoadObjModel("assets/chuck.obj", mTexture);

	mPlayerModel->SetLightData(mLight);

	mPlayer = new Player(mPlayerModel);

	mRootNodePlayer = new SceneNode();
	SceneNode* mNode = new SceneNode();

	mRootNodePlayer->SetGameObject(mPlayer);
	mRootNodePlayer->addChildNode(mNode);
	mRootNodePlayer->SetScale(0.03f);
	mRootNodePlayer->SetYAngle(90);
	mRootNodePlayer->SetYPos(1);
	mNode->SetGameObject(mCamera);
}


//////////////////////////////////////////////////////////////////////////////////////
//	Shutdown
//////////////////////////////////////////////////////////////////////////////////////
void SceneManager::ShutDown3D()
{
	mD3DManager->ShutdownD3D();
}




void SceneManager::Log(float x){
	AllocConsole();
	HANDLE myConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD cCharsWritten;
	char buffer[1014];
	int n, a = 5, b = 3;
	n = sprintf_s(buffer, " x is %f \n", x);
	string thisString = buffer;
	WriteConsole(myConsoleHandle, thisString.c_str(), thisString.size(), &cCharsWritten, NULL);
}


