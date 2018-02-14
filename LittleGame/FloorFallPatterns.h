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

class FFPattern 
{
private:
	int maxNum = 2;
public:
	 void createPattern(int nr, FloorFallData& pattern);
	 int GETmaxNum();
};




#endif // !FLOORFALLPATTERNS_H_
