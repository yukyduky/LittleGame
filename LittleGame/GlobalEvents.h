#pragma once
#ifndef GLOBALEVENTS_H
#define GLOBALEVENTS_H

#include "IGlobalEvents.h"
#include <stdio.h>
#include <map>

class GlobalEvents : public IGlobalEvents {
private:
	std::map<GLOBALMESSAGES, GLOBALMESSAGES> messageMap;
	int enemyDeathCount = 0;

public:
	GlobalEvents();

	void generateMessage(GLOBALMESSAGES message);
	bool pollEvent(GLOBALMESSAGES &msg);

	std::map<GLOBALMESSAGES, GLOBALMESSAGES> GETmessageMap();
	void SETmessageMap(std::map<GLOBALMESSAGES, GLOBALMESSAGES> messageMap);

	void incrementEnemyDeathCount() { this->enemyDeathCount++; }
	int getEnemyDeathCount();
};

#endif