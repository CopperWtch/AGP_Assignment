#include "Model.h"

struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection; //64 bytes
};

Model::Model(ID3D11Device *d3DDevice, ID3D11DeviceContext *immediateContext)
{
	m_pD3DDevice = d3DDevice;
	m_pImmediateContext = immediateContext;
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
	m_xangle = 0.0f;
	m_yangle = 0.0f;
	m_zangle = 0.0f;
	m_scale = 1.0f;
	m_rotation = 0.0f;
}

Model::~Model()
{
	delete m_pObject;
	if (m_pVShader) m_pVShader->Release();
	if (m_pPShader) m_pPShader->Release();
	if (m_pInputLayout) m_pInputLayout->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();
}

int Model::LoadObjModel(char *filename, ID3D11ShaderResourceView *_m_pTexture0)
{
	m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);
	if (m_pObject->filename == "FILE NOT LOADED") return S_FALSE;

	HRESULT hr = S_OK;

	//create constant buffer
	D3D11_BUFFER_DESC constant_buffer_desc;
	ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));
	constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT; //can use UpdateSubresource() to update
	constant_buffer_desc.ByteWidth = 64; //MUST be a multiple of 16, calculate from CB struct
	constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // use as a constant buffer

	hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc, NULL, &m_pConstantBuffer);
	if (FAILED(hr)) return hr;

	//texture 
	m_pTexture0 = _m_pTexture0;

	//sampler
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	m_pD3DDevice->CreateSamplerState(&sampler_desc, &m_pSampler0);

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
	hr = m_pD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVShader);
	if (FAILED(hr))
	{
		return hr;
	}
	hr = m_pD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPShader);
	if (FAILED(hr))
	{
		return hr;
	}

	//Set the shader objects as active 
	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);

	//create and set the input lazout object
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pInputLayout);
	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

}

void Model::Draw(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection){
	
	MODEL_CONSTANT_BUFFER model_cb_values;
	model_cb_values.WorldViewProjection = (*world)*(*view)*(*projection);

	//upload the new values for the constant buffer
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &model_cb_values, 0, 0);

	// set shaders
	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	// sampler
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture0);
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler0);

	m_pObject->Draw();
}

void Model::LookAt_XZ(float x, float z)
{
	m_dx = x - m_x;
	m_dz = z - m_z;
	m_yangle = atan2(m_dx, m_dz);
}

void Model::MoveForward(float distance)
{
	m_x += distance * m_dx;
	m_z += distance * m_dz;
}

void Model::Log(float x){
	AllocConsole();
	HANDLE myConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD cCharsWritten;
	char buffer[1014];
	int n, a = 5, b = 3;
	n = sprintf_s(buffer, " x is %f \n", x);
	string thisString = buffer;
	WriteConsole(myConsoleHandle, thisString.c_str(), thisString.size(), &cCharsWritten, NULL);
}

void Model::SetXPos(float num){ m_x = num; }
void Model::SetYPos(float num){ m_y = num; }
void Model::SetZPos(float num){ m_z = num; }
void Model::SetXAngle(float num){ m_xangle = num; }
void Model::SetYAngle(float num){ m_yangle = num; }
void Model::SetZAngle(float num){ m_zangle = num; }
void Model::SetScale(float num){ m_scale = num; }
void Model::SetRotation(float num){ m_rotation = num; }
float Model::GetXPos(){ return m_x; }
float Model::GetYPos(){ return m_y; }
float Model::GetZPos(){ return m_z; }
float Model::GetXAngle(){ return m_xangle; }
float Model::GetYAngle(){ return m_yangle;  }
float Model::GetZAngle(){ return m_zangle; }
float Model::GetScale(){ return m_scale; }
float Model::GetRotation(){ return m_rotation; }
void Model::IncXPos(float num){ m_x += num; }
void Model::IncYPos(float num){ m_y += num; }
void Model::IncZPos(float num){ m_z += num; }
void Model::IncXAngle(float num){ m_xangle += num; }
void Model::IncYAngle(float num){ m_yangle += num; }
void Model::IncZAngle(float num){ m_zangle += num; }
void Model::IncScale(float num){ m_scale += num; }
void Model::IncRotation(float num){ m_rotation += num; }
void Model::DecXPos(float num){ m_x -= num; }
void Model::DecYPos(float num){ m_y -= num; }
void Model::DecZPos(float num){ m_z -= num; }
void Model::DecXAngle(float num){ m_xangle -= num; }
void Model::DecYAngle(float num){ m_yangle -= num; }
void Model::DecZAngle(float num){ m_zangle -= num; }
void Model::DecScale(float num){ m_scale -= num; }
void Model::DecRotation(float num){ m_rotation -= num; }

