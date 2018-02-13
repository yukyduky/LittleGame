#include "FloorFallPatterns.h"
#include <algorithm>

void FFPattern::createPattern(int nr, FloorFallData& pattern)
{
	int width = ARENAWIDTH / ARENASQUARESIZE;
	int depth = ARENAHEIGHT / ARENASQUARESIZE;
	switch (nr)
	{
	//Flor falls each column from left to right.
	case 0:
		for (int i = 1; i < width - 1; i++) {
			if (i % 2 != 0) {
				for (int j = 1; j < depth - 1; j++) {
					pattern.pattern.push_back(Index(i, j));
				}
			}
			else {
				for (int j = 1; j < depth - 1; j++) {
					pattern.pattern.push_back(Index(i, depth - j - 1));
				}
			}
			
		}
		pattern.time = 3;
		pattern.popsPerIteration = 4;
		pattern.recoverMode = false;
		break;
	//Floor falls in a spiral pattern inwards.
	case 1:
		for (int i = 1; i < depth / 2; i++) {
			for (int j = i; j < depth - i; j++) {
				pattern.pattern.push_back(Index(i, j));
			}
			for (int j = i + 1; j < width - i; j++) {
				pattern.pattern.push_back(Index(j, depth - i - 1));
			}
			for (int j = i; j < depth - i; j++) {
				pattern.pattern.push_back(Index(width - i - 1, depth - j - 2));
			}
			for (int j = i; j < width - i - 1; j++) {
				pattern.pattern.push_back(Index(width - j - 2, i));
			}
		}
		pattern.time = 3;
		pattern.popsPerIteration = 4;
		pattern.recoverMode = false;
		break;
	//Floor falls in a random order.
	case 2:
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < depth - 1; j++) {
				pattern.pattern.push_back(Index(i, j));
			}
		}
		std::random_shuffle(pattern.pattern.begin(), pattern.pattern.end());
		pattern.time = 3;
		pattern.popsPerIteration = 4;
		pattern.recoverMode = false;
		break;
	//If a faulty nr is entered the floor will not fall at all.
	default:
		break;
	}
}

int FFPattern::GETmaxNum()
{
	return this->maxNum;
}