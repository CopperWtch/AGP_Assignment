/**
AGP Assignment
PointLight.h
Purpose: Header file for PointLight.cpp

@author Sarah Bulk
*/

#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__


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


class PointLight : public Light
{
private:

	XMVECTOR pointLightPosition;

public:
	PointLight();
	PointLight(XMVECTOR colour, XMVECTOR position);
	PointLight(const PointLight&);
	~PointLight();

	void SetLightPosition(float x, float y, float z);
	XMVECTOR GetPointLightPosition();

};

#endif