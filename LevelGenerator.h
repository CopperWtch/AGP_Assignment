/**
AGP Assignment
LevelGenerator.h
Purpose: Header file for LevelGenerator.cpp

@author Marcel Zobus
*/
#pragma once

#ifndef _LEVELGENERATOR_H_
#define _LEVELGENERATOR_H_

#include "AGPRandom.h";
#include "SceneNode.h"
#include "Model.h"
#include "SceneData.h"

class Seed
{
public:
	Seed();
	Seed(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin, int levelElements, vector<int>* blocks);
	void SetScaleMax(int val);
	void SetScaleMin(int val);
	void SetSpanMax(int val);
	void SetSpanMin(int val);
	void SetYPosMax(int val);
	void SetYPosMin(int val);
	void SetLevelElements(int val);
	void SetBlockIDs(vector<int>* blocks);
	int GetScaleMax();
	int GetScaleMin();
	int GetSpanMax();
	int GetSpanMin();
	int GetYPosMax();
	int GetYPosMin();
	int GetLevelElements();
	vector<int>* GetBlockIDs();
private:
	int mScaleMax;
	int mScaleMin;
	int mSpanMax;
	int mSpanMin;
	int mYPosMax;
	int mYPosMin;
	int mLevelElements;
	vector<int>* mBlocks;
};


class LevelGenerator
{
public:
	LevelGenerator();
	LevelGenerator(Seed* seed);
	LevelGenerator(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin, int levelElements, vector<int>* blocks);
	~LevelGenerator();
	SceneNode* Generate(Model* model);
	SceneNode* Generate(Model* modelA, Model* modelB);

	Seed* GetSeed();
	void SetSeed(Seed* seed);
private:
	void initLightSpheres();
	SceneNode* generateLevel();
	Model* mLightSphere;
	Model* mDarkSphere;
	ID3D11ShaderResourceView *mTextureLight;
	ID3D11ShaderResourceView *mTextureDark;
	AGPRandom* agpRandom;
	Seed* mSeed;
	Model* mModelA;
	Model* mModelB;
	bool isMultipleModel;
};



#endif