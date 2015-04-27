/**
AGP Assignment
Model.cpp
Purpose: Model Object

@author Marcel Zobus
*/

#include "Model.h"

const int NUM_LIGHTS = 4;

struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection; //64 bytes

	//Light
	XMVECTOR directional_light_vector; //16bytes
	XMVECTOR directional_light_colour; //16bytes
	XMVECTOR ambient_light_colour; //16bytes

	XMVECTOR point_position[NUM_LIGHTS];
	XMVECTOR point_colour[NUM_LIGHTS];
	//XMVECTOR point_light_colour; //16bytes
	//XMVECTOR point_light_position; //16bytes //total: 144 bytes
	//240?
};

Model::Model(ID3D11Device *_d3DDevice, ID3D11DeviceContext *_immediateContext)
{
	mD3DDevice = _d3DDevice;
	mImmediateContext = _immediateContext;
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;
	mXAngle = 0.0f;
	mYAngle = 0.0f;
	mZAngle = 0.0f;
	mScale = 1.0f;
	mRotation = 0.0f;

	mpLight1 = 0;
	mpLight2 = 0;
	mpLight3 = 0;
	mpLight4 = 0;
	mLight = 0;
}

Model::~Model()
{
	if (mObject) delete mObject;
	if (mVShader) mVShader->Release();
	if (mPShader) mPShader->Release();
	if (mInputLayout) mInputLayout->Release();
	if (mConstantBuffer) mConstantBuffer->Release();
	if (mTexture) mTexture->Release();
	if (mSampler) mSampler->Release();

	//if (mLight) delete mLight;
	//if (mpLight1) delete mpLight1;
	//if (mpLight2) delete mpLight2;
	//if (mpLight3) delete mpLight3;
	//if (mpLight4) delete mpLight4;

}

//////////////////////////////////////////////////////////////////////////////////////
// Load OBJ Model
//////////////////////////////////////////////////////////////////////////////////////
int Model::LoadObjModel(char *filename, ID3D11ShaderResourceView *_mTexture0)
{
	mObject = new ObjFileModel(filename, mD3DDevice, mImmediateContext);
	if (mObject->filename == "FILE NOT LOADED") return S_FALSE;

	HRESULT hr = S_OK;

	//create constant buffer
	D3D11_BUFFER_DESC constant_buffer_desc;
	ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));
	constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT; //can use UpdateSubresource() to update
	constant_buffer_desc.ByteWidth = 240; //MUST be a multiple of 16, calculate from CB struct
	constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // use as a constant buffer

	hr = mD3DDevice->CreateBuffer(&constant_buffer_desc, NULL, &mConstantBuffer);
	if (FAILED(hr)) return hr;

	//texture 
	mTexture = _mTexture0;

	//sampler
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	mD3DDevice->CreateSamplerState(&sampler_desc, &mSampler);

	//load and compile pixel and vertex shaders - use  vs_5_0 to target DX11 Hardware only
	ID3DBlob *VS, *PS, *error;
	hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelVS", "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0) //check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr)) //dont fail if error is just a warning
		{
			return hr;
		};
	}

	hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelPS", "ps_4_0", 0, 0, 0, &PS, &error, 0);

	if (error != 0) //check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr)) //dont fail if error is just a warning
		{
			return hr;
		};
	}

	//create shader object
	hr = mD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &mVShader);
	if (FAILED(hr))
	{
		return hr;
	}
	hr = mD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &mPShader);
	if (FAILED(hr))
	{
		return hr;
	}

	//Set the shader objects as active 
	mImmediateContext->VSSetShader(mVShader, 0, 0);
	mImmediateContext->PSSetShader(mPShader, 0, 0);

	//create and set the input lazout object
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = mD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &mInputLayout);
	if (FAILED(hr))
	{
		return hr;
	}

	mImmediateContext->IASetInputLayout(mInputLayout);

}

//////////////////////////////////////////////////////////////////////////////////////
// Draw Model
//////////////////////////////////////////////////////////////////////////////////////
void Model::Draw(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection){
	
	MODEL_CONSTANT_BUFFER model_cb_values;
	model_cb_values.WorldViewProjection = (*world)*(*view)*(*projection);

	//Lighting
	XMMATRIX transpose = XMMatrixTranspose(*world);

	XMVECTOR determinant;
	XMMATRIX inverse;
	inverse = XMMatrixInverse(&determinant, *world);


	if (mLight != nullptr)
	{

		XMVECTOR dirColour = mLight->GetDirectionalLightColour();
		XMVECTOR ambColour = mLight->GetAmbientLightColour();
		XMVECTOR dirVector = mLight->GetLightDirection();

		//XMVECTOR pointColour = mLight->GetPointLightColour();
		//XMVECTOR pointVector = mLight->GetPointLightPosition();

		/*model_cb_values.point_light_colour = pointColour;
		model_cb_values.point_light_position = XMVector3Transform(pointVector, inverse);;*/

		model_cb_values.directional_light_colour = dirColour;
		model_cb_values.ambient_light_colour = ambColour;
		model_cb_values.directional_light_vector = XMVector3Transform(dirVector, transpose);
		model_cb_values.directional_light_vector = XMVector3Normalize(model_cb_values.directional_light_vector);

	}

	if (mpLight1)
	{
		model_cb_values.point_colour[0] = mpLight1->GetPointLightColour();
		model_cb_values.point_position[0] = XMVector3Transform(mpLight1->GetPointLightPosition(), inverse);
	}
	if (mpLight2)
	{
		model_cb_values.point_colour[1] = mpLight2->GetPointLightColour();
		model_cb_values.point_position[1] = XMVector3Transform(mpLight2->GetPointLightPosition(), inverse);
	}
	if (mpLight3)
	{
		model_cb_values.point_colour[2] = mpLight3->GetPointLightColour();
		model_cb_values.point_position[2] = XMVector3Transform(mpLight3->GetPointLightPosition(), inverse);
	}
	if (mpLight4)
	{
		model_cb_values.point_colour[3] = mpLight4->GetPointLightColour();
		model_cb_values.point_position[3] = XMVector3Transform(mpLight4->GetPointLightPosition(), inverse);
	}

	//upload the new values for the constant buffer
	mImmediateContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mImmediateContext->UpdateSubresource(mConstantBuffer, 0, 0, &model_cb_values, 0, 0);

	// set shaders
	mImmediateContext->VSSetShader(mVShader, 0, 0);
	mImmediateContext->PSSetShader(mPShader, 0, 0);
	mImmediateContext->IASetInputLayout(mInputLayout);

	// sampler
	mImmediateContext->PSSetShaderResources(0, 1, &mTexture);
	mImmediateContext->PSSetSamplers(0, 1, &mSampler);

	mObject->Draw();
}

//////////////////////////////////////////////////////////////////////////////////////
// Transform Model
//////////////////////////////////////////////////////////////////////////////////////
void Model::LookAtXZ(float x, float z)
{
	mDX = x - mX;
	mDZ = z - mZ;
	mYAngle = atan2(mDX, mDZ);
}

void Model::MoveForward(float distance)
{
	mX += distance * mDX;
	mZ += distance * mDZ;
}

//////////////////////////////////////////////////////////////////////////////////////
// Getter and Setter
//////////////////////////////////////////////////////////////////////////////////////

// mX, mY, mZ
void Model::SetXPos(float num)
{ 
	mX = num; 
}
void Model::SetYPos(float num)
{ 
	mY = num; 
}
void Model::SetZPos(float num)
{ 
	mZ = num; 
}
float Model::GetXPos()
{
	return mX;
}
float Model::GetYPos()
{
	return mY;
}
float Model::GetZPos()
{
	return mZ;
}

// mXAngle, mYAngle, mZAngle
void Model::SetXAngle(float num)
{ 
	mXAngle = num; 
}
void Model::SetYAngle(float num)
{ 
	mYAngle = num;
}
void Model::SetZAngle(float num)
{ 
	mZAngle = num;
}
float Model::GetXAngle()
{
	return mXAngle;
}
float Model::GetYAngle()
{
	return mYAngle;
}
float Model::GetZAngle()
{
	return mZAngle;
}

// mScale
void Model::SetScale(float num)
{ 
	mScale = num;
}
float Model::GetScale()
{
	return mScale;
}

// mRotation
void Model::SetRotation(float num)
{ 
	mRotation = num; 
}
float Model::GetRotation()
{ 
	return mRotation;
}

// Increase mX, mY, mZ
void Model::IncXPos(float num)
{ 
	mX += num; 
}
void Model::IncYPos(float num)
{ 
	mY += num;
}
void Model::IncZPos(float num)
{ 
	mZ += num;
}
// Decrease mX, mY, mZ
void Model::DecXPos(float num)
{
	mX -= num;
}
void Model::DecYPos(float num)
{
	mY -= num;
}
void Model::DecZPos(float num)
{
	mZ -= num;
}

//  Increase mXAngle, mYAngle, mZAngle
void Model::IncXAngle(float num)
{ 
	mXAngle += num; 
}
void Model::IncYAngle(float num)
{ 
	mYAngle += num;
}
void Model::IncZAngle(float num)
{ 
	mZAngle += num;
}
//  Decrease mXAngle, mYAngle, mZAngle
void Model::DecXAngle(float num)
{ 
	mXAngle -= num; 
}
void Model::DecYAngle(float num)
{ 
	mYAngle -= num;
}
void Model::DecZAngle(float num)
{ 
	mZAngle -= num;
}

// Increase mScale
void Model::IncScale(float num)
{
	mScale += num;
}
// Decrease mScale
void Model::DecScale(float num)
{
	mScale -= num;
}

// Increase mRotation
void Model::IncRotation(float num)
{
	mRotation += num;
}
// Decrease mRotation
void Model::DecRotation(float num)
{ 
	mRotation -= num; 
}

//Set General Light Light
void Model::SetLightData(Light* lightObject)
{
	mLight = lightObject;
}

void Model::SetPointLights(PointLight* light1, PointLight* light2, PointLight* light3, PointLight* light4)
{
	if (!mpLight1)
		mpLight1 = light1;
	if (!mpLight2)
		mpLight2 = light2;
	if (!mpLight3)
		mpLight3 = light3;
	if (!mpLight4)
		mpLight4 = light4;

}

