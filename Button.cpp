/**
AGP Assignment
Button.h
Purpose: 2D Button for the player to interact with

@author Sarah Bulk
*/

#include "Button.h"

//////////////////////////////////////////////////////////////////////////////////////
// Constructors
//////////////////////////////////////////////////////////////////////////////////////
Button::Button()
{

}

Button::Button(ImageClass* obj)
{
	this->mImg = obj;
	this->minX = obj->GetLeft();
	this->maxX = obj->GetRight();
	this->minY = obj->GetBottom();
	this->maxY = obj->GetTop();
}

//////////////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////////////
Button::~Button()
{

}

//////////////////////////////////////////////////////////////////////////////////////
// Check if the image was clicked
//////////////////////////////////////////////////////////////////////////////////////
bool Button::IsClicked(float mouseX, float mouseY)
{
	minX = mImg->GetLeft();
	maxX = mImg->GetRight();
	minY = mImg->GetBottom();
	maxY = mImg->GetTop();

	//mouseX = (float)((640 / 2) * -1) + (float)mouseX;
	//mouseY = (float)(480 / 2) - (float)mouseY;
	//mouseX /= 640;
	//mouseY /= 480;
	mouseX = ((2.0f * (float)mouseX) / (float)640) - 1.0f;
	mouseY = (((2.0f * (float)mouseY) / (float)480) - 1.0f) * -1.0f;

	if ((mouseX > minX && mouseX < maxX) &&
		(mouseY > minY && mouseY < maxY))
	{
		return true;
	}
	else
		return false;
}