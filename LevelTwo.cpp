/**
AGP Assignment
GameScene.cpp
Purpose: Main Scene for the Game

@author Marcel Zobus
*/
#include "LevelTwo.h"

//destructor 
LevelTwo::~LevelTwo()
{
	if (mRootNodeLevel) delete mRootNodeLevel;
	if (levelGenerator) delete levelGenerator;
	if (mCube) delete mCube;
	if (mUpDownFlag) delete mUpDownFlag;
	if (mUpDownVelocity) delete mUpDownVelocity;
	if (mUpDownFlag2) delete mUpDownFlag2;
	if (mUpDownVelocity2) delete mUpDownVelocity2;
}

// init function of the scene
bool LevelTwo::Init()
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
void LevelTwo::RenderScene(float dt)
{
	moveGameObjectUpAndDown(mMovingChild, mUpDownVelocity, mUpDownFlag, maxPos, minPos , dt);
	moveGameObjectUpAndDown(mMovingChild2, mUpDownVelocity2, mUpDownFlag2, maxPos2, minPos2, dt);
	mRootNodeLevel->SetXPos(mRootNodeLevel->GetXPos() - mLevelMoveVelocity * dt);
	mRootNodeLevel->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}

// level initialisation
// generates the level and sets the seed for the levelgenerator and the models
void LevelTwo::initLevel()
{
	// create model 
	mCube = new Model(mD3DDevice, mImmediateContext);
	// load textrue for the model
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/plastic.jpg", NULL, NULL, &mTexture, NULL);
	mCube->LoadObjModel("assets/cube.obj", mTexture);

	// create root node
	mRootNodeLevel = new SceneNode();

	// create levelgenerator
	levelGenerator = new LevelGenerator();
	// set seed 
	levelGenerator->GetSeed()->SetLevelElements(20);
	// creates vector for special items which are moved up and down above the plattforms
	vector<int>* b = new vector<int>();
	// set fix objects which should be moved
	b->push_back(5);
	b->push_back(10);
	levelGenerator->GetSeed()->SetBlockIDs(b);

	// call generate function
	generate();
}

// initialises the variables needed for the moving childs
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

// is called in the render scene to move objects up and down
// parameters:	the scenenode of the object to mode
//				a float pointer for the velocity of the movement
//				a bool pointer for the flag which stops and starts the movement
//				a float for the maximum position, the minmum position and for the deltatime
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

// called from SceneManager to regenerate the level if the player gets to the next level
void LevelTwo::ReGenerateLevel()
{
	delete mRootNodeLevel;
	mRootNodeLevel = new SceneNode();
	generate();
}

// actually calls the generate function of the level generator and picks the moving objects
void LevelTwo::generate()
{
	// generate the level. returns a scenenode
	mRootNodeLevel = levelGenerator->Generate(mCube);

	initMovingChilds(true);
	// get moving childs from the vector in the seed
	mMovingChild = mRootNodeLevel->GetChildren().at(levelGenerator->GetSeed()->GetBlockIDs()->at(0))->GetChildren().at(0);
	mMovingChild2 = mRootNodeLevel->GetChildren().at(levelGenerator->GetSeed()->GetBlockIDs()->at(1))->GetChildren().at(0);
	// set min and maxpos
	minPos = mMovingChild->GetYPos();
	maxPos = mMovingChild->GetXScale() + mMovingChild->GetYPos() + 15;
	minPos2 = mMovingChild2->GetYPos();
	maxPos2 = mMovingChild2->GetXScale() + mMovingChild2->GetYPos() + 15;
}
