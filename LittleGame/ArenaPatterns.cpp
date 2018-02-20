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
	//If a faulty nr is entered the floor will not fall at all.
	default:
		break;
	}
}

int ArenaPatterns::GETmaxFloorNum()
{
	return this->maxFloorNum;
}

void ArenaPatterns::createWallPattern(int nr, WallData& pattern) {


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
	default:
		break;
	}
}