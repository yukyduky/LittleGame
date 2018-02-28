#include "ArenaPatterns.h"
#include <algorithm>
#include "LevelManager.h"
#include "Locator.h"

ArenaPatterns::ArenaPatterns()
{
	this->maxFloorNum = 2;
	this->maxWallNum = 4;
	this->maxArenaNum = 2;
}

ArenaPatterns::~ArenaPatterns()
{

}

void ArenaPatterns::createFloorPattern(int nr, FloorFallData& pattern)
{
	int width = ARENADATA::GETarenaWidth() / ARENADATA::GETsquareSize();
	int depth = ARENADATA::GETarenaHeight() / ARENADATA::GETsquareSize();
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
	//First easy pattern
	case 3: 
		for (int j = 1; j < depth - 1; j++) {
			if (j < depth / 5) {
				for (int i = 1; i < width - 1; i++) {
					pattern.pattern.push_back(Index(i, j));
				}
			} 
			else if (j < depth * 2 / 5 ) {
				for (int i = 1; i < width - 1; i++) {
					if ( i < width / 5 || i > width * 4 / 5) {
						pattern.pattern.push_back(Index(i, j));
					}
				}
			}
			else if (j < depth * 3 / 5) {
				for (int i = 1; i < width - 1; i++) {
					if (i < width * 2 / 5 || i > width * 3 / 5) {
						pattern.pattern.push_back(Index(i, j));
					}
				}
			}
			else if (j < depth * 4 / 5) {
				for (int i = 1; i < width - 1; i++) {
					if (i < width / 5 || i > width * 4 / 5) {
						pattern.pattern.push_back(Index(i, j));
					}
				}
			}
			else {
				for (int i = 1; i < width - 1; i++) {
					pattern.pattern.push_back(Index(i, j));
				}
			}
		}
		pattern.time = 3;
		pattern.popsPerIteration = 10000;
		pattern.recoverMode = false;
		break;
	//If a faulty nr is entered the floor will not fall at all.
	default:
		break;
	}
}

void ArenaPatterns::createEasyFloorPatterns(std::vector<FloorFallData>& easy) 
{
	int width = ARENADATA::GETarenaWidth() / ARENADATA::GETsquareSize();
	int depth = ARENADATA::GETarenaHeight() / ARENADATA::GETsquareSize();
	int randomX1 = Locator::getRandomGenerator()->GenerateInt(1, width - 3);
	int randomY1 = Locator::getRandomGenerator()->GenerateInt(1, depth - 3);
	int randomX2 = randomX1 + 1;
	int randomY2 = randomY1 + 1;

	//First easy pattern
	FloorFallData easy1;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			if (i == randomX1 || i == randomX2 || j == randomY1 || j == randomY2) {
				easy1.pattern.push_back(Index(i, j));
			}
		}
	}
	easy.push_back(easy1);
	//Second easy pattern
	FloorFallData easy2;
	for (int j = 0; j < depth; j++) {
		if (j > depth / 5 && j < depth * 2 / 5) {
			for (int i = 0; i < width; i++) {
				if (i > width / 5 && i < width * 4 / 5) {
					easy2.pattern.push_back(Index(i, j));
				}
			}
		}
		else if (j > depth * 2 / 5 && j < depth * 3 / 5) {
			for (int i = 0; i < width; i++) {
				if (i > width * 2 / 5 && i < width * 3 / 5) {
					easy2.pattern.push_back(Index(i, j));
				}
			}
		}
		else if (j > depth * 3 / 5 && j < depth * 4 / 5) {
			for (int i = 0; i < width; i++) {
				if (i > width / 5 && i < width * 4 / 5) {
					easy2.pattern.push_back(Index(i, j));
				}
			}
		}
	}
	easy.push_back(easy2);
	//Third easy pattern
	FloorFallData easy3;
	for (int i = 0; i < width; i++) {
		if (i > width / 3 && i < width * 2 / 3) {
			for (int j = 0; j < depth; j++) {
				if (j > depth * 2 / 10) {
					easy3.pattern.push_back(Index(i, j));
				}
			}
		}
	}
	easy.push_back(easy3);
	//Fourth easy pattern
	FloorFallData easy4;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			if (i < width * 2 / 10 || i > width * 8 / 10) {
				easy4.pattern.push_back(Index(i, j));
			}
			else if (j < depth * 2 / 10 || j > depth * 8 / 10) {
				easy4.pattern.push_back(Index(i, j));
			}
		}
	}
	easy.push_back(easy4);
}

void ArenaPatterns::createMediumFloorPatterns(std::vector<FloorFallData>& medium) {
	int width = ARENADATA::GETarenaWidth() / ARENADATA::GETsquareSize();
	int depth = ARENADATA::GETarenaHeight() / ARENADATA::GETsquareSize();
	
	//First medium pattern
	FloorFallData medium1;
	for (int j = 0; j < depth; j++) {
		if (j < depth / 5) {
			for (int i = 1; i < width - 1; i++) {
				medium1.pattern.push_back(Index(i, j));
			}
		}
		else if (j < depth * 2 / 5) {
			for (int i = 1; i < width - 1; i++) {
				if (i < width / 5 || i > width * 4 / 5) {
					medium1.pattern.push_back(Index(i, j));
				}
			}
		}
		else if (j < depth * 3 / 5) {
			for (int i = 1; i < width - 1; i++) {
				if (i < width * 2 / 5 || i > width * 3 / 5) {
					medium1.pattern.push_back(Index(i, j));
				}
			}
		}
		else if (j < depth * 4 / 5) {
			for (int i = 1; i < width - 1; i++) {
				if (i < width / 5 || i > width * 4 / 5) {
					medium1.pattern.push_back(Index(i, j));
				}
			}
		}
		else {
			for (int i = 1; i < width - 1; i++) {
				medium1.pattern.push_back(Index(i, j));
			}
		}
	}
	medium.push_back(medium1);
	//Second medium pattern
	FloorFallData medium2;
	int nrOfRings = (width / 2) / 3;
	for (int r = 0; r < nrOfRings; r++) {
		
		for (int i = 3 + r * 3; i < width - r * 3 - 3; i++) {
			medium2.pattern.push_back(Index(i, r * 3 + 3));
			medium2.pattern.push_back(Index(i, depth - (r * 3 + 3)));
		}

		for (int j = 3 + r * 3; j < depth - r * 3 - 3; j++) {
			medium2.pattern.push_back(Index(r * 3 + 3, j));
			medium2.pattern.push_back(Index(width - (r * 3 + 4), j));
		}
	
	}
	medium.push_back(medium2);
	//Third medium pattern
	FloorFallData medium3;
	for (int i = 0; i < width; i++) {
		if (i < width * 3 / 10 || i > width * 7 / 10) {
			for (int j = 0; j < depth; j++) {
				medium3.pattern.push_back(Index(i, j));
			}
		}
		else {
			for (int j = 0; j < depth * 2 / 10; j++) {
				medium3.pattern.push_back(Index(i, j));
			}
		}
	}
	medium.push_back(medium3);
	//Fourth medium pattern
	FloorFallData medium4;
	for (int i = 0; i < width; i++) {
		if (i % 5 == 0) {
			for (int j = 0; j < depth; j++) {
				medium4.pattern.push_back(Index(i, j));
			}
		}
	}
	medium.push_back(medium4);
	//Fifth medium pattern
	FloorFallData medium5;
	for (int j = 0; j < depth; j++) {
		if (j % 5 == 0) {
			for (int i = 0; i < width; i++) {
				medium5.pattern.push_back(Index(i, j));
			}
		}
	}
	medium.push_back(medium5);
}

void ArenaPatterns::createHardFloorPatterns(std::vector<FloorFallData>& hard) {
	int width = ARENADATA::GETarenaWidth() / ARENADATA::GETsquareSize();
	int depth = ARENADATA::GETarenaHeight() / ARENADATA::GETsquareSize();

	//First hard pattern
	FloorFallData hard1;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			if (j % 6 == 0) {
				hard1.pattern.push_back(Index(i, j));
			}
			else if (i % 6 == 0){
				hard1.pattern.push_back(Index(i, j));
			}
		}
	}
	hard.push_back(hard1);
	//Second hard pattern
	FloorFallData hard2;
	for (int r = 0; r < depth / 2; r++) {
		if (r % 2 != 0) {
			for (int j = r; j < depth - r; j++) {
				hard2.pattern.push_back(Index(r, j));
			}
		}
	}
	hard.push_back(hard2);
	
}

int ArenaPatterns::GETmaxFloorNum()
{
	return this->maxFloorNum;
}

void ArenaPatterns::createWallPattern(int nr, WallData& pattern) {
	int randomT[4];
	int randomB[4];
	int randomL[4];
	int randomR[4];
	bool spawn = false;

	switch (nr)
	{
	case 0: //Openings at the middle in top, bot, left and right.
		for (int i = 0; i < pattern.nrVertical; i++) {
			if (i == pattern.nrVertical * 0.5f || i == pattern.nrVertical * 0.5f - 1) {
				pattern.rowL[i] = SQUARETYPE::TYPE::SPAWN;
				pattern.rowR[i] = SQUARETYPE::TYPE::SPAWN;
			}
			else {
				pattern.rowL[i] = SQUARETYPE::TYPE::WALL;
				pattern.rowR[i] = SQUARETYPE::TYPE::WALL;
			}
		}
		for (int i = 0; i < pattern.nrHorizontal; i++) {
			if (i == pattern.nrHorizontal * 0.5f || i == pattern.nrHorizontal * 0.5f - 1) {
				pattern.rowT[i] = SQUARETYPE::TYPE::SPAWN;
				pattern.rowB[i] = SQUARETYPE::TYPE::SPAWN;
			}
			else {
				pattern.rowT[i] = SQUARETYPE::TYPE::WALL;
				pattern.rowB[i] = SQUARETYPE::TYPE::WALL;
			}
		}
		break;

	case 1: //Big openings L,R,T and B
		for (int i = 0; i < pattern.nrVertical; i++) {
			if (i < pattern.nrVertical / 4 || i > pattern.nrVertical * 3 / 4) {
				pattern.rowL[i] = SQUARETYPE::TYPE::WALL;
				pattern.rowR[i] = SQUARETYPE::TYPE::WALL;
			}
			else {
				pattern.rowL[i] = SQUARETYPE::TYPE::SPAWN;
				pattern.rowR[i] = SQUARETYPE::TYPE::SPAWN;
			}
		}
		for (int i = 0; i < pattern.nrHorizontal; i++) {
			if (i < pattern.nrHorizontal / 4 || i > pattern.nrHorizontal * 3 / 4) {
				pattern.rowT[i] = SQUARETYPE::TYPE::WALL;
				pattern.rowB[i] = SQUARETYPE::TYPE::WALL;
			}
			else {
				pattern.rowT[i] = SQUARETYPE::TYPE::SPAWN;
				pattern.rowB[i] = SQUARETYPE::TYPE::SPAWN;
			}
		}
		break;

	case 2: //Openings in middle L and R.
		for (int i = 0; i < pattern.nrVertical; i++) {
			if (i < pattern.nrVertical / 3 || i > pattern.nrVertical * 2 / 3) {
				pattern.rowL[i] = SQUARETYPE::TYPE::WALL;
				pattern.rowR[i] = SQUARETYPE::TYPE::WALL;
			}
			else {
				pattern.rowL[i] = SQUARETYPE::TYPE::SPAWN;
				pattern.rowR[i] = SQUARETYPE::TYPE::SPAWN;
			}
		}
		for (int i = 0; i < pattern.nrHorizontal; i++) {
			pattern.rowT[i] = SQUARETYPE::TYPE::WALL;
			pattern.rowB[i] = SQUARETYPE::TYPE::WALL;
		}
		break;

	case 3: // 1/4 of each side is open.
		for (int i = 0; i < 4; i++) {
			randomT[i] = Locator::getRandomGenerator()->GenerateInt(3, pattern.nrHorizontal - 4);
			randomB[i] = Locator::getRandomGenerator()->GenerateInt(2, pattern.nrHorizontal - 4);
			randomL[i] = Locator::getRandomGenerator()->GenerateInt(2, pattern.nrVertical - 4);
			randomR[i] = Locator::getRandomGenerator()->GenerateInt(2, pattern.nrVertical - 4);
		}
		for (int i = 0; i < pattern.nrVertical; i++) {
			pattern.rowL[i] = SQUARETYPE::TYPE::WALL;
			pattern.rowR[i] = SQUARETYPE::TYPE::WALL;
		}
		for (int i = 0; i < pattern.nrVertical; i++) {
			for (int j = 0; j < 2; j++) {
				if (randomL[j] == i || randomL[j] - 1 == i || randomL[j] + 1 == i) {
					pattern.rowL[i] = SQUARETYPE::TYPE::SPAWN;
				}
				if (randomR[j] == i || randomR[j] - 1 == i || randomR[j] + 1 == i) {
					pattern.rowR[i] = SQUARETYPE::TYPE::SPAWN;
				}
			}
		}

		for (int i = 0; i < pattern.nrHorizontal; i++) {
			pattern.rowT[i] = SQUARETYPE::TYPE::WALL;
			pattern.rowB[i] = SQUARETYPE::TYPE::WALL;
		}
		for (int i = 0; i < pattern.nrHorizontal; i++) {
			for (int j = 0; j < 2; j++) {
				if (randomT[j] == i || randomT[j] - 1 == i || randomT[j] + 1 == i) {
					pattern.rowT[i] = SQUARETYPE::TYPE::SPAWN;
				}
				if (randomB[j] == i || randomB[j] - 1 == i || randomB[j] + 1 == i) {
					pattern.rowB[i] = SQUARETYPE::TYPE::SPAWN;
				}
			}
		}
		/*
		for (int i = 0; i < pattern.nrVertical; i++) {
			if (i < pattern.nrVertical / 4) {
				pattern.rowL[i] = SQUARETYPE::TYPE::SPAWN;
				pattern.rowR[i] = SQUARETYPE::TYPE::SPAWN;
			}
			else {
				pattern.rowL[i] = SQUARETYPE::TYPE::WALL;
				pattern.rowR[i] = SQUARETYPE::TYPE::WALL;
			}
		}
		for (int i = 0; i < pattern.nrHorizontal; i++) {
			if (i < pattern.nrHorizontal / 4) {
				pattern.rowT[i] = SQUARETYPE::TYPE::SPAWN;
				pattern.rowB[i] = SQUARETYPE::TYPE::SPAWN;
			}
			else {
				pattern.rowT[i] = SQUARETYPE::TYPE::WALL;
				pattern.rowB[i] = SQUARETYPE::TYPE::WALL;
			}
		}
		std::random_shuffle(&pattern.rowL[0], &pattern.rowL[pattern.nrVertical - 1]);
		std::random_shuffle(&pattern.rowR[0], &pattern.rowR[pattern.nrVertical - 1]);
		std::random_shuffle(&pattern.rowT[0], &pattern.rowT[pattern.nrHorizontal - 1]);
		std::random_shuffle(&pattern.rowB[0], &pattern.rowB[pattern.nrHorizontal - 1]);
		*/
		break;

	case 4: //Big openings Top and Bot
		for (int i = 0; i < pattern.nrVertical; i++) {
			pattern.rowL[i] = SQUARETYPE::TYPE::WALL;
			pattern.rowR[i] = SQUARETYPE::TYPE::WALL;
		}
		for (int i = 0; i < pattern.nrHorizontal; i++) {
			if (i < pattern.nrHorizontal / 3 || i > pattern.nrHorizontal * 2 / 3) {
				pattern.rowT[i] = SQUARETYPE::TYPE::WALL;
				pattern.rowB[i] = SQUARETYPE::TYPE::WALL;
			}
			else {
				pattern.rowT[i] = SQUARETYPE::TYPE::SPAWN;
				pattern.rowB[i] = SQUARETYPE::TYPE::SPAWN;
			}
		}
		break;
	default:
		break;
	}
}

int ArenaPatterns::GETmaxWallNum()
{
	return this->maxWallNum;
}

void ArenaPatterns::createArenaData() {
	int nr = Locator::getRandomGenerator()->GenerateInt(0, this->maxArenaNum);

	nr = 0;
	//int nr = 5;
	switch (nr)
	{
	case 0:
		ARENADATA::SETarenaHeight(1600);
		ARENADATA::SETarenaWidth(1600);
		ARENADATA::SETheightOfWall(2);
		ARENADATA::SETlengthOfWall(1);
		ARENADATA::SETsquareSize(50);
		break;
	case 1:
		ARENADATA::SETarenaHeight(1000);
		ARENADATA::SETarenaWidth(1000);
		ARENADATA::SETheightOfWall(2);
		ARENADATA::SETlengthOfWall(1);
		ARENADATA::SETsquareSize(50);
		break;
	case 2:
		ARENADATA::SETarenaHeight(1600);
		ARENADATA::SETarenaWidth(800);
		ARENADATA::SETheightOfWall(2);
		ARENADATA::SETlengthOfWall(1);
		ARENADATA::SETsquareSize(50);
		break;
	case 3:
		ARENADATA::SETarenaHeight(1000);
		ARENADATA::SETarenaWidth(1500);
		ARENADATA::SETheightOfWall(2);
		ARENADATA::SETlengthOfWall(1);
		ARENADATA::SETsquareSize(50);
		break;
	case 4:
		ARENADATA::SETarenaHeight(1600);
		ARENADATA::SETarenaWidth(1400);
		ARENADATA::SETheightOfWall(2);
		ARENADATA::SETlengthOfWall(1);
		ARENADATA::SETsquareSize(50);
		break;
	case 5:
		ARENADATA::SETarenaHeight(1200);
		ARENADATA::SETarenaWidth(1200);
		ARENADATA::SETheightOfWall(2);
		ARENADATA::SETlengthOfWall(1);
		ARENADATA::SETsquareSize(50);
		break;

	default:
		break;
	}
}