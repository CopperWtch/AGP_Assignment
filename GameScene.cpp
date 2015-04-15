/**
AGP Assignment
GameScene.cpp
Purpose: Main Scene for the Game

@author Marcel Zobus
*/
#include "GameScene.h"
#include "Player.h"

GameScene::~GameScene()
{
}

bool GameScene::Init()
{
	mSceneData = SceneData::GetInstance();
	mD3DDevice = mSceneData->GetDevice();
	mImmediateContext = mSceneData->GetImmediateContext();
	
	mlight = new Light();
	mlight->SetAmbientLight(XMVectorSet(1.0f, 1.0f, 1.0f, 0.5f));
	

	initPlayer();

	initLevel();


	return true;
}


float pos = 0.00f;
void GameScene::RenderScene()
{
	mRootNodePlayer->SetXPos(mRootNodePlayer->GetXPos() + pos);
	mRootNodePlayer->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
	mRootNodeLevel->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());

}

void GameScene::initPlayer()
{
	mPlayerModel = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/chuck.bmp", NULL, NULL, &mTexture, NULL);

	mPlayerModel->LoadObjModel("assets/chuck.obj", mTexture);
	
	mPlayerModel->SetLightData(mlight);

	Player* mPlayer = new Player(mPlayerModel);
	
	mRootNodePlayer = new SceneNode();
	SceneNode* mNode = new SceneNode();
	
	mRootNodePlayer->SetGameObject(mPlayer);
	mRootNodePlayer->addChildNode(mNode);
	mRootNodePlayer->SetScale(0.03f);
	mRootNodePlayer->SetYAngle(90);
	mRootNodePlayer->SetYPos(1);
	mNode->SetGameObject(mSceneData->GetCamera());
}

void GameScene::initLevel()
{
	Model* mCube = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/stone.jpg", NULL, NULL, &mTexture, NULL);
	mCube->LoadObjModel("assets/cube.obj", mTexture);
	mCube->SetLightData(mlight);

	Model* mCube2 = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/metal.jpg", NULL, NULL, &mTexture, NULL);
	mCube2->LoadObjModel("assets/cube.obj", mTexture);
	mCube2->SetLightData(mlight);

	mRootNodeLevel = new SceneNode();

	LevelGenerator* levelGenerator = new LevelGenerator();
	mRootNodeLevel = levelGenerator->Generate(mCube, mCube2);

}
