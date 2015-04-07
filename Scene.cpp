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

void Scene::RenderScene()
{
	// render stuff here
}