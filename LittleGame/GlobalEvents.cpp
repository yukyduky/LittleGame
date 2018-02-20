#include "GlobalEvents.h"

GlobalEvents::GlobalEvents() {

}

void GlobalEvents::generateMessage(GLOBALMESSAGES message) {
	this->messageList.push_back(message);
}

bool GlobalEvents::pollEvent(GLOBALMESSAGES &msg) {
	bool returnValue = false;

	if (!this->messageList.empty()) {
		msg = this->messageList.front();
		this->messageList.pop_front();
		returnValue = true;
	}

	return returnValue;
}

std::deque<GLOBALMESSAGES> GlobalEvents::GETmessageList() {
	return this->messageList;
}

void GlobalEvents::SETmessageList(std::deque<GLOBALMESSAGES> messageList) {
	this->messageList = messageList;
}