/**
AGP Assignment
HUDScene.h
Purpose: Header file for HUDScene.cpp

@author Sarah Bulk
*/

#pragma once

#ifndef _HUDSCENE_H_
#define _HUDSCENE_H_

#include "AGPSideScroller.h"
#include "SceneData.h"
#include "Timer.h"
#include "text2D.h"

class HUDScene : public Scene
{
public:
	~HUDScene();
	virtual bool Init();
	virtual void RenderScene(float dt);
	CREATE_FUNC(HUDScene);
private:
	void initHUD();

	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	SceneData* mSceneData;

	Text2D* mHUD;
	Timer* mTimer;
	unsigned long int score;

	SceneNode* mRootNodeLevel;
};

#endif