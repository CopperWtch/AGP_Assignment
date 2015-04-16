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
#include "SceneData.h"

class GameScene : public Scene
{
public:
	~GameScene();
	virtual bool Init();
	virtual void RenderScene();
	CREATE_FUNC(GameScene);
private:
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	ID3D11ShaderResourceView *mTexture;
	SceneData* mSceneData;

	Model* mPlayerModel;
	SceneNode* mRootNodePlayer;
	SceneNode* mRootNodeLevel;

	Light *mLight;
	PointLight* mPlight1;
	PointLight* mPlight2;
	PointLight* mPlight3;
	PointLight* mPlight4;

	void initPlayer();
	void initLevel();

	void Log(float x);
};


#endif
