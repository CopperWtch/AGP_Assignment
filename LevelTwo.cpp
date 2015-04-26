/**
AGP Assignment
GameScene.cpp
Purpose: Main Scene for the Game

@author Marcel Zobus
*/
#include "LevelTwo.h"

LevelTwo::~LevelTwo()
{
	if (mRootNodeLevel) delete mRootNodeLevel;
}

bool LevelTwo::Init()
{
	mSceneData = SceneData::GetInstance();
	mD3DDevice = mSceneData->GetDevice();
	mImmediateContext = mSceneData->GetImmediateContext();

	mLight = mSceneData->GetLight();

	initLevel();

	return true;
}


void LevelTwo::RenderScene(float dt)
{
	mRootNodeLevel->SetXPos(mRootNodeLevel->GetXPos() - mLevelMoveVelocity * dt);
	mRootNodeLevel->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}


void LevelTwo::initLevel()
{
	mCube = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/plastic.jpg", NULL, NULL, &mTexture, NULL);
	mCube->LoadObjModel("assets/cube.obj", mTexture);
	mCube->SetLightData(mLight);

	mRootNodeLevel = new SceneNode();

	levelGenerator = new LevelGenerator();
	levelGenerator->GetSeed()->SetLevelElements(20);
	mRootNodeLevel = levelGenerator->Generate(mCube);

}

void LevelTwo::ReGenerateLevel()
{
	delete mRootNodeLevel;
	mRootNodeLevel = new SceneNode();
	mRootNodeLevel = levelGenerator->Generate(mCube);
}
