#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "MenuObject.h"

enum class BEHAVIOR {GOSTART, GOOPTIONS, STARTGAME};

class MenuState;

class Button : public MenuObject
{
public:
	Button(size_t ID, XMFLOAT3 pos, BEHAVIOR behavior);
	Button(size_t ID, XMFLOAT3 pos, BEHAVIOR behavior, MenuState* pMS);
	~Button();

	void SETNext(Button* nextB) { this->nextButton = nextB; };
	void SETPrev(Button* prevB) { this->prevButton = prevB; };

	void onPress();
	Button* GETNext() { return this->nextButton; };
	Button* GETPrev() { return this->prevButton; };
private:
	BEHAVIOR behavior;
	MenuState* pMS;
	
	Button* nextButton;
	Button* prevButton;
};


#endif // !BUTTON_H
