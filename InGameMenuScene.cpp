#include "InGameMenuScene.h"

InGameMenuScene::~InGameMenuScene()
{

}

bool InGameMenuScene::Init()
{
	mSceneData = SceneData::GetInstance();
	mD3DDevice = mSceneData->GetDevice();
	mImmediateContext = mSceneData->GetImmediateContext();
	initMenu();
	return true;
}


void InGameMenuScene::RenderScene(float dt)
{
	//render background image
	mBackground->Render(mImmediateContext, -1.0, 1.0, 2.0, 2.0);

	//headline
	mTextPause->AddText("PAUSE", -0.5, +0.8, .2);

	//Render everything
	mBtnResume->Display(mImmediateContext, -0.4, +0.0, .6, .2);

	//cant currently work
	//mInput = mSceneData->GetInput();

	//mInput->ReadInputStates();
	//if (mInput->IsMouseClicked())
	//{

	//	//not finalised input , still buggy
	//	if (mBtnResume->IsClicked(mInput->GetMouseData().x, mInput->GetMouseData().y));
	//	{
	//	}

	//}


	mTextPause->RenderText();

	mRootNode->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}

void InGameMenuScene::initMenu()
{

	mTextPause = new Text2D("assets/font1C.png", mD3DDevice, mImmediateContext);

	imgResume = new ImageClass(mD3DDevice, mImmediateContext, "assets/btnResume.png");

	mBtnResume = new Button(imgResume);

	mBackground = new ImageClass(mD3DDevice, mImmediateContext, "assets/bg.png");

	mRootNode = new SceneNode();


}
