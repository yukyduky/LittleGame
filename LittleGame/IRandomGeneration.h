#pragma once
#ifndef IRANDOMGENERATION_H
#define IRANDOMGENERATION_H

class IRandomGeneration {
public:
	virtual int GenerateInt(int rangeStart, int rangeEnd) = 0;
	virtual float GenerateFloat(float rangeStart, float rangeEnd) = 0;
};

#endif
