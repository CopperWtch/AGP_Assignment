#include "camera.h"


Camera::Camera(float x, float y, float z, float camera_rotation){
	m_x = x;
	m_y = y;
	m_z = z;
	m_camera_rotation = camera_rotation;

	CalcDXDY();
}

void Camera::Rotate(float number_of_degrees)
{
	m_camera_rotation += number_of_degrees;
	CalcDXDY();
}

void Camera::Forward(float distance)
{
	m_x += distance * m_dx;
	m_z += distance * m_dz;
}

void Camera::MoveLeftRight(float distance)
{
	XMVECTOR crossProduct = XMVector3Cross(m_position, m_lookat);
	m_x += crossProduct.x * distance;
	m_z += crossProduct.z * distance;
}

XMVECTOR Camera::Up()
{
	return XMVectorSet(0.0, 0.1, 0.0, 0.0);
}

XMMATRIX Camera::GetViewMatrix()
{
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0);
	m_lookat = XMVectorSet(m_x + m_dx, m_y, m_z + m_dz, 0.0);
	return XMMatrixLookAtLH(m_position, m_lookat, Up());
}

void Camera::CalcDXDY()
{
	m_dx = sin(XMConvertToRadians(m_camera_rotation));
	m_dz = cos(XMConvertToRadians(m_camera_rotation));
}

float Camera::GetX()
{
	return m_x;
}

float Camera::GetY()
{
	return m_y;
}

float Camera::GetZ()
{
	return m_z;
}


