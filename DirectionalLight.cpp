/**
AGP Assignment
DirectionalLight.h
Purpose: Directional Light

@author Sarah Bulk
*/

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::DirectionalLight(const DirectionalLight& other)
{

}

DirectionalLight::DirectionalLight(XMVECTOR colour, XMVECTOR direction) : Light(colour)
{
	directionalLightVector = direction;
}

DirectionalLight::~DirectionalLight()
{
}

XMVECTOR DirectionalLight::GetLightDirection()
{
	return directionalLightVector;
}

void DirectionalLight::SetLightDirection(float x, float y, float z)
{
	directionalLightVector = XMVectorSet(x, y, z, 1.0f);
}