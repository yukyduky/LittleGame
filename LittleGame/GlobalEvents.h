#pragma once
#ifndef GLOBALEVENTS_H
#define GLOBALEVENTS_H

#include "IGlobalEvents.h"
#include <stdio.h>
#include <deque>

class GlobalEvents : public IGlobalEvents {
private:
	std::deque<GLOBALMESSAGES> messageList;

public:
	GlobalEvents();

	void generateMessage(GLOBALMESSAGES message);
	bool pollEvent(GLOBALMESSAGES &msg);

	std::deque<GLOBALMESSAGES> GETmessageList();
	void SETmessageList(std::deque<GLOBALMESSAGES> messageList);
};

#endif