#pragma once
#ifndef RANDOMGENERATION_H
#define RANDOMGENERATION_H

#include "IRandomGeneration.h"

class RandomGeneration : public IRandomGeneration
{
private:


public:
	RandomGeneration();

	int GenerateInt(int rangeStart, int rangeEnd);

	float GenerateFloat(float rangeStart, float rangeEnd);
};

#endif