#pragma once
#ifndef IRANDOMGENERATION_H
#define IRANDOMGENERATION_H

#include <DirectXMath.h>

class IRandomGeneration {
public:
	virtual int GenerateInt(int rangeStart, int rangeEnd) = 0;
	virtual float GenerateFloat(float rangeStart, float rangeEnd) = 0;
	virtual DirectX::XMFLOAT3 GenerateEnemySpawnPosition() = 0;
};

#endif
