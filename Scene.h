/**
AGP Assignment
Scene.h
Purpose: Header file for Scene.cpp // class to inherit from to create a scene

@author Marcel Zobus
*/
#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include <d3d11.h>


class Scene
{
public:
	Scene();
	~Scene();
	static Scene *create(void);
	bool Init();
	void RenderScene(float dt);
};

#endif
