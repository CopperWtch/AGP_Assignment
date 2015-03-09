/**
AGP Assignment
Scene.h
Purpose: Header file for Scene.cpp

@author Marcel Zobus
*/

#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

#include "SceneNode.h"
#include "Model.h"

class Scene
{
public:
	Scene(ID3D11Device *_d3DDevice, ID3D11DeviceContext *_immediateContext);
	Scene::~Scene();
	void Create();
	void RenderScene(XMMATRIX view, XMMATRIX projection);

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
};