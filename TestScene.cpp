/**
AGP Assignment
Scene.cpp
Purpose: Scene Object which renders everything in this scene

@author Marcel Zobus
*/

#include "TestScene.h"


//////////////////////////////////////////////////////////////////////////////////////
// intitialise the scene constructor, destructor and the create method
//////////////////////////////////////////////////////////////////////////////////////

TestScene::~TestScene()
{
	if (mRootNodeCrates) delete mRootNodeCrates;
	if (mNode1) delete mNode1;
	if (mNode2) delete mNode2;
	if (mNode3) delete mNode3;
	if (mCube) delete mCube;
}

bool TestScene::Init() 
{
	data = SceneData::GetInstance();
	mD3DDevice = data->GetDevice();
	mImmediateContext = data->GetImmediateContext();
	createCrates();
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////
// Render the scene
//////////////////////////////////////////////////////////////////////////////////////
float degrees = 0;
void TestScene::RenderScene()
{
	 //draw model
	mRootNodeCrates->SetYAngle(degrees);
	mRootNodeCrates->execute(&XMMatrixIdentity(), data->GetView(), data->GetProjection());
	mNode1->HideObject(true);
	degrees += 0.01f;
}

//////////////////////////////////////////////////////////////////////////////////////
// Create objects for the scene
//////////////////////////////////////////////////////////////////////////////////////
void TestScene::createCrates()
{
	mRootNodeCrates = new SceneNode();
	mNode1 = new SceneNode();
	mNode2 = new SceneNode();
	mNode3 = new SceneNode();

	mCube = new Model(mD3DDevice, mImmediateContext);

	mNode1->SetModel(mCube);
	mNode2->SetModel(mCube);
	mNode3->SetModel(mCube);

	mRootNodeCrates->addChildNode(mNode1);
	mNode1->addChildNode(mNode2);
	mNode2->addChildNode(mNode3);

	mNode2->SetXPos(5);
	mNode3->SetXPos(6);
	mNode3->SetYPos(1);

	//textrue
	D3DX11CreateShaderResourceViewFromFile(mD3DDevice, "assets/crate002.jpg", NULL, NULL, &mTexture0, NULL);

	mCube->LoadObjModel("cube.obj", mTexture0);
}

