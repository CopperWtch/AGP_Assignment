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

class Seed
{
public:
	Seed();
	Seed(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin, int levelElements);
	void SetScaleMax(int val);
	void SetScaleMin(int val);
	void SetSpanMax(int val);
	void SetSpanMin(int val);
	void SetYPosMax(int val);
	void SetYPosMin(int val);
	void SetLevelElements(int val);
	int GetScaleMax();
	int GetScaleMin();
	int GetSpanMax();
	int GetSpanMin();
	int GetYPosMax();
	int GetYPosMin();
	int GetLevelElements();
private:
	int mScaleMax;
	int mScaleMin;
	int mSpanMax;
	int mSpanMin;
	int mYPosMax;
	int mYPosMin;
	int mLevelElements;
};


class LevelGenerator
{
public:
	LevelGenerator();
	LevelGenerator(Seed* seed);
	LevelGenerator(int scaleMax, int scaleMin, int spanMax, int spanMin, int yPosMax, int yPosMin, int levelElements);
	~LevelGenerator();
	SceneNode* Generate(Model* model);
	SceneNode* Generate(Model* modelA, Model* modelB);

	Seed* GetSeed();
	void SetSeed(Seed* seed);
private:
	AGPRandom* agpRandom;
	Seed* mSeed;
	SceneNode* generateLevel();
	Model* mModelA;
	Model* mModelB;
	bool isMultipleModel;
};



#endif