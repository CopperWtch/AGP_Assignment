/**
AGP Assignment
PatricleGenerator.cpp
Purpose: Generate Particles

@author Marcel Zobus
*/
#include "ParticleGenerator.h"

struct PARTICLE_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection; //64 bytes
	XMFLOAT4 Color; //16 bytes
};




ParticleGenerator::ParticleGenerator(ID3D11Device *_d3DDevice, ID3D11DeviceContext *_immediateContext)
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
	VERTCOUNT = 6;
	for (int i = 0; i < 100; i++)
	{
		mFree.push_back(new Particle());
	}
	mTimePrevious = float(timeGetTime());
	mUntilParticle = 2.0f;
	
}



ParticleGenerator::~ParticleGenerator()
{
	for (int i = 0; i < mFree.size(); i++)
	{
		//delete mFree[i];
	}
	if (mVShader) mVShader->Release();
	if (mPShader) mPShader->Release();
	if (mInputLayout) mInputLayout->Release();
	if (mConstantBuffer) mConstantBuffer->Release();
	if (mTexture) mTexture->Release();
}

//////////////////////////////////////////////////////////////////////////////////////
// Initialise Generator
//////////////////////////////////////////////////////////////////////////////////////

void ParticleGenerator::InitialiseGenerator()
{
	XMFLOAT3 vertices[]
	{
		XMFLOAT3(-1.0f, -1.0f, 0.0f),
		XMFLOAT3(1.0f, 1.0f, 0.0f),
		XMFLOAT3(-1.0f, 1.0f, 0.0f),
		XMFLOAT3(-1.0f, -1.0f, 0.0f),
		XMFLOAT3(1.0f, -1.0f, 0.0f),
		XMFLOAT3(1.0f, 1.0f, 0.0f)
	};

	HRESULT hr = S_OK;

	//create constant buffer
	D3D11_BUFFER_DESC constant_buffer_desc;
	ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));
	constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT; //can use UpdateSubresource() to update
	constant_buffer_desc.ByteWidth = 80; //MUST be a multiple of 16, calculate from CB struct
	constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // use as a constant buffer

	hr = mD3DDevice->CreateBuffer(&constant_buffer_desc, NULL, &mConstantBuffer);
	if (FAILED(hr)) return;

	// create vertex buffer
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC; // used by cpu and gpu
	bufferDesc.ByteWidth = sizeof(XMFLOAT3)* VERTCOUNT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //edit from cpu side
	hr = mD3DDevice->CreateBuffer(&bufferDesc, NULL, &mVertexBuffer);

	if (FAILED(hr))
		return;

	// copy vertices into buffer
	D3D11_MAPPED_SUBRESOURCE ms;

	// mapping = locking buffer, allows writing
	mImmediateContext->Map(mVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertices, sizeof(vertices)); //copy the data
	// unmap = unlock the buffer	
	mImmediateContext->Unmap(mVertexBuffer, NULL);


	//texture 
//	mTexture = _mTexture0;

	//load and compile pixel and vertex shaders - use  vs_5_0 to target DX11 Hardware only
	ID3DBlob *VS, *PS, *error;
	hr = D3DX11CompileFromFile("particle.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0) //check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr)) //dont fail if error is just a warning
		{
			return;
		};
	}

	hr = D3DX11CompileFromFile("particle.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, &error, 0);

	if (error != 0) //check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr)) //dont fail if error is just a warning
		{
			return;
		};
	}

	//create shader object
	hr = mD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &mVShader);
	if (FAILED(hr))
	{
		return;
	}
	hr = mD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &mPShader);
	if (FAILED(hr))
	{
		return;
	}

	//Set the shader objects as active 
	mImmediateContext->VSSetShader(mVShader, 0, 0);
	mImmediateContext->PSSetShader(mPShader, 0, 0);

	//create and set the input lazout object
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = mD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &mInputLayout);
	if (FAILED(hr))
	{
		return;
	}

	mImmediateContext->IASetInputLayout(mInputLayout);

}

//////////////////////////////////////////////////////////////////////////////////////
// Draw Model
//////////////////////////////////////////////////////////////////////////////////////
void ParticleGenerator::Draw(XMMATRIX *view, XMMATRIX *projection, XMFLOAT3 cameraposition){
	
	float timeNow = float(timeGetTime());
	float deltaTime = (timeNow - mTimePrevious) / 1000;
	mTimePrevious = timeNow;

	mUntilParticle -= deltaTime;
	if (mUntilParticle <= 0)
	{
		std::list<Particle*>::iterator it = mFree.begin();

		(*it)->color = XMFLOAT4(0.f, randomZeroToOne(), randomZeroToOne(), 1);
		(*it)->gravity = 1.f;
		(*it)->position = XMFLOAT3(3, -6.f, 12.f);
		(*it)->velocity = XMFLOAT3(randomNegOneToPosOne(), 4.5f, randomNegOneToPosOne());

		mActive.push_back(*it);
		mFree.pop_front();

		mUntilParticle = 0.2;
	}

	std::list<Particle*>::iterator it = mActive.begin();
	while (it != mActive.end())
	{
		DrawOne((*it), view, projection, cameraposition);
		it++;
	}
}

void ParticleGenerator::DrawOne(Particle *one, XMMATRIX *view, XMMATRIX *projection, XMFLOAT3 cameraposition)
{
	
	XMMATRIX world;
	
	world *= XMMatrixScaling(0.3f, 0.3f, 0.3f);
	world *= XMMatrixRotationY(1);
	world *= XMMatrixTranslation(one->position.x, one->position.y, one->position.z);

	PARTICLE_CONSTANT_BUFFER particle_cb_values;
	particle_cb_values.WorldViewProjection = (world)*(*view)*(*projection);
	particle_cb_values.Color = one->color;

	//upload the new values for the constant buffer
	mImmediateContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mImmediateContext->UpdateSubresource(mConstantBuffer, 0, 0, &particle_cb_values, 0, 0);

	// set shaders
	mImmediateContext->VSSetShader(mVShader, 0, 0);
	mImmediateContext->PSSetShader(mPShader, 0, 0);
	mImmediateContext->IASetInputLayout(mInputLayout);

	UINT stride = sizeof(XMFLOAT3);
	UINT offset = 0;
	mImmediateContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	mImmediateContext->Draw(VERTCOUNT, 0);
}

float ParticleGenerator::randomNegOneToPosOne()
{
	return ((float(rand()) / float(RAND_MAX)) * (1 - -1)) + -1;
}

float ParticleGenerator::randomZeroToOne()
{
	return ((float)rand() / (RAND_MAX));
}

//////////////////////////////////////////////////////////////////////////////////////
// Transform Model
//////////////////////////////////////////////////////////////////////////////////////
void ParticleGenerator::LookAtXZ(float x, float z)
{
	mDX = x - mX;
	mDZ = z - mZ;
	mYAngle = atan2(mDX, mDZ);
}

void ParticleGenerator::MoveForward(float distance)
{
	mX += distance * mDX;
	mZ += distance * mDZ;
}

//////////////////////////////////////////////////////////////////////////////////////
// Getter and Setter
//////////////////////////////////////////////////////////////////////////////////////

// mX, mY, mZ
void ParticleGenerator::SetXPos(float num)
{ 
	mX = num; 
}
void ParticleGenerator::SetYPos(float num)
{ 
	mY = num; 
}
void ParticleGenerator::SetZPos(float num)
{ 
	mZ = num; 
}
float ParticleGenerator::GetXPos()
{
	return mX;
}
float ParticleGenerator::GetYPos()
{
	return mY;
}
float ParticleGenerator::GetZPos()
{
	return mZ;
}

// mXAngle, mYAngle, mZAngle
void ParticleGenerator::SetXAngle(float num)
{ 
	mXAngle = num; 
}
void ParticleGenerator::SetYAngle(float num)
{ 
	mYAngle = num;
}
void ParticleGenerator::SetZAngle(float num)
{ 
	mZAngle = num;
}
float ParticleGenerator::GetXAngle()
{
	return mXAngle;
}
float ParticleGenerator::GetYAngle()
{
	return mYAngle;
}
float ParticleGenerator::GetZAngle()
{
	return mZAngle;
}

// mScale
void ParticleGenerator::SetScale(float num)
{ 
	mScale = num;
}
float ParticleGenerator::GetScale()
{
	return mScale;
}

// mRotation
void ParticleGenerator::SetRotation(float num)
{ 
	mRotation = num; 
}
float ParticleGenerator::GetRotation()
{ 
	return mRotation;
}

// Increase mX, mY, mZ
void ParticleGenerator::IncXPos(float num)
{ 
	mX += num; 
}
void ParticleGenerator::IncYPos(float num)
{ 
	mY += num;
}
void ParticleGenerator::IncZPos(float num)
{ 
	mZ += num;
}
// Decrease mX, mY, mZ
void ParticleGenerator::DecXPos(float num)
{
	mX -= num;
}
void ParticleGenerator::DecYPos(float num)
{
	mY -= num;
}
void ParticleGenerator::DecZPos(float num)
{
	mZ -= num;
}

//  Increase mXAngle, mYAngle, mZAngle
void ParticleGenerator::IncXAngle(float num)
{ 
	mXAngle += num; 
}
void ParticleGenerator::IncYAngle(float num)
{ 
	mYAngle += num;
}
void ParticleGenerator::IncZAngle(float num)
{ 
	mZAngle += num;
}
//  Decrease mXAngle, mYAngle, mZAngle
void ParticleGenerator::DecXAngle(float num)
{ 
	mXAngle -= num; 
}
void ParticleGenerator::DecYAngle(float num)
{ 
	mYAngle -= num;
}
void ParticleGenerator::DecZAngle(float num)
{ 
	mZAngle -= num;
}

// Increase mScale
void ParticleGenerator::IncScale(float num)
{
	mScale += num;
}
// Decrease mScale
void ParticleGenerator::DecScale(float num)
{
	mScale -= num;
}

// Increase mRotation
void ParticleGenerator::IncRotation(float num)
{
	mRotation += num;
}
// Decrease mRotation
void ParticleGenerator::DecRotation(float num)
{ 
	mRotation -= num; 
}

