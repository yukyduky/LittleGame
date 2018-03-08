#include "GlobalEvents.h"

GlobalEvents::GlobalEvents() {

}

void GlobalEvents::generateMessage(GLOBALMESSAGES message) {
	this->messageMap.insert(std::make_pair(message, message));
}

bool GlobalEvents::pollEvent(GLOBALMESSAGES &msg) {
	bool returnValue = false;

	if (!this->messageMap.empty()) {
		msg = (*this->messageMap.begin()).second;
		this->messageMap.erase(this->messageMap.begin());
		returnValue = true;
	}

	return returnValue;
}

std::map<GLOBALMESSAGES, GLOBALMESSAGES> GlobalEvents::GETmessageMap() {
	return this->messageMap;
}

void GlobalEvents::SETmessageMap(std::map<GLOBALMESSAGES, GLOBALMESSAGES> messageMap) {
	this->messageMap = messageMap;
}

int GlobalEvents::getEnemyDeathCount()
{
	int returnValue = this->enemyDeathCount;
	this->enemyDeathCount = 0;

	return returnValue;
}