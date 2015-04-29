/**
AGP Assignment
LightManager.cpp
Purpose: Global class to manage the lighting.
		Set the light data in the manager for
		the models to access the data automatically.

@author Sarah Bulk
*/

#include "LightManager.h"


static LightManager* _instance = NULL;

LightManager * LightManager::sharedLightManager() {
	if (!_instance) {
		_instance = new LightManager();
	}
	return _instance;
}

LightManager::~LightManager()
{
};
LightManager::LightManager()
{
};


void LightManager::addPointLight(PointLight* p)
{
	pointLights.push_back(p);
};
void LightManager::removePointLight(PointLight* p)
{
	for (int i = 0; i < pointLights.size(); i++)
	{
		if (pointLights[i] == p)
			pointLights.erase(pointLights.begin() + i);
	}
};
void LightManager::setDirectionalLight(DirectionalLight* d)
{
	directionalLight = d;
};
void LightManager::setAmbientLight(Light* l)
{
	ambientLight = l;
};

std::vector<PointLight*> LightManager::getPointLights()
{
	return pointLights;
};
DirectionalLight* LightManager::getDirectionalLight()
{
	return directionalLight;
};
Light* LightManager::getAmbientLight()
{
	return ambientLight;
};