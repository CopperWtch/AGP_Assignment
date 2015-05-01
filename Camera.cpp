/**
AGP Assignment
Camera.cpp
Purpose: Camera Object

@author Marcel Zobus
*/

#include "camera.h"


Camera::Camera(float x, float y, float z, float camera_rotation){
	mX = x;
	mY = y;
	mZ = z;
	mCameraRotation = camera_rotation;

	CalcDXDY();
}

//////////////////////////////////////////////////////////////////////////////////////
// Transform Camera
//////////////////////////////////////////////////////////////////////////////////////

void Camera::Rotate(float number_of_degrees)
{
	mCameraRotation += number_of_degrees;
	CalcDXDY();
}

void Camera::Forward(float distance)
{
	mX += distance * mDX;
	mZ += distance * mDZ;
}

void Camera::MoveLeftRight(float distance)
{
	XMVECTOR crossProduct = XMVector3Cross(mPosition, mLookat);
	mX += crossProduct.x * distance;
	mZ += crossProduct.z * distance;
}

XMVECTOR Camera::Up()
{
	return XMVectorSet(0.0, 0.1, 0.0, 0.0);
}

XMMATRIX Camera::GetViewMatrix()
{
	mPosition = XMVectorSet(mX, mY, mZ, 0.0);
	mLookat = XMVectorSet(mX + mDX, mY, mZ + mDZ, 0.0);
	return XMMatrixLookAtLH(mPosition, mLookat, Up());
}

// third person view matrix calculation
XMMATRIX Camera::GetViewMatrixThirdPerson(XMVECTOR pos)
{
	// look at is the position of the player
	mLookat = XMVectorSet(pos.x, pos.y, 0, 0.0);
	return XMMatrixLookAtLH(pos, mLookat, Up());
}

void Camera::CalcDXDY()
{
	mDX = sin(XMConvertToRadians(mCameraRotation));
	mDZ = cos(XMConvertToRadians(mCameraRotation));
}

//////////////////////////////////////////////////////////////////////////////////////
// Getter and Setter
//////////////////////////////////////////////////////////////////////////////////////

float Camera::GetX()
{
	return mX;
}

float Camera::GetY()
{
	return mY;
}

float Camera::GetZ()
{
	return mZ;
}

XMFLOAT3 Camera::GetPosition()
{
	return XMFLOAT3(GetX(), GetY(), GetZ());
}


