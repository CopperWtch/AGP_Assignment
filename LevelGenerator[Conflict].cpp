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
}

LevelGenerator::LevelGenerator(Seed seed)
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = seed;
}

LevelGenerator::LevelGenerator(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin)
{
	agpRandom = AGPRandom::GetInstance();
	mSeed = new Seed();
	mSeed.ScaleMax = scaleMax;
	mSeed.ScaleMin = scaleMin;
	mSeed.SpanMax = spanMax;
	mSeed.SpanMin = spanMin;
	mSeed.YPosMax = yPosMax;
	mSeed.YPosMin = yPosMin;
}

LevelGenerator::~LevelGenerator()
{

}

SceneNode* LevelGenerator::Generate(Model* model)
{
	SceneNode* mRootNodeLevel = new SceneNode();

	SceneNode* prevNode = mRootNodeLevel;
	float span = 1.5f;
	for (int i = 0; i < 10; i++)
	{
		SceneNode* mNodeLevelPart = new SceneNode();
		mNodeLevelPart->SetGameObject(model);
		mRootNodeLevel->addChildNode(mNodeLevelPart);

		// random scale
		float scale = (rand() % 5) + 5;
		mNodeLevelPart->SetXScale(scale);
		mNodeLevelPart->SetZScale(scale);


		// random span between the blocks
		span = agpRandom->GetRandomRange(5, 1);
		// xpos calculation 
		mNodeLevelPart->SetXPos(prevNode->GetXPos() + prevNode->GetXScale() + scale + span);

		// random ypos
		float ypos = agpRandom->GetRandomRange(5, 1);
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

LevelGenerator::Seed LevelGenerator::GetSeed()
{
	return mSeed;
}

void LevelGenerator::SetSeed(Seed seed)
{
	mSeed = seed;
}

void LevelGenerator::SetSeedScaleMax(int val)
{
	mSeed.ScaleMax = val;
	
}

void LevelGenerator::SetSeedScaleMin(int val)
{
	mSeed.ScaleMin = val;
	
}

void LevelGenerator::SetSeedSpanMax(int val)
{
	mSeed.SpanMax = val;
	
}

void LevelGenerator::SetSeedSpanMin(int val)
{
	mSeed.SpanMin = val;

}

void LevelGenerator::LevelGenerator::SetSeedYPosMax(int val)
{
	mSeed.YPosMax = val;
	
}

void LevelGenerator::SetSeedYPosMin(int val)
{
	mSeed.YPosMin = val;
}

