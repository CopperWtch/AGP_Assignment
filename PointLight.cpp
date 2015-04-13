#include "PointLight.h"


PointLight::PointLight(XMVECTOR colour, XMVECTOR position)
{
	point_light_colour = colour;
	point_light_position = position;
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

void PointLight::SetLightPosition(float x,float y,float z)
{
	point_light_position = XMVectorSet(x,y,z, 1.0f);


}

void PointLight::SetColour(float r, float g, float b,float a)
{
	point_light_colour = XMVectorSet(r, g, b, a);
}

XMVECTOR PointLight::GetPointLightColour()
{
	return point_light_colour;
}
XMVECTOR PointLight::GetPointLightPosition()
{
	return point_light_position;
}
