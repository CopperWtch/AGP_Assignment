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

	initMovingChilds(false);

	initLevel();

	return true;
}


void LevelTwo::RenderScene(float dt)
{
	moveGameObjectUpAndDown(mMovingChild, mUpDownVelocity, mUpDownFlag, maxPos, minPos , dt);
	moveGameObjectUpAndDown(mMovingChild2, mUpDownVelocity2, mUpDownFlag2, maxPos2, minPos2, dt);
	mRootNodeLevel->SetXPos(mRootNodeLevel->GetXPos() - mLevelMoveVelocity * dt);
	mRootNodeLevel->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}

void LevelTwo::initMovingChilds(bool isReset)
{
	if (isReset)
	{
		delete mUpDownFlag;
		delete mUpDownVelocity;
		delete mUpDownFlag2;
		delete mUpDownVelocity2;
	}

	mUpDownFlag = new bool();
	mUpDownVelocity = new float();
	*mUpDownFlag = true;
	*mUpDownVelocity = 6;
	mUpDownFlag2 = new bool();
	mUpDownVelocity2 = new float();
	*mUpDownFlag2 = true;
	*mUpDownVelocity2 = 6;
}

void LevelTwo::moveGameObjectUpAndDown(SceneNode* movingChild, float* velocity, bool* updownflag, float maxPos, float minPos, float dt)
{
	movingChild->SetYPos(movingChild->GetYPos() + (*velocity*dt));

	if (*updownflag && movingChild->GetYPos() > maxPos)
	{
		*velocity *= -1;
		*updownflag = false;
	}
	if (*updownflag && movingChild->GetYPos() < minPos)
	{
		*velocity *= -1;
		*updownflag = false;
	}

	if (movingChild->GetYPos() < maxPos && movingChild->GetYPos() > minPos)
		*updownflag = true;
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
	vector<int>* b = new vector<int>();
	b->push_back(5);
	b->push_back(10);
	levelGenerator->GetSeed()->SetBlockIDs(b);
	generate();
}



void LevelTwo::ReGenerateLevel()
{
	delete mRootNodeLevel;
	mRootNodeLevel = new SceneNode();
	generate();
}

void LevelTwo::generate()
{
	mRootNodeLevel = levelGenerator->Generate(mCube);

	initMovingChilds(true);
	mMovingChild = mRootNodeLevel->GetChildren().at(levelGenerator->GetSeed()->GetBlockIDs()->at(0))->GetChildren().at(0);
	mMovingChild2 = mRootNodeLevel->GetChildren().at(levelGenerator->GetSeed()->GetBlockIDs()->at(1))->GetChildren().at(0);
	minPos = mMovingChild->GetYPos();
	maxPos = mMovingChild->GetXScale() + mMovingChild->GetYPos() + 15;
	minPos2 = mMovingChild2->GetYPos();
	maxPos2 = mMovingChild2->GetXScale() + mMovingChild2->GetYPos() + 15;
}
