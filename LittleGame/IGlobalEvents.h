#pragma once
#ifndef IGLOBALEVENTS_H
#define IGLOBALEVENTS_H

enum class GLOBALMESSAGES { PLAYERDIED, SIZE };

class IGlobalEvents {
public:
	virtual void generateMessage(GLOBALMESSAGES message) = 0;
	virtual bool pollEvent(GLOBALMESSAGES &msg) = 0;
};

#endif