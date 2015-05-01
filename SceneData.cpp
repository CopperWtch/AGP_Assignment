/**
AGP Assignment
SceneData.cpp
Purpose: contains a lot of important pointer for the scenes
This includes:
Camera
D3DDevice
ImmediateContext
Projection
View
Input

@author Marcel Zobus
*/

#include "SceneData.h"

// static instance 
static SceneData* dataInstance = NULL;

// constructor
SceneData::SceneData()
{

}

// get instance for the singleton
SceneData* SceneData::GetInstance()
{
	if (dataInstance == NULL)
	{
		dataInstance = new SceneData();
	}
	return dataInstance;
}

// getter and setter

Camera* SceneData::GetCamera()
{
	return mCamera;
}
ID3D11Device* SceneData::GetDevice()
{
	return mD3DDevice;
}
ID3D11DeviceContext* SceneData::GetImmediateContext()
{
	return mImmediateContext;
}
XMMATRIX* SceneData::GetProjection()
{
	return mProjection;
}
XMMATRIX* SceneData::GetView()
{
	return mView;
}
Input* SceneData::GetInput()
{
	return mInput;
}

void SceneData::SetCamera(Camera* camera)
{
	mCamera = camera;
}
void SceneData::SetDevice(ID3D11Device* device)
{
	mD3DDevice = device;
}
void SceneData::SetImmediateContext(ID3D11DeviceContext* context)
{
	mImmediateContext = context;
}
void SceneData::SetProjection(XMMATRIX* projection)
{
	mProjection = projection;
}
void SceneData::SetView(XMMATRIX* view)
{
	mView = view;
}
void SceneData::SetInput(Input* input)
{
	mInput = input;
}