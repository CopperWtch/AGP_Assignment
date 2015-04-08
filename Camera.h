/**
AGP Assignment
Camera.h
Purpose: Header file for Camera.cpp

@author Marcel Zobus
*/

#include "d3d11.h"
#include "math.h"

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENTS
#include <xnamath.h>
#include "GameObject.h"

class Camera : public GameObject {
public:
	Camera::Camera(float _x, float _y, float _z, float _cameraRotation);
	void Rotate(float degrees);
	void Forward(float distance);
	void MoveLeftRight(float distance);
	XMVECTOR Up();
	XMMATRIX GetViewMatrix();
	void CalcDXDY();
	float GetX();
	float GetY();
	float GetZ();
	XMFLOAT3 GetPosition();
private:
	float mX, mY, mZ, mDX, mDZ, mCameraRotation;
	XMVECTOR mPosition, mLookat, mUp;

	
};