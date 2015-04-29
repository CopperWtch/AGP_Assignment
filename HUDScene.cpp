/**
AGP Assignment
HUDScene.cpp
Purpose: renders the HUD for the game

@author Sarah Bulk
*/
#include "HUDScene.h"

//////////////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////////////
HUDScene::~HUDScene()
{

}


//////////////////////////////////////////////////////////////////////////////////////
// Initialise Scene
//////////////////////////////////////////////////////////////////////////////////////
bool HUDScene::Init()
{
	mSceneData = SceneData::GetInstance();
	mD3DDevice = mSceneData->GetDevice();
	mImmediateContext = mSceneData->GetImmediateContext();
	initHUD();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////
// Render Scene
//////////////////////////////////////////////////////////////////////////////////////
void HUDScene::RenderScene(float dt)
{
	//Display Time
	mTimer->update();
	unsigned long int time = floor(mTimer->GetTotalGameTime());
	std::string text = "Time " + std::to_string(time);
	mHUD->AddText(text, -1.0, +1.0, .1);

	//Display Light/Dark

	int lightAmount = (int)LightManager::GetInstance()->GetAmbientLight()->GetLightRatio();
	text = std::to_string(lightAmount) + "/" + std::to_string(100 - lightAmount);
	mHUD->AddText(text, -1.0, -0.9, .1);

	//Display Score
	//Todo: move the maths somewhere else 
	//		& replace calculation. This one is placeholder 
	score = (unsigned long int)(time * lightAmount / 100);
	text = "Score " + std::to_string(score);
	mHUD->AddText(text, -0.0, +1.0, .1);

	//Render all text
	mHUD->RenderText();

	mRootNodeLevel->execute(&XMMatrixIdentity(), mSceneData->GetView(), mSceneData->GetProjection());
}

void HUDScene::initHUD()
{
	score = 0;
	mTimer = Timer::getInstance();
	mTimer->initialize();

	mHUD = new Text2D("assets/font1C.png", mD3DDevice, mImmediateContext);
	//mSceneData->SetTimeTxt(mHUD);

	mRootNodeLevel = new SceneNode();


}