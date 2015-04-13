#include "Light.h"


Light::Light(XMVECTOR lightDirection, XMVECTOR directionalColour, XMVECTOR ambientColour)
{
	directional_light_shines_from = lightDirection;
	directional_light_colour = directionalColour;
	ambient_light_colour = ambientColour;

}

Light::Light()
{
	directional_light_shines_from = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	directional_light_colour = XMVectorSet(0.5f, 0.5f, 0.5f, 0.5f);
	ambient_light_colour = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}


Light::Light(const Light& other)
{
}


Light::~Light()
{
}

void Light::SetDirectionalLight(XMVECTOR direction, XMVECTOR colour)
{
	directional_light_shines_from = direction;
	directional_light_colour = colour;


}

void Light::SetAmbientLight(XMVECTOR colour)
{
	ambient_light_colour = colour;
}

XMVECTOR Light::GetLightDirection()
{
	return directional_light_shines_from;
}
XMVECTOR Light::GetDirectionalLightColour()
{
	return directional_light_colour;
}

XMVECTOR Light::GetAmbientLightColour()
{
	return ambient_light_colour;
}
