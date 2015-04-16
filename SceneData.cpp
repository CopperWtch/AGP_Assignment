/**
AGP Assignment
SceneData.cpp
Purpose: 

@author Marcel Zobus
*/

#include "SceneData.h"


static SceneData* dataInstance = NULL;
SceneData::SceneData()
{

}

SceneData::~SceneData()
{

}

SceneData* SceneData::GetInstance()
{
	if (dataInstance == NULL)
	{
		dataInstance = new SceneData();
	}
	return dataInstance;
}

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
Light* SceneData::GetLight()
{
	return mLight;
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
void SceneData::SetLight(Light* light)
{
	mLight = light;
}

