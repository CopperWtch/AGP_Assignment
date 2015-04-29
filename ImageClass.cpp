/**
AGP Assignment
ImageClass.cpp
Purpose: Image that can be rendered in the scene

@author Sarah Bulk
*/

#include "ImageClass.h"

//////////////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////////////
ImageClass::~ImageClass()
{
	if (pDepthDisabledStencilState) pDepthDisabledStencilState->Release();
	if (pDepthEnabledStencilState) pDepthEnabledStencilState->Release();
	if (mTexture) mTexture->Release();
	if (pSampler) pSampler->Release();
	if (m_vertexBuffer) m_vertexBuffer->Release();
	if (pVShader) pVShader->Release();
	if (pPShader) pPShader->Release();
	if (pInputLayout) pInputLayout->Release();
}

//////////////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////////////
ImageClass::ImageClass(ID3D11Device* device, ID3D11DeviceContext* context, string filename)
{

	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	HRESULT result;
	int i;


	// Set the number of vertices in the vertex array.
	m_vertexCount = 6;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType)* m_vertexCount));


	// Set up the description of the static vertex buffer.
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;										// Used by CPU and GPU
	bufferDesc.ByteWidth = sizeof(VertexType)* m_vertexCount;					// Total size of buffer,
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;							// Use as a vertex buffer
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;							// Allow CPU access
	HRESULT hr = device->CreateBuffer(&bufferDesc, NULL, &m_vertexBuffer);		// Create the buffer

	if (FAILED(hr)) exit(0);


	// --------SHADERS----------- //
	// Load and compile pixel and vertex shaders
	ID3DBlob *VS, *PS, *error;
	hr = D3DX11CompileFromFile("text2d_shaders.hlsl", 0, 0, "TextVS", "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0)
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))exit(0);
	}

	hr = D3DX11CompileFromFile("text2d_shaders.hlsl", 0, 0, "TextPS", "ps_4_0", 0, 0, 0, &PS, &error, 0);

	if (error != 0)
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr)) exit(0);
	}

	// Create shader objects
	hr = device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVShader);
	if (FAILED(hr)) exit(0);

	hr = device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPShader);
	if (FAILED(hr)) exit(0);

	// Create and set the input layout object
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};

	hr = device->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &pInputLayout);
	if (FAILED(hr)) exit(0);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	// Load in the font texture from given filename
	result = D3DX11CreateShaderResourceViewFromFile(device, filename.c_str(), NULL, NULL, &mTexture, NULL);

	// Create sampler for texture
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&sampler_desc, &pSampler);

	// Create 2 depth stencil states to turn Z buffer on and off
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = device->CreateDepthStencilState(&depthStencilDesc, &pDepthDisabledStencilState);
	if (FAILED(hr)) exit(0);

	depthStencilDesc.DepthEnable = true;
	hr = device->CreateDepthStencilState(&depthStencilDesc, &pDepthEnabledStencilState);
	if (FAILED(hr)) exit(0);

	//Create Blending state for alpha
	D3D11_BLEND_DESC BlendStateDescription;
	ZeroMemory(&BlendStateDescription, sizeof(D3D11_BLEND_DESC));


	BlendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	BlendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	BlendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;


	BlendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	BlendStateDescription.IndependentBlendEnable = FALSE;
	BlendStateDescription.AlphaToCoverageEnable = FALSE;


	device->CreateBlendState(&BlendStateDescription, &pBlendAlphaEnable);

}


void ImageClass::Shutdown()
{
	// Release the bitmap texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}

//////////////////////////////////////////////////////////////////////////////////////
// Display the texture
//////////////////////////////////////////////////////////////////////////////////////
bool ImageClass::Render(ID3D11DeviceContext* deviceContext, float x, float y, float sizeW, float sizeH)
{
	m_vertexCount = 6;

	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;
	int positionX = x;
	int positionY = y;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];

	left = x;
	right = x + sizeW;
	top = y;
	bottom = y - sizeH;

	// create 6 vertices with given size and xy position
	vertices[0].position.x = x;
	vertices[0].position.y = y;
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position.x = x + sizeW;
	vertices[1].position.y = y;
	vertices[1].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[2].position.x = x + sizeW;
	vertices[2].position.y = y - sizeH;
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[3].position.x = x;
	vertices[3].position.y = y;
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position.x = x + sizeW;
	vertices[4].position.y = y - sizeH;
	vertices[4].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[5].position.x = x;
	vertices[5].position.y = y - sizeH;
	vertices[5].texture = D3DXVECTOR2(0.0f, 1.0f);

	// set all z to 1.0 to avoid being clipped
	vertices[0].position.z = 1.0;
	vertices[1].position.z = 1.0;
	vertices[2].position.z = 1.0;
	vertices[3].position.z = 1.0;
	vertices[4].position.z = 1.0;
	vertices[5].position.z = 1.0;

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType)* m_vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);



	// Copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	deviceContext->Map(m_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);	// Lock the buffer to allow writing
	memcpy(ms.pData, vertices, (sizeof(VertexType)* m_vertexCount));				// Copy the data -  only upload those that are used
	deviceContext->Unmap(m_vertexBuffer, NULL);

	// set all rendering states
	deviceContext->PSSetSamplers(0, 1, &pSampler);
	deviceContext->PSSetShaderResources(0, 1, &mTexture);
	deviceContext->VSSetShader(pVShader, 0, 0);
	deviceContext->PSSetShader(pPShader, 0, 0);
	deviceContext->IASetInputLayout(pInputLayout);

	UINT stride = sizeof(POS_TEX_VERTEX);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// turn off Z buffer so text always on top
	deviceContext->OMSetDepthStencilState(pDepthDisabledStencilState, 1);
	//Turn on transparency
	deviceContext->OMSetBlendState(pBlendAlphaEnable, 0, 0xffffffff);

	// draw all added characters
	deviceContext->Draw(6, 0);

	// turn on Z buffer so other rendering can use it
	deviceContext->OMSetDepthStencilState(pDepthEnabledStencilState, 1);
	//Turn off transparency
	deviceContext->OMSetBlendState(pBlendAlphaDisable, 0, 0xffffffff);

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////
// Release components
//////////////////////////////////////////////////////////////////////////////////////
void ImageClass::ShutdownBuffers()
{

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ImageClass::ReleaseTexture()
{
	// Release the texture object.
	if (mTexture)
	{
		delete mTexture;
		mTexture = 0;
	}

	return;
}