/**
AGP Assignment
Light.h
Purpose: Header file for Light.cpp

@author Sarah Bulk
*/

#ifndef __LIGHT_H__
#define __LIGHT_H__

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


class Light : public GameObject
{
private:
	XMVECTOR lightColour;

public:
	Light();
	Light(const Light&);
	Light(XMVECTOR colour);
	~Light();

	void SetLightColour(float x, float y, float z, float w);
	XMVECTOR GetLightColour();

	void IncreaseLight(float r, float g, float b, float a);
	void DecreaseLight(float r, float g, float b, float a);
	float GetLightRatio();
};

#endif