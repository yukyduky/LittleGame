#include "RandomGeneration.h"
#include <time.h>
#include <stdlib.h>
#include <cassert>

RandomGeneration::RandomGeneration() {
	srand(time(NULL));
}

int RandomGeneration::GenerateInt(int rangeStart, int rangeEnd) {
	return rand() % ((rangeEnd + 1) - rangeStart) + rangeStart;
}

float RandomGeneration::GenerateFloat(float rangeStart, float rangeEnd) {
	float randomFloat = 0.0f;
	int integral = (rangeEnd - rangeStart) * 100;

	while (randomFloat == 0.0f) {
		randomFloat = ((rand() % integral * 0.01) + rangeStart);
	}

	return randomFloat;
}

