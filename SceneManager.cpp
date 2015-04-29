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

	// create camera
	mCamera = new Camera(0, 0, 0, 0);

	// create Light
	mAmbientLight = new Light();
	mAmbientLight->SetLightColour(0.3f, 0.3f, 0.3f, 0.3f);
	mDirectionalLight = new DirectionalLight();
	mDirectionalLight->SetLightColour(0.5f, 0.5f, 0.5f, 0.5f);
	mDirectionalLight->SetLightDirection(0.f, 0.f, -1.f);


	// init player object
	initPlayer();
	mActivePlayerState = PlayerState::Alive;

	// fill sceneData 
	// IMPORTANT!!!
	// THIS HAS TO BE DONE BEFORE CREATING THE LEVEL SCENES!
	data->SetDevice(mD3DManager->GetDevice());
	data->SetImmediateContext(mImmediateContext);
	data->SetCamera(mCamera);
	data->SetInput(mInput);

	LightManager::GetInstance()->SetDirectionalLight(mDirectionalLight);
	LightManager::GetInstance()->SetAmbientLight(mAmbientLight);

	// create level scenes
	mGameScene = GameScene::create();
	mLevelTwo = LevelTwo::create();
	mHUD = HUDScene::create();
	mMainMenu = MainMenuScene::create();
	mGameOver = GameOverScene::create();

	// set active level
	mLevelCounter = 1;
	mActiveSceneState = SceneState::MenuStart;
	mPreviousSceneState = SceneState::MenuStart;
	mNextLevel = false;

	// init render variables
	mMovementVelociy = 12;
	positionY = 0;
	velocityY = 0;
	gravity = 45.0f;
	isJump = false;
	isDoubleJump = true;
	isNextLevelDebugKey = true;
	isDieDebugKey = true;
	isMenuKey = true;

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Render
//////////////////////////////////////////////////////////////////////////////////////
void SceneManager::RenderFrame(float dt)
{
	mInput->ReadInputStates();
	if (mInput->IsKeyPressed(DIK_ESCAPE))
	{
		DestroyWindow(mHWnd);
	}

	if (mActivePlayerState == PlayerState::Alive)
	{
		/*********************** Input ***********************/

		if (mInput->IsKeyPressed(DIK_LEFTARROW)) mRootNodePlayer->SetXPos(mRootNodePlayer->GetXPos() - dt * mMovementVelociy);
		if (mInput->IsKeyPressed(DIK_RIGHTARROW)) mRootNodePlayer->SetXPos(mRootNodePlayer->GetXPos() + dt * mMovementVelociy);

		// jump velocity 
		if (mInput->IsKeyPressed(DIK_SPACE))
		{
			if (!isJump)
			{
				velocityY = 16;
				isJump = true;
			}
		}
		// double jump
		if (mInput->IsKeyReleased(DIK_SPACE))
		{
			if (isDoubleJump)
			{
				isJump = false;
				isDoubleJump = false;
			}
		}

		// debug next level
		if (mInput->IsKeyPressed(DIK_END))
		{
			if (isNextLevelDebugKey)
			{
				nextLevel();
				isNextLevelDebugKey = false;
			}
		}
		if (mInput->IsKeyReleased(DIK_END))
		{
			isNextLevelDebugKey = true;
		}

		if (mInput->IsKeyPressed(DIK_DELETE))
		{
			if (isDieDebugKey)
			{
				killPlayer();
				isDieDebugKey = false;
			}
		}
		if (mInput->IsKeyReleased(DIK_DELETE))
		{
			isDieDebugKey = true;
		}
	}

	if (mActivePlayerState == PlayerState::Dead)
	{
		if (mRootNodePlayer->GetXAngle() > -90)
			mRootNodePlayer->SetXAngle(mRootNodePlayer->GetXAngle() + dt * -80);

		if (mInput->IsKeyPressed(DIK_INSERT))
		{
			if (isResetKey)
			{
				resetGame();
				isResetKey = false;
			}
		}
		if (mInput->IsKeyReleased(DIK_INSERT))
		{
			isResetKey = true;
		}
	}

	//debug lighten
	if (mInput->IsKeyPressed(DIK_L)) mAmbientLight->IncreaseLight(.0001f, .0001f, .0001f, 0.f);

	//debug dim light
	if (mInput->IsKeyPressed(DIK_O)) mAmbientLight->DecreaseLight(.0001f, .0001f, .0001f, 0.f);


	//open menu on button press
	if (mInput->IsKeyPressed(DIK_M))
	{
		if (isMenuKey)
		{
			if (mActiveSceneState == SceneState::MenuDead || mActiveSceneState == SceneState::MenuStart)
			{
				mActiveSceneState = mPreviousSceneState;
			}
			else
			{
				mPreviousSceneState = mActiveSceneState;
				mActiveSceneState = SceneState::MenuStart;
			}
			isMenuKey = false;
		}
	}
	if (mInput->IsKeyReleased(DIK_M))
	{
		isMenuKey = true;
	}

	//interact with menu via pressing buttons
	if (mInput->IsKeyPressed(DIK_P))
	{
		if (mActiveSceneState == SceneState::MenuStart && mPreviousSceneState == SceneState::MenuStart)
			mActiveSceneState = SceneState::Level1;
	}

	if (mInput->IsKeyPressed(DIK_Q))
	{
		if (mActiveSceneState == SceneState::MenuDead || mActiveSceneState == SceneState::MenuStart)
			DestroyWindow(mInput->GetMHWnd());
	}

	/*********************** view & projection ***********************/

	// Clear the back buffer - choose a colour you like
	float rgba_clear_colour[4] = { 0.15f, 0.15f, 0.15f, 1.0f };
	mImmediateContext->ClearRenderTargetView(mBackBufferRTView, rgba_clear_colour);
	mImmediateContext->ClearDepthStencilView(mZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	mImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// set view and projection
	XMVECTOR playerPos = XMVectorSet(mRootNodePlayer->GetXPos(), mRootNodePlayer->GetYPos() + 5, mRootNodePlayer->GetZPos() - 25, 0.0f);
	mView = mCamera->GetViewMatrixThirdPerson(playerPos);
	// 16:9 
	mProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0), 16.0 / 9.0, 1.0, 100.0);

	data->SetView(&mView);
	data->SetProjection(&mProjection);

	/*********************** player jump ***********************/

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
		isDoubleJump = true;
	}

	// execute player (render)
	mRootNodePlayer->execute(&XMMatrixIdentity(), &mView, &mProjection);

	renderScenes(dt);

	// Display what has just been rendered
	mSwapChain->Present(0, 0);
}


void SceneManager::initPlayer()
{
	Model* mPlayerModel = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/chuck.bmp", NULL, NULL, &mTexture, NULL);

	mPlayerModel->LoadObjModel("assets/chuck.obj", mTexture);

	mPlayer = new Player(mPlayerModel);

	mRootNodePlayer = new SceneNode();
	SceneNode* mNode = new SceneNode();

	mRootNodePlayer->SetGameObject(mPlayer);
	mRootNodePlayer->addChildNode(mNode);
	mRootNodePlayer->SetScale(0.03f);
	mRootNodePlayer->SetYAngle(90);
	mRootNodePlayer->SetYPos(1);
}

void SceneManager::renderScenes(float dt)
{
	switch (mActiveSceneState)
	{
	case SceneState::MenuStart:
		mMainMenu->RenderScene(dt);
		break;
	case SceneState::Level1:
		if (mNextLevel)
		{
			mGameScene->ReGenerateLevel();
			mNextLevel = false;
		}
		mGameScene->RenderScene(dt);
		break;
	case SceneState::Level2:
		if (mNextLevel)
		{
			mLevelTwo->ReGenerateLevel();
			mNextLevel = false;
		}
		mLevelTwo->RenderScene(dt);
		break;
	case SceneState::MenuDead:
		mGameOver->RenderScene(dt);
		break;
	}

	if (mActiveSceneState == SceneState::MenuDead || mActiveSceneState == SceneState::MenuStart)
	{
		Timer::getInstance()->PauseTime(true);
	}
	else
	{
		//render HUD
		mHUD->RenderScene(dt);
		Timer::getInstance()->PauseTime(false);
	}

}

void SceneManager::nextLevel()
{
	nextLevelSetting();
	mRootNodePlayer->SetXPos(0);
	mRootNodePlayer->SetYPos(1);
	mLevelCounter++;
	mNextLevel = true;
}

void SceneManager::nextLevelSetting()
{
	if (mActiveSceneState == SceneState::Level1)
		mActiveSceneState = SceneState::Level2;
	else if (mActiveSceneState == SceneState::Level2)
		mActiveSceneState = SceneState::Level1;
	/*else if (mActiveLevelSetting == LevelSetting::Setting3)
		mActiveLevelSetting = LevelSetting::Setting1;*/
}

void SceneManager::killPlayer()
{
	//TODO: HUD Message Here
	mActiveSceneState = SceneState::MenuDead;
	mActivePlayerState = PlayerState::Dead;
}

void SceneManager::resetGame()
{
	mLevelCounter = 1;
	mActiveSceneState = SceneState::MenuStart;
	mNextLevel = false;
	mActivePlayerState = PlayerState::Alive;
	mPreviousSceneState = SceneState::MenuStart;
	mRootNodePlayer->SetXPos(0);
	mRootNodePlayer->SetYPos(1);
	mRootNodePlayer->SetXAngle(0);

	isJump = false;
	isDoubleJump = true;
	isNextLevelDebugKey = true;
	isDieDebugKey = true;

	delete mGameScene;
	delete mLevelTwo;
	mGameScene = GameScene::create();
	mLevelTwo = LevelTwo::create();
	mHUD = HUDScene::create();

	//TODO: reset player hud values
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


