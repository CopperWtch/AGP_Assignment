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
	static LightManager * sharedLightManager();

	std::vector<PointLight*> getPointLights();
	DirectionalLight* getDirectionalLight();
	Light* getAmbientLight();

	void addPointLight(PointLight* p);
	void removePointLight(PointLight* p);
	void setDirectionalLight(DirectionalLight* d);
	void setAmbientLight(Light* l);


};

#endif