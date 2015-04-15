#include "AGPRandom.h"


static AGPRandom* instance = NULL;

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

float AGPRandom::GetRandomRange(int high, int low)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}

float AGPRandom::GetRandom0To1()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float AGPRandom::GetRandom0ToX(int x)
{
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x));
}