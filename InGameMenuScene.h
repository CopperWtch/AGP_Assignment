#pragma once

#ifndef _INGAMEMENUSCENE_H_
#define _INGAMEMENUSCENE_H_

#include "AGPSideScroller.h"

class InGameMenuScene : public Scene
{
public:
	~InGameMenuScene();
	virtual bool Init();
	virtual void RenderScene(float dt);
	CREATE_FUNC(InGameMenuScene);
};

#endif