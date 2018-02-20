#pragma once
#ifndef ARENAGLOBALS_H_
#define ARENAGLOBALS_H_

namespace ARENADATA {
		static int arenaWidth;
		static int arenaHeight;
		static int squareSize;
		static int lengthOfWall;
		static int heightOfWall;

		void SETarenaWidth(int width); //{ arenaWidth = width; }
		void SETarenaHeight(int height); // { arenaHeight = height; }
		void SETsquareSize(int size); // { squareSize = size; }
		void SETlengthOfWall(int length); // { lengthOfWall = length; }
		void SETheightOfWall(int height); // { heightOfWall = height; }

		int GETarenaWidth(); // { return arenaWidth; }
		int GETarenaHeight(); // { return arenaHeight; }
		int GETsquareSize(); // { return squareSize; }
		int GETlengthOfWall(); // { return lengthOfWall; }
		int GETheightOfWall(); // { return heightOfWall; }
}


#endif