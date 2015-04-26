/**
AGP Assignment
GameScene.h
Purpose: Header file for GameScene.cpp

@author Marcel Zobus
*/
#pragma once

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "AGPSideScroller.h"

class GameScene : public Scene
{
public:
	~GameScene();
	virtual bool Init();
	virtual void RenderScene(float dt);
	void ReGenerateLevel();
	CREATE_FUNC(GameScene);
private:
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	ID3D11ShaderResourceView *mTexture;
	SceneData* mSceneData;

	SceneNode* mRootNodeLevel;
	SceneNode* mMovingChild;
	SceneNode* mMovingChild2;

	LevelGenerator* levelGenerator;
	Model* mCube;
	Model* mCube2;

	Light *mLight;
	
	void moveGameObjectUpAndDown(SceneNode* movingChild, float* velocity, bool* updownflag, float maxPos, float dt);
	void initLevel();
	void initMovingChilds(bool isReset);
	void generate();
	void Log(float x);

	bool* mUpDownFlag;
	bool* mUpDownFlag2;
	float* mUpDownVelocity;
	float* mUpDownVelocity2;
	float maxPos = 8;
	float mLevelMoveVelocity = 0.5f;
};


#endif
