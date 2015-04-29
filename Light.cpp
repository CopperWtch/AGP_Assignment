/**
AGP Assignment
Light.cpp
Purpose: Base light class that can be created as an ambient light

@author Sarah Bulk
*/

#include "Light.h"

Light::Light()
{
	lightColour = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}


Light::Light(const Light& other)
{
}

Light::Light(XMVECTOR colour)
{
	this->lightColour = colour;
}

Light::~Light()
{
}

void Light::SetLightColour(float r, float g, float b, float a)
{
	lightColour = XMVectorSet(r, g, b, a);
}

XMVECTOR Light::GetLightColour()
{
	return lightColour;
}

void Light::IncreaseLight(float r, float g, float b, float a)
{
	if (lightColour.x < 1.5f)
	{
		XMVECTOR amount = XMVectorSet(r, g, b, a);
		lightColour = lightColour + amount;
	}
}

void Light::DecreaseLight(float r, float g, float b, float a)
{
	if (lightColour.x > -0.5f)
	{
		XMVECTOR amount = XMVectorSet(r, g, b, a);
		lightColour = lightColour - amount;
	}

}

float Light::GetLightRatio()
{
	float light_amount = (lightColour.x + 0.5f) / 2 * 100;
	return (lightColour.x + 0.5f) / 2 * 100;
}