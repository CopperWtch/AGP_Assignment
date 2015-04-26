/**
AGP Assignment
LevelTwo.h
Purpose: Header file for LevelTwo.cpp

@author Marcel Zobus
*/
#pragma once

#ifndef _LEVELTWO_H_
#define _LEVELTWO_H_

#include "AGPSideScroller.h"

class LevelTwo : public Scene
{
public:
	~LevelTwo();
	virtual bool Init();
	virtual void RenderScene(float dt);
	void ReGenerateLevel();
	CREATE_FUNC(LevelTwo);
private:
	void generate();
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	ID3D11ShaderResourceView *mTexture;
	SceneData* mSceneData;

	SceneNode* mRootNodeLevel;
	LevelGenerator* levelGenerator;
	Model* mCube;

	Light *mLight;
	void initLevel();

	float mLevelMoveVelocity = 0.5f;

	SceneNode* mMovingChild;
	SceneNode* mMovingChild2;
	void moveGameObjectUpAndDown(SceneNode* movingChild, float* velocity, bool* updownflag, float maxPos, float minPos, float dt);
	void initMovingChilds(bool isReset);

	bool* mUpDownFlag;
	float* mUpDownVelocity;
	float maxPos;
	float minPos;
	bool* mUpDownFlag2;
	float* mUpDownVelocity2;
	float maxPos2;
	float minPos2;

};


#endif
