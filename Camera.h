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

class Camera {
public:
	Camera::Camera(float x, float y, float z, float camera_rotation);
	void Rotate(float number_of_degrees);
	void Forward(float distance);
	void MoveLeftRight(float distance);
	XMVECTOR Up();
	XMMATRIX GetViewMatrix();
	void CalcDXDY();
	float GetX();
	float GetY();
	float GetZ();
private:
	float mX, m_y, m_z, m_dx, m_dz, m_camera_rotation;
	XMVECTOR m_position, m_lookat, m_up;

	
};