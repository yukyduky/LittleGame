#include "RandomGeneration.h"
#include <time.h>
#include <stdlib.h>
#include <cassert>

RandomGeneration::RandomGeneration() {
	time_t t;
	srand(static_cast<unsigned int>(time(&t)));
}

int RandomGeneration::GenerateInt(int rangeStart, int rangeEnd) {
	/// If you're calling this function with rangeEnd < rangeStart, then you deserve the consequences.
	int returnValue = -1;
	if (rangeStart < 0) {
		// Both are negative
		if (rangeEnd < 0) {
			// make them positive
			int rangeEnd_ = rangeStart*-1;
			int rangeStart_ = rangeEnd*-1;
			returnValue = rand() % ((rangeEnd_ + 1) - rangeStart_) + rangeStart_;
			// then make the returnvalue negative
			returnValue *= -1;
		}
		// Only range start is negative
		else {
			// Force them positive
			int totalLength = rangeEnd - rangeStart;
			int rangeStart_ = rangeStart + totalLength;
			int rangeEnd_ = rangeEnd + totalLength;
			returnValue = rand() % ((rangeEnd_ + 1) - rangeStart_) + rangeStart_;
			// Subtract the forced value
			returnValue -= totalLength;
		}
	}
	// Both are positive, proceed as usual
	else {
		returnValue = rand() % ((rangeEnd + 1) - rangeStart) + rangeStart;
	}

	return rand() % ((rangeEnd + 1) - rangeStart) + rangeStart;
}

float RandomGeneration::GenerateFloat(float rangeStart, float rangeEnd) {
	float randomFloat = 0.0f;
	int integral = static_cast<int>((rangeEnd - rangeStart) * 100.0f);

	while (randomFloat == 0.0f) {
		randomFloat = (static_cast<float>((rand() % integral) * 0.01f) + rangeStart);
	}

	return randomFloat;
}

