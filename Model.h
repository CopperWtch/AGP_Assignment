#pragma once
#include "objfilemodel.h"

class Model
{
private:
	ID3D11Device *m_pD3DDevice;
	ID3D11DeviceContext *m_pImmediateContext;

	ObjFileModel *m_pObject;
	ID3D11VertexShader *m_pVShader;
	ID3D11PixelShader *m_pPShader;
	ID3D11InputLayout *m_pInputLayout;
	ID3D11Buffer *m_pConstantBuffer;
	ID3D11ShaderResourceView *m_pTexture0;
	ID3D11SamplerState *m_pSampler0;


	float m_x, m_y, m_z, m_dx, m_dz;
	float m_xangle, m_zangle, m_yangle;
	float m_scale, m_rotation;
public:
	Model::Model(ID3D11Device *d3DDevice, ID3D11DeviceContext *immediateContext);
	Model::~Model();
	int LoadObjModel(char *filename, ID3D11ShaderResourceView *m_pTexture0);
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
	void LookAt_XZ(float x, float z);
	void MoveForward(float distance);
	void Log(float x);
};