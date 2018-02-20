#pragma once
#ifndef RANDOMGENERATION_H
#define RANDOMGENERATION_H

#include "IRandomGeneration.h"
#include <DirectXMath.h>

class RandomGeneration : public IRandomGeneration
{
private:


public:
	RandomGeneration();

	int GenerateInt(int rangeStart, int rangeEnd);

	float GenerateFloat(float rangeStart, float rangeEnd);

	//virtual DirectX::XMFLOAT3 GenerateEnemySpawnPosition();// NOT NEEDED, will be given by levelManager
};

#endif