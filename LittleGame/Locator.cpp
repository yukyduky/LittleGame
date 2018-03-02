#include "Locator.h"


IGameTime* Locator::sGT = nullptr;
ID3D* Locator::sID3D = nullptr;
ID2D* Locator::sID2D = nullptr;
IRandomGeneration* Locator::sRandomGeneration = nullptr;
IGlobalEvents* Locator::sGlobalEvents = nullptr;
IAudioManager* Locator::sAM = nullptr;
IStatsHeader* Locator::sSH = nullptr;