/**
AGP Assignment
AGPRandom.cpp
Purpose: Has general functions to generate random values

@author Marcel Zobus
*/
#include "AGPRandom.h"

static AGPRandom* instance = NULL;

//singleton class
AGPRandom* AGPRandom::GetInstance()
{
	if (instance == NULL)
	{
		instance = new AGPRandom();
	}
	return instance;
}

AGPRandom::AGPRandom()
{
	srand(static_cast <unsigned> (time(0)));
}

// returns a random value from low (inclusive) to high (exclusive)
float AGPRandom::GetRandomRange(int high, int low)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}

// returns a random value from 0 to 1
float AGPRandom::GetRandom0To1()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

// returns a random value from 0 to X (exclusive)
float AGPRandom::GetRandom0ToX(int x)
{
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x));
}