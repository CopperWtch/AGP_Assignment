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
	// get scenedata
	data = SceneData::GetInstance();

	mHWnd = _hWnd;
	mHInst = _hInst;

	// create input class
	mInput = new Input(mHWnd, mHInst);
	if (FAILED(mInput->InitialiseInput()))
	{
		DXTRACE_MSG("Failed to initialise input");
	}

	// create mD3DManager
	mD3DManager = new D3DManager();
	// call the start method 
	mD3DManager->Start(mHWnd);

	// initialise graphic functions
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

	// fill LightManager
	LightManager::GetInstance()->SetDirectionalLight(mDirectionalLight);
	LightManager::GetInstance()->SetAmbientLight(mAmbientLight);

	// create level scenes
	mGameScene = GameScene::create();
	mLevelTwo = LevelTwo::create();
	mHUD = HUDScene::create();
	mMainMenu = MainMenuScene::create();
	mGameOver = GameOverScene::create();
	mInGameMenu = InGameMenuScene::create();

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
	// ending the game with Escape works always
	mInput->ReadInputStates();
	if (mInput->IsKeyPressed(DIK_ESCAPE))
	{
		DestroyWindow(mHWnd);
	}
	
	// if player is alive inputs
	if (mActivePlayerState == PlayerState::Alive)
	{
		/********************************************** Input **********************************************/

		if (mInput->IsKeyPressed(DIK_LEFTARROW)) mRootNodePlayer->SetXPos(mRootNodePlayer->GetXPos() - dt * mMovementVelociy);
		if (mInput->IsKeyPressed(DIK_RIGHTARROW)) mRootNodePlayer->SetXPos(mRootNodePlayer->GetXPos() + dt * mMovementVelociy);

		// press space for jumping 
		if (mInput->IsKeyPressed(DIK_SPACE))
		{
			if (!isJump)
			{
				// adds jump velocity
				velocityY = 16;
				isJump = true;
			}
		}
		// press space again for double jump
		if (mInput->IsKeyReleased(DIK_SPACE))
		{
			if (isDoubleJump)
			{
				isJump = false;
				isDoubleJump = false;
			}
		}

		// Press end for the next level (debug function)
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

		// press delete to kill the player (debug function)
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

		// lighten (debug function)
		if (mInput->IsKeyPressed(DIK_L)) mAmbientLight->IncreaseLight(.0001f, .0001f, .0001f, 0.f);

		// dim light (debug function)
		if (mInput->IsKeyPressed(DIK_O)) mAmbientLight->DecreaseLight(.0001f, .0001f, .0001f, 0.f);

		//open menu on button press
		if (mInput->IsKeyPressed(DIK_M))
		{
			if (isMenuKey)
			{
				if (mActiveSceneState == SceneState::MenuInGame)
				{
					mActiveSceneState = mPreviousSceneState;
				}
				else if (mActiveSceneState != SceneState::MenuDead && mActiveSceneState != SceneState::MenuStart)
				{
					mPreviousSceneState = mActiveSceneState;
					mActiveSceneState = SceneState::MenuInGame;
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

	}
	else // player is dead input
	{
		// animates the kill of the player (he falls over)
		if (mRootNodePlayer->GetXAngle() > -90)
			mRootNodePlayer->SetXAngle(mRootNodePlayer->GetXAngle() + dt * -80);

		// press insert to restart the game
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

	/********************************************** View & Projection **********************************************/

	// back buffer (dark color)
	float rgba_clear_colour[4] = { 0.15f, 0.15f, 0.15f, 1.0f };
	mImmediateContext->ClearRenderTargetView(mBackBufferRTView, rgba_clear_colour);
	mImmediateContext->ClearDepthStencilView(mZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	mImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// set view and projection
	XMVECTOR playerPos = XMVectorSet(mRootNodePlayer->GetXPos(), mRootNodePlayer->GetYPos() + 5, mRootNodePlayer->GetZPos() - 25, 0.0f);
	mView = mCamera->GetViewMatrixThirdPerson(playerPos);
	// 16:9 projection
	mProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0), 16.0 / 9.0, 1.0, 100.0);

	// set view and projection to sceneData
	data->SetView(&mView);
	data->SetProjection(&mProjection);

	/********************************************** Player Jump **********************************************/

	// jump
	// calculates the Y positon based on a velocity
	// the gravity reduces the velocity
	positionY += velocityY * dt;
	velocityY -= gravity * dt;
	mRootNodePlayer->SetYPos(positionY);

	// if on ground
	// gravity is working until on ground (Y pos <=1)
	if (mRootNodePlayer->GetYPos() <= 1)
	{
		velocityY = 0.0f;
		positionY = 1.0f;
		mRootNodePlayer->SetYPos(positionY);
		isJump = false;
		isDoubleJump = true;
	}

	/********************************************** Render Player and Scenes **********************************************/
	// execute player (render)
	mRootNodePlayer->execute(&XMMatrixIdentity(), &mView, &mProjection);

	// function which renders the correct scene
	renderScenes(dt);

	// Display what has just been rendered
	mSwapChain->Present(0, 0);
}

// initialised the player model
void SceneManager::initPlayer()
{
	// create a model for the player
	Model* mPlayerModel = new Model(mD3DDevice, mImmediateContext);
	// load the textrue for the model
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/chuck.bmp", NULL, NULL, &mTexture, NULL);
	mPlayerModel->LoadObjModel("assets/chuck.obj", mTexture);

	// add the model to the player object
	mPlayer = new Player(mPlayerModel);

	// create a scene root node
	mRootNodePlayer = new SceneNode();
	mRootNodePlayer->SetGameObject(mPlayer);
	mRootNodePlayer->SetScale(0.03f);
	mRootNodePlayer->SetYAngle(90);
	mRootNodePlayer->SetYPos(1);
}

void SceneManager::renderScenes(float dt)
{
	// switch the enum which holds the active scene
	switch (mActiveSceneState)
	{
	case SceneState::MenuStart: // render menu start scene
		mMainMenu->RenderScene(dt);
		break;
	case SceneState::MenuInGame: // render menu in game scene
		mInGameMenu->RenderScene(dt);
		break;
	case SceneState::Level1: // render level 1 scene
		if (mNextLevel) // if next level regnenerate the level so it looks different
		{
			mGameScene->ReGenerateLevel();
			mNextLevel = false;
		}
		mGameScene->RenderScene(dt);
		break;
	case SceneState::Level2: // render level 2 scene
		if (mNextLevel) // if next level regnenerate the level so it looks different
		{
			mLevelTwo->ReGenerateLevel();
			mNextLevel = false;
		}
		mLevelTwo->RenderScene(dt);
		break;
	case SceneState::MenuDead: // render menu dead scene
		mGameOver->RenderScene(dt);
		break;
	}

	// pause timer in the menu scenes
	if (mActiveSceneState == SceneState::MenuDead || mActiveSceneState == SceneState::MenuStart || mActiveSceneState == SceneState::MenuInGame)
	{
		Timer::getInstance()->PauseTime(true);
	}
	else // show hud and start timer in level scenes
	{
		mHUD->RenderScene(dt);
		Timer::getInstance()->PauseTime(false);
	}
}

// next level function sets values
void SceneManager::nextLevel()
{
	nextLevelSetting();
	// sets player to start point
	mRootNodePlayer->SetXPos(0);
	mRootNodePlayer->SetYPos(1);
	// adds 1 to levelcounter
	mLevelCounter++;
	mNextLevel = true;
}

// chooses the correct level setting for the next level
void SceneManager::nextLevelSetting()
{
	// if active is level 1 then level setting 2 and so on
	if (mActiveSceneState == SceneState::Level1)
		mActiveSceneState = SceneState::Level2;
	else if (mActiveSceneState == SceneState::Level2)
		mActiveSceneState = SceneState::Level1;
}

// sets the states for the scene and the player
void SceneManager::killPlayer()
{
	mActiveSceneState = SceneState::MenuDead;
	mActivePlayerState = PlayerState::Dead;
}

// sets variables back to default 
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
}

//////////////////////////////////////////////////////////////////////////////////////
//	Shutdown
//////////////////////////////////////////////////////////////////////////////////////
void SceneManager::ShutDown3D()
{
	mD3DManager->ShutdownD3D();
}

// Debug Function to log values in the console
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


