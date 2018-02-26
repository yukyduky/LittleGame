#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "MenuObject.h"

class MenuState;

enum class BEHAVIOR {GOSTART, GOOPTIONS, RESUMEGAME, STARTGAME, VOLUMEUP, VOLUMEDOWN, WINDOWSWITCH, QUIT};

class Button : public MenuObject
{
public:
	Button(ID2D1HwndRenderTarget* pRT, IDWriteTextFormat* pTF, MenuState* pMS, size_t ID, 
		XMFLOAT4 pos, D2D1::ColorF color, const WCHAR* text, BEHAVIOR behavior);
	~Button();
	void cleanUp();

	void SETNext(Button* nextB) { this->nextButton = nextB; };
	void SETPrev(Button* prevB) { this->prevButton = prevB; };

	Button* GETNext() { return this->nextButton; };
	Button* GETPrev() { return this->prevButton; };

	void selectButton() { this->selected = true; };
	void deSelectButton() { this->selected = false; };
	void onPress();
private:
	BEHAVIOR behavior;
	// Pointer to the MenuState
	MenuState* pMS = nullptr;
	
	Button* nextButton = nullptr;
	Button* prevButton = nullptr;

	bool selected;
	// The hidden Highlight that will be shown when the button is selected
	D2D1_RECT_F highlight;
	ID2D1SolidColorBrush * pHighlightColorBrush = nullptr;

	// Holds the text settings from D2D
	IDWriteTextFormat* pTF = nullptr;
	ID2D1SolidColorBrush * pTextColorBrush = nullptr;
	const WCHAR* text = nullptr;

	void render();
};


#endif // !BUTTON_H
