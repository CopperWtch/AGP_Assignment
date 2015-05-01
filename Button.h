/**
AGP Assignment
Button.h
Purpose: Header file for Button.cpp

@author Sarah Bulk
*/

#pragma once

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "AGPSideScroller.h"
#include "ImageClass.h"

class Button : public GameObject
{
public:
	Button();
	Button(ImageClass* obj);
	~Button();
	virtual std::string GetName();
private:
	//image component
	ImageClass* mImg;
	//relative position of the image
	float minX, maxX, minY, maxY;

public:
	void SetComponent(ImageClass* obj){ this->mImg = obj; };
	ImageClass* GetComponent(){ return mImg; };

	bool IsClicked(float mouseX, float mouseY);

	bool Display(ID3D11DeviceContext* deviceContext, float x, float y, float sizeW, float sizeH);
};

#endif