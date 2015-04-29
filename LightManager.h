/**
AGP Assignment
LightManager.h
Purpose: Header file for LightManager.h

@author Sarah Bulk
*/

#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include "PointLight.h"
#include "DirectionalLight.h"
#include "Light.h"

#include <vector>
#pragma once

class LightManager : public GameObject
{
public:
	~LightManager();
	LightManager();

private:
	std::vector<PointLight*> pointLights;
	DirectionalLight* directionalLight;
	Light* ambientLight;

public:
	static LightManager * GetInstance();

	std::vector<PointLight*> GetPointLights();
	DirectionalLight* GetDirectionalLight();
	Light* GetAmbientLight();

	void AddPointLight(PointLight* p);
	void RemovePointLight(PointLight* p);
	void SetDirectionalLight(DirectionalLight* d);
	void SetAmbientLight(Light* l);


};

#endif