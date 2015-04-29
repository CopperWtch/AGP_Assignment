/**
AGP Assignment
Model.h
Purpose: Header file for Model.cpp

@author Marcel Zobus
*/

#pragma once
#include "objfilemodel.h"
#include "GameObject.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "LightManager.h"

class Model : public GameObject
{
public:
	Model::Model(ID3D11Device *_d3DDevice, ID3D11DeviceContext *_immediateContext);
	Model::~Model();
	int LoadObjModel(char *filename, ID3D11ShaderResourceView *texture);
	void Draw(XMMATRIX *world, XMMATRIX *view, XMMATRIX *projection);
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

	ObjFileModel *mObject;
	ID3D11VertexShader *mVShader;
	ID3D11PixelShader *mPShader;
	ID3D11InputLayout *mInputLayout;
	ID3D11Buffer *mConstantBuffer;
	ID3D11ShaderResourceView *mTexture;
	ID3D11SamplerState *mSampler;

	Light*	mAmbientLight;
	DirectionalLight*	mDirectionalLight;
	std::vector<PointLight*> mPointLights;
	LightManager* mLightManager;

	float mX, mY, mZ, mDX, mDZ;
	float mXAngle, mZAngle, mYAngle;
	float mScale, mRotation;
};