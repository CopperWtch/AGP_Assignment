/**
AGP Assignment
Scene.cpp
Purpose: Scene Object which renders everything in this scene

@author Marcel Zobus
*/

#include "Scene.h"

//////////////////////////////////////////////////////////////////////////////////////
// intitialise the scene constructor, destructor and the create method
//////////////////////////////////////////////////////////////////////////////////////

Scene::Scene(ID3D11Device *_d3DDevice, ID3D11DeviceContext *_immediateContext)
{
	mD3DDevice = _d3DDevice;
	mImmediateContext = _immediateContext;
}

Scene::~Scene()
{
	if (mRootNodeCrates) delete mRootNodeCrates;
	if (mCube) delete mCube;
}


void Scene::Create()
{
	createCrates();
}

//////////////////////////////////////////////////////////////////////////////////////
// Render the scene
//////////////////////////////////////////////////////////////////////////////////////
float degrees = 0;
void Scene::RenderScene(XMMATRIX view, XMMATRIX projection)
{
	// draw model
	mRootNodeCrates->SetYAngle(degrees);
	mRootNodeCrates->execute(&XMMatrixIdentity(), &view, &projection);
	mNode1->HideObject(true);
	degrees += 0.01f;
}

//////////////////////////////////////////////////////////////////////////////////////
// Create objects for the scene
//////////////////////////////////////////////////////////////////////////////////////
void Scene::createCrates()
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

