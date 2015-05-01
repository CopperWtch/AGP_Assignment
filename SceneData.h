/**
AGP Assignment
SceneManager.h
Purpose: Header file for SceneManager.cpp

@author Marcel Zobus
*/
#pragma once

#ifndef _SCENEDATA_H_
#define _SCENEDATA_H_

#include "AGPSideScroller.h"

class SceneData
{
public:
	static SceneData* GetInstance();
	Camera* GetCamera();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetImmediateContext();
	XMMATRIX* GetProjection();
	XMMATRIX* GetView();
	Input * GetInput();
	void SetCamera(Camera* camera);
	void SetDevice(ID3D11Device* device);
	void SetImmediateContext(ID3D11DeviceContext* context);
	void SetProjection(XMMATRIX* projection);
	void SetView(XMMATRIX* view);
	void SetInput(Input* input);
private:
	SceneData();
	Camera* mCamera;
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	XMMATRIX* mProjection;
	XMMATRIX* mView;
	Input *mInput;
	
};

#endif