#include "Button.h"
#include "MenuState.h"

Button::Button(ID2D1HwndRenderTarget* pRT, IDWriteTextFormat* pTF, MenuState* pMS, size_t ID, 
	XMFLOAT4 pos, D2D1::ColorF color, const WCHAR* text, BEHAVIOR behavior) : MenuObject(pRT, ID, pos, color)
{
	this->behavior = behavior;
	this->pMS = pMS;
	this->pTF = pTF;
	this->selected = false;
	this->nextButton = this;
	this->prevButton = this;

	D2D1_SIZE_F rtSize = this->pRT->GetSize();
	highlight = D2D1::RectF(
		rtSize.width / 2 - this->menuSize.x + pos.x,
		rtSize.height / 2 - this->menuSize.y + pos.y,
		rtSize.width / 2 - this->menuSize.x + pos.z + 5,
		rtSize.height / 2 - this->menuSize.y + pos.w + 5
	);

	this->pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &this->pHighlightColorBrush);
	this->pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &this->pTextColorBrush);

	this->text = text;
	
}

Button::~Button()
{
}

void Button::onPress()
{
	switch (this->behavior)
	{
	case BEHAVIOR::GOSTART:
		this->pMS->displayMenu(MENUS::START);
		break;
	case BEHAVIOR::GOOPTIONS:
		this->pMS->displayMenu(MENUS::OPTIONS);
		break;
	case BEHAVIOR::STARTGAME:
		break;
	default:
		break;
	}
}

void Button::render()
{
	if (this->selected)
	{
		this->pRT->FillRectangle(&this->highlight, this->pHighlightColorBrush);
	}

	//Renders button quad
	MenuObject::render();

	this->pRT->DrawText(
		this->text,
		10,
		this->pTF,
		this->highlight,
		this->pTextColorBrush
	);
}