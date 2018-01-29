#pragma once
#ifndef LOCATOR_H
#define LOCATOR_H

#include "IGameTime.h"
#include "ID3D.h"

/* Service Locator pattern */

class Locator
{
private:
	static IGameTime* sGT;
	static ID3D* sID3D;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Provides the address of 'gameTime'(obj) to the 'sGT'(ptr) Locator object.
	2. Passes the pointer to 'gameTime'(obj) as a parameter.
	*/
	static void provide(IGameTime* gameTime) { sGT = gameTime; }
	static void provide(ID3D* d3d) { sID3D = d3d; }
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the 'sGT'(ptr).
	2. 'sGT'(ptr) points to the address of 'gameTime'(obj), thereby returning that address.
	*/
	static IGameTime* getGameTime() { return sGT; }
	static ID3D* getD3D() { return sID3D; }
};

#endif
