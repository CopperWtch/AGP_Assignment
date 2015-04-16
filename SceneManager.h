/**
AGP Assignment
SceneManager.h
Purpose: Header file for SceneManager.cpp

@author Marcel Zobus
*/

#pragma once

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_


#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

#include "D3DManager.h"
#include "TestScene.h"
#include "GameScene.h"
#include "Player.h"


class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void Initialise(HWND _hWnd, HINSTANCE _hInst);
	void ShutDown3D();
	void RenderFrame(float dt);
	void Log(float x);

private: 
	void initPlayer();
	SceneNode* mRootNodePlayer;
	Light* mLight;
	HRESULT initialiseGraphics();
	D3DManager *mD3DManager;
	Camera *mCamera;
	Input *mInput;
	ParticleGenerator *mParticle;
	HWND mHWnd;
	HINSTANCE mHInst;
	IDXGISwapChain* mSwapChain;
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	ID3D11RenderTargetView* mBackBufferRTView;
	ID3D11DepthStencilView* mZBuffer;
	XMMATRIX mProjection;
	XMMATRIX mView;
	SceneData* data;
	TestScene *mScene;
	GameScene *mGameScene;
	Player* mPlayer;
	ID3D11ShaderResourceView* mTexture;
};

#endif