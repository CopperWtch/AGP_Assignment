/**
AGP Assignment
LevelGenerator.h
Purpose: Header file for LevelGenerator.cpp

@author Marcel Zobus
*/
#pragma once

#ifndef _AGPRANDOM_H_
#define _AGPRANDOM_H_

#include <time.h>
#include <cstdlib>

class AGPRandom
{
public:
	static AGPRandom* GetInstance();
	float GetRandomRange(int high, int low);
	float GetRandom0To1();
	float GetRandom0ToX(int x);
private:
	AGPRandom();
};

#endif