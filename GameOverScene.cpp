/**
AGP Assignment
MainMenuScene.cpp
Purpose: renders Main Menu for the game

@author Sarah Bulk
*/
#include "GameOverScene.h"

GameOverScene::~GameOverScene()
{

}

bool GameOverScene::Init()
{
	mSceneData = SceneData::GetInstance();
	mD3DDevice = mSceneData->GetDevice();
	mImmediateContext = mSceneData->GetImmediateContext();
	initMenu();

	return true;
}


void GameOverScene::RenderScene(float dt)
{
	/*Timer* mTimer = Timer::getInstance();
	mTimer->PauseTime(true);*/


	//headline
	mTextGameOver->AddText("GAME", -0.45, +0.8, .2);
	mTextGameOver->AddText("OVER", -0.45, +0.5, .2);


	mTextGameOver->RenderText();

	mRootNode->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}

void GameOverScene::initMenu()
{

	mTextGameOver = new Text2D("assets/font1C.png", mD3DDevice, mImmediateContext);


	mRootNode = new SceneNode();


}
