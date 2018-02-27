#include "Button.h"
#include "MainMenuState.h"
#include "RewardMenuState.h"

Button::Button(ID2D1HwndRenderTarget* pRT, IDWriteTextFormat* pTF, MenuState* pMS, size_t ID,
	XMFLOAT4 pos, D2D1::ColorF color, const WCHAR* text, BEHAVIOR behavior) : MenuObject(pRT, ID, pos, color)
{
	init(pTF, pMS, text, behavior);
	
}

Button::Button(ID2D1HwndRenderTarget* pRT, IDWriteTextFormat* pTF, MenuState* pMS, size_t ID,
	XMFLOAT4 pos, D2D1::ColorF color, const WCHAR* text, BEHAVIOR behavior,
	NAME spellname, GLYPHTYPE glyph) : MenuObject(pRT, ID, pos, color)
{
	init(pTF, pMS, text, behavior);

	this->spellname = spellname;
	this->glyph = glyph;
}

Button::~Button()
{
	this->cleanUp();
}

void Button::init(IDWriteTextFormat * pTF, MenuState * pMS, const WCHAR * text, BEHAVIOR behavior)
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
		this->pMS->displayMenu(static_cast<MainMenuState*>(this->pMS)->initStartMenu());
		break;
	case BEHAVIOR::GOOPTIONS:
		this->pMS->displayMenu(static_cast<MainMenuState*>(this->pMS)->initOptionsMenu());
		break;
	case BEHAVIOR::RESUMEGAME:
		this->pMS->resume();
		break;
	case BEHAVIOR::STARTGAME:
		this->pMS->startGame();
		break;
	case BEHAVIOR::NEWGAME:
		static_cast<RewardMenuState*>(this->pMS)->startGame();
		break;
	case BEHAVIOR::VOLUMEUP:
		Locator::getAudioManager()->adjustMaster(true);
		break;
	case BEHAVIOR::VOLUMEDOWN:
		Locator::getAudioManager()->adjustMaster(false);
		break;
	case BEHAVIOR::WINDOWSWITCH:
		static_cast<MainMenuState*>(this->pMS)->FullScreenSwitch();
		break;

	case BEHAVIOR::ADDGLYPH:
		static_cast<RewardMenuState*>(this->pMS)->GETPlayer()->changeSpell((int)this->spellname, (int)this->glyph);
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