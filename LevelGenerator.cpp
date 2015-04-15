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
	mSeed = new Seed(10, 5, 5, 1, 5, 1);
}

LevelGenerator::LevelGenerator(Seed* seed)
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = seed;
}

LevelGenerator::LevelGenerator(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin)
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = new Seed(scaleMax, scaleMin, spanMax, spanMin, yPosMax, yPosMin);
}

LevelGenerator::~LevelGenerator()
{

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
	for (int i = 0; i < 10; i++)
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
		float scale = (int)agpRandom->GetRandomRange(mSeed->GetScaleMax(), mSeed->GetScaleMin());
		mNodeLevelPart->SetXScale(scale);
		mNodeLevelPart->SetZScale(scale);

		// random span between the blocks
		span = agpRandom->GetRandomRange(mSeed->GetSpanMax(), mSeed->GetSpanMin());
		// xpos calculation 
		mNodeLevelPart->SetXPos(prevNode->GetXPos() + prevNode->GetXScale() + scale + span);

		// random ypos
		float ypos = agpRandom->GetRandomRange(mSeed->GetYPosMax(), mSeed->GetYPosMin());
		// random value between 0.999 and 0 
		float val = agpRandom->GetRandom0To1();
		// if <= 0.5 then normal ypos value else the value is minus
		if (val <= 0.5f)
			mNodeLevelPart->SetYPos(ypos);
		else
			mNodeLevelPart->SetYPos(ypos * -1);

		// set fix positions for the first block
		if (i == 0)
		{
			mNodeLevelPart->SetXPos(0);
			mNodeLevelPart->SetYPos(0);
		}

		// set pointer of this node to prev node
		prevNode = mNodeLevelPart;
	}

	return mRootNodeLevel;
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
}

Seed::Seed(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin)
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

