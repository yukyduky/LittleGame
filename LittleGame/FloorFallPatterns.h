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

	Index(int x, int y) { this->x = x; this->y = y; }
};

struct FloorFallData {
	double time;
	int popsPerIteration;
	std::vector<Index> pattern;
	std::vector<Index> recoverPattern;
};

class FFPattern 
{
private:

public:
	 void createPattern(int nr, FloorFallData& pattern);
};




#endif // !FLOORFALLPATTERNS_H_
