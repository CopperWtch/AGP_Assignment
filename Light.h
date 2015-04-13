#pragma once
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include "GameObject.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#include <xnamath.h>
#include <stdio.h>
#include <string>
#include <vector>


class Light
{
private:
	XMVECTOR directional_light_shines_from;
	XMVECTOR directional_light_colour;
	XMVECTOR ambient_light_colour;

public:
	Light();
	Light(XMVECTOR lightDirection, XMVECTOR directionalColour, XMVECTOR ambientColour);
	Light(const Light&);
	~Light();

	void SetDirectionalLight(XMVECTOR direction, XMVECTOR colour);
	void SetAmbientLight(XMVECTOR colour);
	XMVECTOR GetLightDirection();
	XMVECTOR GetDirectionalLightColour();
	XMVECTOR GetAmbientLightColour();

};