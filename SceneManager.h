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
#include "GameScene.h"
#include "LevelTwo.h"
#include "Player.h"
#include "HUDScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "InGameMenuScene.h"


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
	HRESULT initialiseGraphics();
	void initPlayer();
	void killPlayer();
	void nextLevelSetting();
	void nextLevel();
	void renderScenes(float dt);
	void resetGame();

	HWND mHWnd;
	HINSTANCE mHInst;
	IDXGISwapChain* mSwapChain;
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	ID3D11RenderTargetView* mBackBufferRTView;
	ID3D11DepthStencilView* mZBuffer;
	ID3D11ShaderResourceView* mTexture;
	XMMATRIX mProjection;
	XMMATRIX mView;
	
	//player
	SceneNode* mRootNodePlayer;
	Player* mPlayer;
	enum PlayerState { Alive, Dead };
	PlayerState mActivePlayerState;
	//level
	enum SceneState { Level1, Level2, MenuStart, MenuInGame, MenuDead };
	SceneState mActiveSceneState;
	SceneState mPreviousSceneState;
	int mLevelCounter;
	bool mNextLevel;
	//scene
	Light *mAmbientLight;
	DirectionalLight* mDirectionalLight;
	PointLight* mPointLight;
	D3DManager* mD3DManager;
	Camera* mCamera;
	Input* mInput;
	SceneData* data;
	// level scenes
	GameScene* mGameScene;
	LevelTwo* mLevelTwo;

	//UI scenes
	HUDScene* mHUD;
	MainMenuScene* mMainMenu;
	GameOverScene* mGameOver;
	InGameMenuScene* mInGameMenu;

	// render variables
	float mMovementVelociy;
	// render variables - jump
	float positionY;
	float velocityY;    
	float gravity;
	// render variables - input flags
	bool isJump;
	bool isDoubleJump;
	bool isNextLevelDebugKey;
	bool isDieDebugKey;
	bool isResetKey;
	bool isMenuKey;
};

#endif