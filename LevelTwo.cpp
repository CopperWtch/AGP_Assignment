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
	mRootNodeLevel->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}


void LevelTwo::initLevel()
{
	Model* mCube = new Model(mD3DDevice, mImmediateContext);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/plastic.jpg", NULL, NULL, &mTexture, NULL);
	mCube->LoadObjModel("assets/cube.obj", mTexture);
	mCube->SetLightData(mLight);

	mRootNodeLevel = new SceneNode();

	LevelGenerator* levelGenerator = new LevelGenerator();
	levelGenerator->GetSeed()->SetLevelElements(10);
	mRootNodeLevel = levelGenerator->Generate(mCube);

}
