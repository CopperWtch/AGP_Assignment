/**
AGP Assignment
MainMenuScene.cpp
Purpose: renders Main Menu for the game

@author Sarah Bulk
*/
#include "MainMenuScene.h"

MainMenuScene::~MainMenuScene()
{

}

bool MainMenuScene::Init()
{
	mSceneData = SceneData::GetInstance();
	mD3DDevice = mSceneData->GetDevice();
	mImmediateContext = mSceneData->GetImmediateContext();
	initMenu();

	return true;
}


void MainMenuScene::RenderScene(float dt)
{
	Timer* mTimer = Timer::getInstance();
	mTimer->PauseTime(true);

	//render background image
	mBackground->Render(mImmediateContext, -1.0, 1.0, 2.0, 2.0);

	//headline
	mTextMenu->AddText("MENU", -0.25, +0.8, .1);

	//Render everything
	txtStart->Render(mImmediateContext, -0.4, +0.0, .6, .2);
	txtQuit->Render(mImmediateContext, -0.4, -0.4, .6, .2);



	mInput = mSceneData->GetInput();

	mInput->ReadInputStates();
	if (mInput->IsMouseClicked())
	{

		//not finalised input , still buggy
		if (mBtnStart->IsClicked(mInput->GetMouseData().x, mInput->GetMouseData().y));
		{
			bIsActive = false;
		}

		if (mBtnQuit->IsClicked(mInput->GetMouseData().x, mInput->GetMouseData().y));
		{
			DestroyWindow(mInput->GetMHWnd());
		}

		
	}

	//interact with menu via pressing buttons
	if (mInput->IsKeyPressed(DIK_P))
	{
		bIsActive = false;
	}

	if (mInput->IsKeyPressed(DIK_Q))
	{
		DestroyWindow(mInput->GetMHWnd());
	}

	mTextMenu->RenderText();

	mRootNode->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}

void MainMenuScene::initMenu()
{

	mTextMenu = new Text2D("assets/font1C.png", mD3DDevice, mImmediateContext);

	txtStart = new ImageClass(mD3DDevice, mImmediateContext, "assets/btnStart.png");
	txtQuit = new ImageClass(mD3DDevice, mImmediateContext, "assets/btnQuit.png");

	mBtnStart = new Button(txtStart);
	mBtnQuit = new Button(txtQuit);


	mBackground = new ImageClass(mD3DDevice, mImmediateContext, "assets/bg.png");

	bIsActive = true;

	mRootNode = new SceneNode();


}

bool MainMenuScene::GetIsActive()
{
	return bIsActive;
}

void MainMenuScene::SetIsActive(bool isActive)
{
	bIsActive = isActive;
}