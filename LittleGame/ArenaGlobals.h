#pragma once
#ifndef ARENAGLOBALS_H_
#define ARENAGLOBALS_H_

#define TIMEBETWEENPATTERNS 20
#define GRAVITY -9.82

namespace ARENADATA {
		static int arenaWidth;
		static int arenaHeight;
		static int squareSize;
		static int lengthOfWall;
		static int heightOfWall;

		void SETarenaWidth(int width);
		void SETarenaHeight(int height);
		void SETsquareSize(int size);
		void SETlengthOfWall(int length);
		void SETheightOfWall(int height);

		int GETarenaWidth();
		int GETarenaHeight();
		int GETsquareSize();
		int GETlengthOfWall();
		int GETheightOfWall();
}


#endif