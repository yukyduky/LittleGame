#include "Locator.h"


IGameTime* Locator::sGT = nullptr;
ID3D* Locator::sID3D = nullptr;
IRandomGeneration* Locator::sRandomGeneration = nullptr;
IGlobalEvents* Locator::sGlobalEvents = nullptr;
IAudioManager* Locator::sAM = nullptr;