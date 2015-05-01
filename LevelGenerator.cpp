/**
AGP Assignment
LevelGenerator.cpp
Purpose: Generates the Levels

@author Marcel Zobus
*/

#include "LevelGenerator.h"

//////////////////////////////////////////////////////////////////////////////////////
// LEVEL GENERATOR CLASS
//////////////////////////////////////////////////////////////////////////////////////

// constructor 1
LevelGenerator::LevelGenerator()
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = new Seed(10, 5, 5, 1, 5, 1, 10, new vector<int>());
	initLightSpheres();
}
// constructor 2 with seed object as a parameter
LevelGenerator::LevelGenerator(Seed* seed)
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = seed;
	initLightSpheres();
}
// constructor 3 with the values for a new seed as parameters
LevelGenerator::LevelGenerator(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin, int levelElements, vector<int>* blocks)
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = new Seed(scaleMax, scaleMin, spanMax, spanMin, yPosMax, yPosMin, levelElements, blocks);
	initLightSpheres();
}

// destructor
LevelGenerator::~LevelGenerator()
{
	if (mSeed) delete mSeed;
}

// generate 1 with just one model for the level
SceneNode* LevelGenerator::Generate(Model* modelA)
{
	mModelA = modelA;
	isMultipleModel = false;
	return generateLevel();
}
// generate 2 with two models for the level
SceneNode* LevelGenerator::Generate(Model* modelA, Model* modelB)
{
	mModelA = modelA;
	mModelB = modelB;
	isMultipleModel = true;
	return generateLevel();
}

// generates the level
SceneNode* LevelGenerator::generateLevel()
{
	// creates a new scenenode which will be returned
	SceneNode* mRootNodeLevel = new SceneNode();
	
	// initialises the previous scenenode with the rootNode;
	SceneNode* prevNode = mRootNodeLevel;
	// init span
	float span = .0f;

	// for loop as long as the seed value for the amount of elements
	// each loop is the generation of one platform element in the level
	for (int i = 0; i < mSeed->GetLevelElements(); i++)
	{
		// create new scenenode for each part
		SceneNode* mNodeLevelPart = new SceneNode();

		// if multiple models this code sets the models by random
		if (isMultipleModel)
		{
			float val = agpRandom->GetRandom0To1();
			// if <= 0.5 then normal ypos value else the value is minus
			if (val <= 0.5f)
				mNodeLevelPart->SetGameObject(mModelA);
			else
				mNodeLevelPart->SetGameObject(mModelB);
		}
		else // just one model so set modelA
		{
			mNodeLevelPart->SetGameObject(mModelA);
		}

		// add models as childNode
		mRootNodeLevel->addChildNode(mNodeLevelPart);

		// generates and sets random scale for this element
		float scale = (int)agpRandom->GetRandomRange(mSeed->GetScaleMax() + 1, mSeed->GetScaleMin());
		mNodeLevelPart->SetXScale(scale);
		mNodeLevelPart->SetZScale(scale);

		// generate random span between the blocks using the seeds max and min span
		span = agpRandom->GetRandomRange(mSeed->GetSpanMax() + 1, mSeed->GetSpanMin());

		// calculate the x position of the element
		// position of the previous element + the scale of the previous element + the new random scale and span
		mNodeLevelPart->SetXPos(prevNode->GetXPos() + prevNode->GetXScale() + scale + span);

		// generates a random y position between the min and max in the seed 
		float ypos = agpRandom->GetRandomRange(mSeed->GetYPosMax() + 1, mSeed->GetYPosMin());

		// random value between 0.999 and 0 
		float val = agpRandom->GetRandom0To1();
		// if <= 0.5 then normal ypos value else the value is minus
		// this means a ratio of 50:50 
		if (val <= 0.5f)
			mNodeLevelPart->SetYPos(ypos);
		else
			mNodeLevelPart->SetYPos(ypos * -1);

		// if i = 0 it means it is the first element
		// the first element should always be at 0,0,0
		if (i == 0) // first element 
		{
			mNodeLevelPart->SetXPos(0);
			mNodeLevelPart->SetYPos(0);
		}
		else // not first element 
		{
			// every element besides the first element has a child element
			// this could be a light item, a dark item
			// or a moving object which blocks the way

			// create item node
			SceneNode *item = new SceneNode();
			
			// get the choosen elements form the seed vector i defined in the level scene
			vector<int>* b = mSeed->GetBlockIDs();
			// checks if i is in the vector
			// if i is in the vector a moving object is created
			// if not a light or dark item is created
			if (std::find(b->begin(), b->end(), i) != b->end()) // Element is in vector.
			{
				// adds the models and sets the y pos
				item->SetGameObject(mModelA);
				item->SetYPos(scale + 2);
				// reset the scale to be in the ratio 1:1:1 again
				float resettedScale = 1 / scale;
				// set new scale and note to the element node
				item->SetYScale(scale);
				mNodeLevelPart->addChildNode(item);
			}
			else // i is not in the vector which means a item is created
			{
				// 70% chance for light items
				if (agpRandom->GetRandom0To1() < 0.7f)
					item->SetGameObject(mLightSphere);
				else
					item->SetGameObject(mDarkSphere);

				// set y position
				item->SetYPos(3);

				// reset the scale to be in the ratio 1:1:1 again
				float resettedScale = 1 / scale;
				// set new scale to 25 % of the original size
				item->SetXScale(resettedScale * 0.25);
				item->SetZScale(resettedScale * 0.25);
				item->SetYScale(item->GetYScale() * 0.25);
				
				// add node to element node
				mNodeLevelPart->addChildNode(item);
			}
		}

		// set pointer of this node to prev node
		prevNode = mNodeLevelPart;
	}

	return mRootNodeLevel;
}

// create the models for the light and dark items
void LevelGenerator::initLightSpheres()
{
	// create model light
	mLightSphere = new Model(SceneData::GetInstance()->GetDevice(), SceneData::GetInstance()->GetImmediateContext());
	// load textrue for model light
	D3DX11CreateShaderResourceViewFromFile(SceneData::GetInstance()->GetDevice(), "assets/white.jpg", NULL, NULL, &mTextureLight, NULL);
	mLightSphere->LoadObjModel("assets/sphere.obj", mTextureLight);

	// create model dark
	mDarkSphere = new Model(SceneData::GetInstance()->GetDevice(), SceneData::GetInstance()->GetImmediateContext());
	// load textrue for model dark
	D3DX11CreateShaderResourceViewFromFile(SceneData::GetInstance()->GetDevice(), "assets/black.jpg", NULL, NULL, &mTextureDark, NULL);
	mDarkSphere->LoadObjModel("assets/sphere.obj", mTextureDark);
}

// getter & setter
Seed* LevelGenerator::GetSeed()
{
	return mSeed;
}

void LevelGenerator::SetSeed(Seed* seed)
{
	mSeed = seed;
}

//////////////////////////////////////////////////////////////////////////////////////
// SEED CLASS
//////////////////////////////////////////////////////////////////////////////////////
// consturcor 1 without parameters
// initialised the seed with default values
Seed::Seed()
{
	mScaleMax = 10;
	mScaleMin = 5;
	mSpanMax = 5;
	mSpanMin = 1;
	mYPosMax = 5;
	mYPosMin = 1;
	mLevelElements = 10;
	mBlocks = new vector<int>();
}

// constructor 2 with the values for the seed
Seed::Seed(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin, int levelElements, vector<int>* blocks)
{
	mScaleMax = 2;
	mScaleMin = 1;
	mSpanMax = 1;
	mSpanMin = 0;
	mYPosMax = 1;
	mYPosMin = 0;

	SetScaleMax(scaleMax);
	SetScaleMin(scaleMin);
	SetSpanMax(spanMax);
	SetSpanMin(spanMin);
	SetYPosMax(yPosMax);
	SetYPosMin(yPosMin);
	SetLevelElements(levelElements);
	SetBlockIDs(blocks);
}

// destructor
Seed::~Seed()
{
	if(mBlocks) delete mBlocks;
}

// getter & setter
void Seed::SetScaleMax(int val)
{
	if (val > mScaleMin)
		mScaleMax = val;
}

void Seed::SetScaleMin(int val)
{
	if (mScaleMin < 1)
		mScaleMin = 1;

	if (val < mScaleMax)
		mScaleMin = val;
}

void Seed::SetSpanMax(int val)
{
	if (val > mSpanMin)
		mSpanMax = val;
}

void Seed::SetSpanMin(int val)
{
	if (mSpanMin < 0)
		mSpanMin = 0;

	if (val < mSpanMax)
		mSpanMin = val;
}

void Seed::SetYPosMax(int val)
{
	if (mYPosMax < 0)
		mYPosMax = 0;

	if (val > mYPosMin)
		mYPosMax = val;
}

void Seed::SetYPosMin(int val)
{
	if (mYPosMin < 0)
		mYPosMin = 0;

	if (val < mYPosMax)
		mYPosMin = val;
}

void Seed::SetLevelElements(int val)
{
	if (val > 0)
		mLevelElements = val;
}

void Seed::SetBlockIDs(vector<int>* blocks)
{
	mBlocks = blocks;
}

int Seed::GetScaleMax()
{
	return mScaleMax;
}
int Seed::GetScaleMin()
{
	return mScaleMin;
}
int Seed::GetSpanMax()
{
	return mSpanMax;
}
int Seed::GetSpanMin()
{
	return mSpanMin;
}
int Seed::GetYPosMax()
{
	return mYPosMax;
}
int Seed::GetYPosMin()
{
	return mYPosMin;
}
int Seed::GetLevelElements()
{
	return mLevelElements;
}
vector<int>* Seed::GetBlockIDs()
{
	return mBlocks;
}

