/**
AGP Assignment
GameScene.cpp
Purpose: First level of the game

@author Marcel Zobus
*/
#include "GameScene.h"
#include "Player.h"

//destructor 
GameScene::~GameScene()
{
	if (mRootNodeLevel) delete mRootNodeLevel;
	if (mUpDownFlag) delete mUpDownFlag;
	if (mUpDownFlag2) delete mUpDownFlag2;
	if (mUpDownVelocity) delete mUpDownVelocity;
	if (mUpDownVelocity2) delete mUpDownVelocity2;
	
	if (levelGenerator) delete levelGenerator;
	if (mCube) delete  mCube;
	if (mCube2) delete  mCube2;
}

// init function of the scene
bool GameScene::Init()
{
	// get scene data from the singleton
	mSceneData = SceneData::GetInstance();
	mD3DDevice = mSceneData->GetDevice();
	mImmediateContext = mSceneData->GetImmediateContext();

	// inititalise the moving child variables
	initMovingChilds(false);

	// initialise the level
	initLevel();

	return true;
}

// render function of the scene with the delta time as parameter
void GameScene::RenderScene(float dt)
{
	moveGameObjectUpAndDown(mMovingChild, mUpDownVelocity, mUpDownFlag, 8, dt);
	moveGameObjectUpAndDown(mMovingChild2, mUpDownVelocity2, mUpDownFlag2, 10, dt);
	mRootNodeLevel->SetXPos(mRootNodeLevel->GetXPos() - mLevelMoveVelocity * dt);
	mRootNodeLevel->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}

// level initialisation
// generates the level and sets the seed for the levelgenerator and the models
void GameScene::initLevel()
{
	// create model 1
	mCube = new Model(mD3DDevice, mImmediateContext);
	// load textrue for model 1
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/stone.jpg", NULL, NULL, &mTexture, NULL);
	mCube->LoadObjModel("assets/cube.obj", mTexture);

	// create model 2
	mCube2 = new Model(mD3DDevice, mImmediateContext);
	// load textrue for model 2
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/metal.jpg", NULL, NULL, &mTexture, NULL);
	mCube2->LoadObjModel("assets/cube.obj", mTexture);

	// create root scene node
	mRootNodeLevel = new SceneNode();

	// create level generator
	levelGenerator = new LevelGenerator();
	// change seed 
	levelGenerator->GetSeed()->SetLevelElements(15);
	// generate function call
	generate();
}

// initialises the variables needed for the moving childs
void GameScene::initMovingChilds(bool isReset)
{
	if (isReset)
	{
		delete mUpDownFlag;
		delete mUpDownFlag2;
		delete mUpDownVelocity;
		delete mUpDownVelocity2;
	}
	
	mUpDownFlag = new bool();
	mUpDownFlag2 = new bool();
	mUpDownVelocity = new float();
	mUpDownVelocity2 = new float();
	*mUpDownFlag = true;
	*mUpDownFlag2 = false;
	*mUpDownVelocity = 10;
	*mUpDownVelocity2 = -6;
}

// is called in the render scene to move objects up and down
// parameters:	the scenenode of the object to mode
//				a float pointer for the velocity of the movement
//				a bool pointer for the flag which stops and starts the movement
//				a float for the maximum position and for the deltatime
void GameScene::moveGameObjectUpAndDown(SceneNode* movingChild, float* velocity, bool* updownflag, float maxPos, float dt)
{
	movingChild->SetYPos(movingChild->GetYPos() + (*velocity*dt));

	if (*updownflag && movingChild->GetYPos() >= maxPos)
	{
		*velocity *= -1;
		*updownflag = false;
	}
	if (*updownflag && movingChild->GetYPos() <= -maxPos)
	{
		*velocity *= -1;
		*updownflag = false;
	}

	if (movingChild->GetYPos() < maxPos && movingChild->GetYPos() > -maxPos)
		*updownflag = true;
}

// called from SceneManager to regenerate the level if the player gets to the next level
void GameScene::ReGenerateLevel()
{
	delete mRootNodeLevel;
	mRootNodeLevel = new SceneNode();
	generate();
}

// actually calls the generate function of the level generator and picks the two moving objects
void GameScene::generate()
{
	// generates the level into a scenenode
	mRootNodeLevel = levelGenerator->Generate(mCube, mCube2);

	initMovingChilds(true);
	// two moving objects in the rootnode
	mMovingChild = mRootNodeLevel->GetChildren().at((int)AGPRandom::GetInstance()->GetRandomRange(3, 1));
	mMovingChild2 = mRootNodeLevel->GetChildren().at((int)AGPRandom::GetInstance()->GetRandomRange(5, 3));
}

