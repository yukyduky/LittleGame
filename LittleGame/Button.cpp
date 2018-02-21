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
		this->pos.x - 10.0f,
		this->pos.y,
		this->pos.x + this->size.x + 10.0f,
		this->pos.y + this->size.y
	);

	this->pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &this->pHighlightColorBrush);
	this->pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &this->pTextColorBrush);

	this->text = text;
	
}

Button::~Button()
{
	this->cleanUp();
}

void Button::cleanUp()
{
	SafeRelease(&this->pHighlightColorBrush);
	SafeRelease(&this->pTextColorBrush);

	MenuObject::cleanUp();
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
		this->pMS->startGame();
		break;
	case BEHAVIOR::VOLUMEUP:
		Locator::getAudioManager()->adjustMaster(true);
		break;
	case BEHAVIOR::VOLUMEDOWN:
		Locator::getAudioManager()->adjustMaster(false);
		break;
	case BEHAVIOR::WINDOWSWITCH:
		this->pMS->FullScreenSwitch();
		break;
		break;
	case BEHAVIOR::QUIT:
		this->pMS->quitMenu();
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

	//Renders the text ontop
	this->pRT->DrawText(
		this->text,
		wcslen(this->text),
		this->pTF,
		this->highlight,
		this->pTextColorBrush
	);
}