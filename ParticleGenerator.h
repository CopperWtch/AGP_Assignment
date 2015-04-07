/**
AGP Assignment
PatricleGenerator.h
Purpose: Header file for PatricleGenerator.cpp

@author Marcel Zobus
*/

#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#include <xnamath.h>
#include <list>


class ParticleGenerator
{
public:
	struct Particle
	{
		float gravity;
		XMFLOAT3 position;
		XMFLOAT3 velocity;
		XMFLOAT4 color;
	};

	ParticleGenerator(ID3D11Device *_d3DDevice, ID3D11DeviceContext *_immediateContext);
	~ParticleGenerator();
	void InitialiseGenerator();
	void DrawOne(Particle *one, XMMATRIX *view, XMMATRIX *projection, XMFLOAT3 cameraposition);
	void Draw(XMMATRIX *view, XMMATRIX *projection, XMFLOAT3 cameraposition);
	
	void SetXPos(float num);
	void SetYPos(float num);
	void SetZPos(float num);
	void SetXAngle(float num);
	void SetYAngle(float num);
	void SetZAngle(float num);
	void SetScale(float num);
	void SetRotation(float num);
	float GetXPos();
	float GetYPos();
	float GetZPos();
	float GetXAngle();
	float GetYAngle();
	float GetZAngle();
	float GetScale();
	float GetRotation();
	void IncXPos(float num);
	void IncYPos(float num);
	void IncZPos(float num);
	void IncXAngle(float num);
	void IncYAngle(float num);
	void IncZAngle(float num);
	void IncScale(float num);
	void IncRotation(float num);
	void DecXPos(float num);
	void DecYPos(float num);
	void DecZPos(float num);
	void DecXAngle(float num);
	void DecYAngle(float num);
	void DecZAngle(float num);
	void DecScale(float num);
	void DecRotation(float num);
	void LookAtXZ(float x, float z);
	void MoveForward(float distance);
private:
	ID3D11Device *mD3DDevice;
	ID3D11DeviceContext *mImmediateContext;

	ID3D11Buffer* mVertexBuffer;
	ID3D11VertexShader *mVShader;
	ID3D11PixelShader *mPShader;
	ID3D11InputLayout *mInputLayout;
	ID3D11Buffer *mConstantBuffer;
	ID3D11ShaderResourceView *mTexture;
	ID3D11SamplerState *mSampler;

	float mX, mY, mZ, mDX, mDZ;
	float mXAngle, mZAngle, mYAngle;
	float mScale, mRotation;

	UINT VERTCOUNT;
	float mTimePrevious;
	float mUntilParticle;
	float randomZeroToOne();
	float randomNegOneToPosOne();
	
	std::list<Particle*> mFree;
	std::list<Particle*> mActive;
};