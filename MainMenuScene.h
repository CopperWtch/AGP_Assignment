/**
AGP Assignment
MainMenuScene.h
Purpose: Header file for MainMenuScene.cpp

@author Sarah Bulk
*/

#pragma once

#ifndef _MAINMENUSCENE_H_
#define _MAINMENUSCENE_H_

#include "AGPSideScroller.h"
#include "SceneData.h"
#include "Timer.h"
#include "Button.h"
#include "text2D.h"

class MainMenuScene : public Scene
{
public:
	~MainMenuScene();
	virtual bool Init();
	virtual void RenderScene(float dt);
	CREATE_FUNC(MainMenuScene);

	bool GetIsActive();
	void SetIsActive(bool isActive);

private:
	void initMenu();

	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	SceneData* mSceneData;
	Input* mInput;

	ImageClass* mBackground;

	ImageClass* txtStart;
	ImageClass* txtQuit;

	Button* mBtnStart;
	Button* mBtnQuit;

	Text2D* mTextMenu;
	SceneNode* mRootNode;

	bool bIsActive;


};

#endif