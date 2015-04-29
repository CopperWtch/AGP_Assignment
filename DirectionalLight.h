/**
AGP Assignment
DirectionalLight.h
Purpose: Header file for DirectionalLight.cpp

@author Sarah Bulk
*/

#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#pragma once
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

#include "Light.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#include <xnamath.h>
#include <stdio.h>
#include <string>
#include <vector>


class DirectionalLight : public Light
{
private:
	XMVECTOR directionalLightVector;

public:
	DirectionalLight();
	DirectionalLight(const DirectionalLight&);
	DirectionalLight(XMVECTOR colour, XMVECTOR direction);
	~DirectionalLight();

	XMVECTOR GetLightDirection();
	void SetLightDirection(float x, float y, float z);

	void IncreaseDirLight(float r, float g, float b, float a);
	void DecreaseDirLight(float r, float g, float b, float a);
	float GetLightRatio();
};


#endif