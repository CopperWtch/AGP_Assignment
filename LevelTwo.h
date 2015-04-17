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
#include "SceneData.h"

class LevelTwo : public Scene
{
public:
	~LevelTwo();
	virtual bool Init();
	virtual void RenderScene(float dt);
	CREATE_FUNC(LevelTwo);
private:
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	ID3D11ShaderResourceView *mTexture;
	SceneData* mSceneData;

	SceneNode* mRootNodeLevel;

	Light *mLight;
	void initLevel();
};


#endif
