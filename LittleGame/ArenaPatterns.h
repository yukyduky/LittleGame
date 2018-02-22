#pragma once
#ifndef FLOORFALLPATTERNS_H_
#define FLOORFALLPATTERNS_H_

#include "ArenaGlobals.h"
#include <vector>
#include <DirectXMath.h>
#include <d3d11.h>

struct Index
{
	int x;
	int y;

	Index() {};
	Index(int x, int y) { this->x = x; this->y = y; }
};

struct FloorFallData {
	double time; //Time between each iteration.
	int popsPerIteration; //Nr of tiles that falls per iteration.
	bool recoverMode; //Determines if the floor is going to fall or be restored at the end of the stage.
	std::vector<Index> pattern; //Fall order.
	std::vector<Index> recoverPattern; //Recovery order.
};

struct WallData {
	int nrVertical;
	int nrHorizontal;
	int* rowL;
	int* rowR;
	int* rowT;
	int* rowB;

	WallData(int nrVertical, int nrHorizontal) {
		this->nrVertical = nrVertical;
		this->nrHorizontal = nrHorizontal;
		this->rowL = new int[nrVertical];
		this->rowR = new int[nrVertical];
		this->rowT = new int[nrHorizontal];
		this->rowB = new int[nrHorizontal];
	}
	~WallData() {
		delete this->rowL;
		delete this->rowR;
		delete this->rowT;
		delete this->rowB;
	}
};

class ArenaPatterns 
{
private:
	int maxFloorNum;
	int maxWallNum;
	int maxArenaNum;

public:
	ArenaPatterns();
	~ArenaPatterns();
	void createFloorPattern(int nr, FloorFallData& pattern);
	void createEasyFloorPatterns(std::vector<FloorFallData>& easy);
	void createMediumFloorPatterns(std::vector<FloorFallData>& medium);
	void createHardFloorPatterns(std::vector<FloorFallData>& hard);
	int GETmaxFloorNum();
	void createWallPattern(int nr, WallData& pattern);
	int GETmaxWallNum();
	void createArenaData();
};




#endif // !FLOORFALLPATTERNS_H_
