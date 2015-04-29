/**
AGP Assignment
PointLight.cpp
Purpose: Point Light that can be created to affect the world

@author Sarah Bulk
*/

#include "PointLight.h"


PointLight::PointLight(XMVECTOR colour, XMVECTOR position) : Light(colour)
{
	pointLightPosition = position;
}

PointLight::PointLight()
{
	/*point_light_position = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	point_light_colour = XMVectorSet(0.7f, 0.7f, 0.1f, 0.5f);*/
}


PointLight::PointLight(const PointLight& other)
{
}


PointLight::~PointLight()
{
}

void PointLight::SetLightPosition(float x, float y, float z)
{
	pointLightPosition = XMVectorSet(x, y, z, 1.0f);


}
XMVECTOR PointLight::GetPointLightPosition()
{
	return pointLightPosition;
}
