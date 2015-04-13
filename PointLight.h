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


class PointLight
{
private:

	XMVECTOR point_light_colour;
	XMVECTOR point_light_position;

public:
	PointLight();
	PointLight(XMVECTOR colour, XMVECTOR position);
	PointLight(const PointLight&);
	~PointLight();

	void SetLightPosition(float x, float y , float z);
	void SetColour(float r, float g, float b,float a);
	XMVECTOR GetPointLightColour();
	XMVECTOR GetPointLightPosition();

};