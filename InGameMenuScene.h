#pragma once

#ifndef _INGAMEMENUSCENE_H_
#define _INGAMEMENUSCENE_H_

#include "AGPSideScroller.h"
#include "Button.h"
#include "text2D.h"

class InGameMenuScene : public Scene
{
public:
	~InGameMenuScene();
	virtual bool Init();
	virtual void RenderScene(float dt);
	CREATE_FUNC(InGameMenuScene);

private:
	void initMenu();

	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mImmediateContext;
	SceneData* mSceneData;
	Input* mInput;

	ImageClass* mBackground;

	ImageClass* imgResume;

	Button* mBtnResume;

	Text2D* mTextPause;
	SceneNode* mRootNode;
};

#endif