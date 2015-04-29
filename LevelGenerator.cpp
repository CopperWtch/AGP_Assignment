/**
AGP Assignment
LevelGenerator.cpp
Purpose: Generates the Levels

@author Marcel Zobus
*/

#include "LevelGenerator.h"

LevelGenerator::LevelGenerator()
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = new Seed(10, 5, 5, 1, 5, 1, 10, new vector<int>());
	initLightSpheres();
}

LevelGenerator::LevelGenerator(Seed* seed)
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = seed;
	initLightSpheres();
}

LevelGenerator::LevelGenerator(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin, int levelElements, vector<int>* blocks)
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = new Seed(scaleMax, scaleMin, spanMax, spanMin, yPosMax, yPosMin, levelElements, blocks);
	initLightSpheres();
}

LevelGenerator::~LevelGenerator()
{
	if (mSeed) delete mSeed;
}

SceneNode* LevelGenerator::Generate(Model* modelA)
{
	mModelA = modelA;
	isMultipleModel = false;
	return generateLevel();
}

SceneNode* LevelGenerator::Generate(Model* modelA, Model* modelB)
{
	mModelA = modelA;
	mModelB = modelB;
	isMultipleModel = true;
	return generateLevel();
}


SceneNode* LevelGenerator::generateLevel()
{
	SceneNode* mRootNodeLevel = new SceneNode();

	SceneNode* prevNode = mRootNodeLevel;
	float span = 1.5f;
	for (int i = 0; i < mSeed->GetLevelElements(); i++)
	{
		SceneNode* mNodeLevelPart = new SceneNode();
		if (isMultipleModel)
		{
			float val = agpRandom->GetRandom0To1();
			// if <= 0.5 then normal ypos value else the value is minus
			if (val <= 0.5f)
				mNodeLevelPart->SetGameObject(mModelA);
			else
				mNodeLevelPart->SetGameObject(mModelB);
		}
		else
		{
			mNodeLevelPart->SetGameObject(mModelA);
		}

		mRootNodeLevel->addChildNode(mNodeLevelPart);

		// random scale
		float scale = (int)agpRandom->GetRandomRange(mSeed->GetScaleMax() + 1, mSeed->GetScaleMin());
		mNodeLevelPart->SetXScale(scale);
		mNodeLevelPart->SetZScale(scale);

		// random span between the blocks
		span = agpRandom->GetRandomRange(mSeed->GetSpanMax() + 1, mSeed->GetSpanMin());
		// xpos calculation 
		mNodeLevelPart->SetXPos(prevNode->GetXPos() + prevNode->GetXScale() + scale + span);

		// random ypos
		float ypos = agpRandom->GetRandomRange(mSeed->GetYPosMax() + 1, mSeed->GetYPosMin());
		// random value between 0.999 and 0 
		float val = agpRandom->GetRandom0To1();
		// if <= 0.5 then normal ypos value else the value is minus
		if (val <= 0.5f)
			mNodeLevelPart->SetYPos(ypos);
		else
			mNodeLevelPart->SetYPos(ypos * -1);

		// set fix positions for the first block
		if (i == 0) // first element 
		{
			mNodeLevelPart->SetXPos(0);
			mNodeLevelPart->SetYPos(0);
		}
		else // not first element 
		{
			
			SceneNode *item = new SceneNode();
			vector<int>* b = mSeed->GetBlockIDs();
			if (std::find(b->begin(), b->end(), i) != b->end()) // i is in the vector which means a block is created not a sphere
			{
				// Element in vector.
				item->SetGameObject(mModelA);
				item->SetYPos(scale + 2);
				float resettedScale = 1 / scale;
				item->SetYScale(scale);
				mNodeLevelPart->addChildNode(item);
			}
			else // i is not in the vector which means a sphere is created
			{
				// 70% chance for light items
				if (agpRandom->GetRandom0To1() < 0.7f)
					item->SetGameObject(mLightSphere);
				else
					item->SetGameObject(mDarkSphere);
				item->SetYPos(3);
				// reset scale from the parent
				float resettedScale = 1 / scale;
				item->SetXScale(resettedScale * 0.25);
				item->SetZScale(resettedScale * 0.25);
				item->SetYScale(item->GetYScale() * 0.25);
				mNodeLevelPart->addChildNode(item);
			}
		}

		// set pointer of this node to prev node
		prevNode = mNodeLevelPart;
	}

	return mRootNodeLevel;
}

void LevelGenerator::initLightSpheres()
{
	mLightSphere = new Model(SceneData::GetInstance()->GetDevice(), SceneData::GetInstance()->GetImmediateContext());

	//textrue
	D3DX11CreateShaderResourceViewFromFile(SceneData::GetInstance()->GetDevice(), "assets/white.jpg", NULL, NULL, &mTextureLight, NULL);
	mLightSphere->LoadObjModel("assets/sphere.obj", mTextureLight);

	mDarkSphere = new Model(SceneData::GetInstance()->GetDevice(), SceneData::GetInstance()->GetImmediateContext());

	//textrue
	D3DX11CreateShaderResourceViewFromFile(SceneData::GetInstance()->GetDevice(), "assets/black.jpg", NULL, NULL, &mTextureDark, NULL);
	mDarkSphere->LoadObjModel("assets/sphere.obj", mTextureDark);
}


Seed* LevelGenerator::GetSeed()
{
	return mSeed;
}

void LevelGenerator::SetSeed(Seed* seed)
{
	mSeed = seed;
}


/// Seed Class

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

Seed::~Seed()
{
	if(mBlocks) delete mBlocks;
}

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

