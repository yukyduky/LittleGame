#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "MenuObject.h"
#include "Spell.h"

class MenuState;

enum class BEHAVIOR {
	GOSTART, GOSTART_HOME, GOCONTROLS, GOOPTIONS, RESUMEGAME, STARTGAME, RESTARTGAME, NEWGAME, 
	VOLUMEUP, VOLUMEDOWN, VOLUMEUP_E, VOLUMEDOWN_E, VOLUMEUP_M, VOLUMEDOWN_M, WINDOWSWITCH, USECONTROLLER,
	ADDGLYPH, ADDENEMYUPG, REWSTARTGAME, GOSTATS,
	QUIT
};


class Button : public MenuObject
{
public:
	Button(MenuState* pMS, size_t ID, 
		XMFLOAT4 pos, D2D1::ColorF color, std::wstring text, BEHAVIOR behavior);
	Button(MenuState* pMS, size_t ID,
		XMFLOAT4 pos, D2D1::ColorF color, std::wstring text, BEHAVIOR behavior,
		NAME spellname, GLYPHTYPE glyph);
	Button(MenuState* pMS, size_t ID,
		XMFLOAT4 pos, D2D1::ColorF color, std::wstring text, BEHAVIOR behavior,
		ENEMYUPGRADE eneUpg);
	~Button();
	void init(MenuState* pMS, BEHAVIOR behavior);
	void cleanUp();

	void SETNext(Button* nextB) { this->nextButton = nextB; };
	void SETPrev(Button* prevB) { this->prevButton = prevB; };

	Button* GETNext(int nrOfChoosen);
	Button* GETPrev(int nrOfChoosen);
	BEHAVIOR GETBehavior() { return this->behavior; };

	void selectButton() { this->selected = true; };
	void deSelectButton();
	void onPress();
private:
	BEHAVIOR behavior;
	// Pointer to the MenuState
	MenuState* pMS = nullptr;
	
	// Used for updating spells
	NAME spellname;
	GLYPHTYPE glyph;
	//Used for upgrading enemies
	ENEMYUPGRADE eneUpg;

	Button* nextButton = nullptr;
	Button* prevButton = nullptr;

	bool selected;
	bool choosen = false;
	// The hidden Highlight that will be shown when the button is selected
	D2D1_RECT_F highlight;
	ID2D1SolidColorBrush * pHighlightColorBrush = nullptr;
	//ID2D1SolidColorBrush * pTextColorBrush = nullptr;

	// Holds the text settings from D2D
	IDWriteTextFormat* pTF = nullptr;

	void render();
};


#endif // !BUTTON_H
