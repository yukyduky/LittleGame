#include "RandomGeneration.h"
#include <time.h>
#include <stdlib.h>
#include <cassert>

RandomGeneration::RandomGeneration() {
	time_t t;
	srand(static_cast<unsigned int>(time(&t)));
}

int RandomGeneration::GenerateInt(int rangeStart, int rangeEnd) {
	return rand() % ((rangeEnd + 1) - rangeStart) + rangeStart;
}

float RandomGeneration::GenerateFloat(float rangeStart, float rangeEnd) {
	float randomFloat = 0.0f;
	int integral = static_cast<int>((rangeEnd - rangeStart) * 100.0f);

	randomFloat = (static_cast<float>((rand() % integral) * 0.01f) + rangeStart);

	return randomFloat;
}