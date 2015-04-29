/**
AGP Assignment
Scene.h
Purpose: Header file for Scene.cpp

@author Marcel Zobus
*/
#pragma once

#ifndef _TESTSCENE_H_
#define _TESTSCENE_H_

#include "AGPSideScroller.h"
#include "SceneData.h"



class TestScene : public Scene
{
public:
	~TestScene();
	virtual bool Init();
	virtual void RenderScene();
	CREATE_FUNC(TestScene);


private:
	ID3D11Device *mD3DDevice;
	ID3D11DeviceContext *mImmediateContext;
	ID3D11ShaderResourceView *mTexture0;
	
	//crates 
	void createCrates();
	Model *mCube;
	SceneNode *mRootNodeCrates;
	SceneNode *mNode1;
	SceneNode *mNode2;
	SceneNode *mNode3;
	SceneData* data;

	Light *mAmbient;
	DirectionalLight *mDirectional;
	PointLight* mPlight1;
	PointLight* mPlight2;
	PointLight* mPlight3;
	PointLight* mPlight4;
};

#endif