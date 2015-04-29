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

	//Create Light objects & Set them for the model
	mAmbient = new Light();
	mDirectional = new DirectionalLight();

	mPlight1 = new PointLight();
	mPlight1->SetLightPosition(1.0f, 1.0f, 1.0f);
	mPlight1->SetLightColour(0.1f, 0.1f, 0.1f, 0.5f);

	mPlight2 = new PointLight();
	mPlight2->SetLightPosition(1.0f, 1.0f, 1.0f);
	mPlight2->SetLightColour(0.1f, 0.1f, 0.1f, 0.5f);

	mPlight3 = new PointLight();
	mPlight3->SetLightPosition(1.0f, 1.0f, 1.0f);
	mPlight3->SetLightColour(0.1f, 0.1f, 0.1f, 0.5f);

	mPlight4 = new PointLight();
	mPlight4->SetLightPosition(1.0f, 1.0f, 1.0f);
	mPlight4->SetLightColour(0.1f, 0.1f, 0.1f, 0.5f);


	mNode1->SetGameObject(mCube);
	mNode2->SetGameObject(mCube);
	mNode3->SetGameObject(mCube);

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

