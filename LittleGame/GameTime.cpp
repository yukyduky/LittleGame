#include "GameTime.h"
#include <dwrite.h>


GameTime::GameTime()
{
	this->frequency = 0.0;
	this->CounterStart = 0;
	this->prevCurrentCount = 0;
	this->deltaTime = 0.0;
}

void GameTime::StartTimer()
{
	LARGE_INTEGER currentCount;
	// Gets the frequency of the performance counter which is fixed at boot and only needed to be stored once
	QueryPerformanceFrequency(&currentCount);
	this->frequency = double(currentCount.QuadPart);

	// Get the current value of the performance counter since boot
	QueryPerformanceCounter(&currentCount);
	this->CounterStart = currentCount.QuadPart;
}

double GameTime::GetTime()
{
	LARGE_INTEGER currentCount;

	QueryPerformanceCounter(&currentCount);
	return double(currentCount.QuadPart - this->CounterStart) / this->frequency;
}

void GameTime::UpdateFrameTime()
{
	LARGE_INTEGER currentCount;
	__int64 frameCount = (__int64)0.0;

	QueryPerformanceCounter(&currentCount);

	// Gets the count since last frame
	frameCount = currentCount.QuadPart - this->prevCurrentCount;
	// Stores the current count for the next frame
	this->prevCurrentCount = currentCount.QuadPart;

	// Should never happen
	if (frameCount < 0.0f) {
		frameCount = (__int64)0.0;
	}

	// Count divided by frequency equals time in milliseconds
	this->deltaTime = frameCount / this->frequency;
}

const double GameTime::getDeltaTime()
{
	return this->deltaTime;
}
