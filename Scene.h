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

// abstract base class
class Scene
{
public:
	virtual bool Init() = 0;
	virtual void RenderScene(float dt) = 0;
};

#endif
