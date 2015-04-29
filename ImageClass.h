/**
AGP Assignment
GameSprite.h
Purpose: Header file for ImageClass.cpp

@author Sarah Bulk
*/

#pragma once
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#ifndef _GAMESPRITE_H_
#define _GAMESPRITE_H_

#include "GameObject.h"
#include "AGPSideScroller.h"
#include <string>
#include <d3d11.h>
#include <d3dx10math.h>

// Define vertex structure
struct POS_TEX_VERTEX
{
	XMFLOAT3 Pos;
	XMFLOAT2 Texture;
};

//Define vertex type
struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
};

class ImageClass
{
public:
	ImageClass(ID3D11Device* device, ID3D11DeviceContext* context, string filename);
	~ImageClass();

	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, float x, float y, float sizeW, float sizeH);

	float GetLeft(){ return left; };
	float GetRight(){ return right; };
	float GetTop(){ return top; };
	float GetBottom(){ return bottom; };

private:


	void ShutdownBuffers();
	void ReleaseTexture();

	ID3D11Buffer *m_vertexBuffer;
	ID3D11ShaderResourceView*	mTexture;

	ID3D11VertexShader*		pVShader;
	ID3D11PixelShader*		pPShader;
	ID3D11InputLayout*		pInputLayout;
	ID3D11SamplerState*		pSampler;

	float left, right, top, bottom;

	ID3D11DepthStencilState* pDepthEnabledStencilState;		// state to turn on Z buffer
	ID3D11DepthStencilState* pDepthDisabledStencilState;	// state to turn off Z buffer
	ID3D11BlendState*		 pBlendAlphaEnable;				//state to turn on transparency
	ID3D11BlendState*		 pBlendAlphaDisable;			//state to turn off transparency

	VertexType* vertices;

	int m_vertexCount;
};


#endif