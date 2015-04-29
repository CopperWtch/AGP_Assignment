/**
AGP Assignment
MainMenuScene.h
Purpose: Header file for MainMenuScene.cpp

@author Sarah Bulk
*/

#pragma once

#ifndef _GAMEOVERSCENE_H_
#define _GAMEOVERSCENE_H_

#include "AGPSideScroller.h"
#include "SceneData.h"
#include "Timer.h"
#include "text2D.h"

class GameOverScene : public Scene
{
public:
	~GameOverScene();
	virtual bool Init();
	virtual void RenderScene(float dt);
	CREATE_FUNC(GameOverScene);

	bool GetIsActive();
	void SetIsActive(bool isActive);

private:
	void initMenu();

	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	SceneData* mSceneData;

	SceneNode* mRootNode;
	Text2D* mTextGameOver;

};

#endif