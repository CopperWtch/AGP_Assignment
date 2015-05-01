/**
AGP Assignment
Gameobject.h
Purpose: Header file for GameObject.cpp // base class for all objects in the game

@author Marcel Zobus
*/
#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <string>

// abstract base class 
class GameObject
{
public:
	virtual std::string GetName() = 0; //pure virtual function
};

#endif
