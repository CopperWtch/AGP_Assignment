/**
AGP Assignment
Scene.cpp
Purpose: implements the base class Scene

@author Marcel Zobus
*/
#pragma once
#include "Scene.h"

Scene::Scene()
{
	// constructor
}

Scene::~Scene()
{
	// destructor
}

bool Scene::Init()
{
	return true;
}


Scene *Scene::create()
{
	Scene *scene = new Scene();
	if (scene && scene->Init())
	{
		return scene;
	}
	else
	{
		delete scene;
		return NULL;
	}
}

void Scene::RenderScene(float dt)
{
	// render stuff here
}