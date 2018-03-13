#include "Button.h"
#include "PauseMenuState.h"
#include "HomeMenuState.h"
#include "RewardMenuState.h"

Button::Button(MenuState* pMS, size_t ID,
	XMFLOAT4 pos, D2D1::ColorF color, std::wstring text, BEHAVIOR behavior) : MenuObject(ID, pos, color, text)
{
	init(pMS, behavior);
}

Button::Button(MenuState* pMS, size_t ID,
	XMFLOAT4 pos, D2D1::ColorF color, std::wstring text, BEHAVIOR behavior,
	NAME spellname, GLYPHTYPE glyph) : MenuObject(ID, pos, color, text)
{
	init(pMS, behavior);

	this->spellname = spellname;
	this->glyph = glyph;
}

Button::Button(MenuState * pMS, size_t ID, 
	XMFLOAT4 pos, D2D1::ColorF color, std::wstring text, BEHAVIOR behavior, 
	ENEMYUPGRADE eneUpg) : MenuObject(ID, pos, color, text)
{
	init(pMS, behavior);

	this->eneUpg = eneUpg;
}

Button::~Button()
{
	this->cleanUp();
}

void Button::init(MenuState * pMS, BEHAVIOR behavior)
{
	this->behavior = behavior;
	this->pMS = pMS;
	this->pTF = Locator::getD2D()->GETTextFormat();
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
	//this->pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &this->pTextColorBrush);

	//this->text = text;
}

void Button::cleanUp()
{
	SafeRelease(&this->pHighlightColorBrush);
	//SafeRelease(&this->pTextColorBrush);

	MenuObject::cleanUp();
}

Button * Button::GETNext(int nrOfChoosen)
{
	if (nrOfChoosen <= 0 && this->nextButton->behavior == BEHAVIOR::ADDGLYPH)
	{
		return this->nextButton->GETNext(nrOfChoosen);
	}
	return this->nextButton;
}

Button * Button::GETPrev(int nrOfChoosen)
{
	if (nrOfChoosen <= 0 && this->prevButton->behavior == BEHAVIOR::ADDGLYPH)
	{
		return this->prevButton->GETPrev(nrOfChoosen);
	}
	return this->prevButton;
}

void Button::deSelectButton()
{
	if (!this->choosen)
	{
		this->selected = false;
	}
}

void Button::onPress()
{
	bool currSetting;
	switch (this->behavior)
	{
	case BEHAVIOR::GOSTART:
		this->pMS->displayMenu(static_cast<PauseMenuState*>(this->pMS)->initStartMenu());
		break;
	case BEHAVIOR::GOSTART_HOME:
		this->pMS->displayMenu(static_cast<HomeMenuState*>(this->pMS)->initStartMenu());
		break;
	case BEHAVIOR::GOCONTROLS:
		this->pMS->displayMenu(static_cast<HomeMenuState*>(this->pMS)->initControlsMenu());
		break;
	case BEHAVIOR::GOOPTIONS:
		this->pMS->displayMenu(static_cast<PauseMenuState*>(this->pMS)->initOptionsMenu());
		break;
	case BEHAVIOR::RESUMEGAME:
		this->pMS->resumeGame();
		break;
	case BEHAVIOR::STARTGAME:
		this->pMS->startGame();
		break;
	case BEHAVIOR::RESTARTGAME:
		this->pMS->restartGame();
		break;

		//Options
	case BEHAVIOR::VOLUMEUP:
		Locator::getAudioManager()->adjustMaster(true);
		break;
	case BEHAVIOR::VOLUMEDOWN:
		Locator::getAudioManager()->adjustMaster(false);
		break;
	case BEHAVIOR::VOLUMEUP_E:
		Locator::getAudioManager()->adjustEffects(5.0f);
		break;
	case BEHAVIOR::VOLUMEDOWN_E:
		Locator::getAudioManager()->adjustEffects(-5.0f);
		break;
	case BEHAVIOR::VOLUMEUP_M:
		Locator::getAudioManager()->adjustMusic(5.0f);
		break;
	case BEHAVIOR::VOLUMEDOWN_M:
		Locator::getAudioManager()->adjustMusic(-5.0f);
		break;
	case BEHAVIOR::WINDOWSWITCH:
		static_cast<PauseMenuState*>(this->pMS)->FullScreenSwitch();
		break;
	case BEHAVIOR::USECONTROLLER:
		currSetting = GamePlayState::getInstance()->switchControllerInput();
		if (currSetting)
		{
			this->text = L"Input: Controller";
		}
		else
		{
			this->text = L"Input: Keyboard";
		}
		break;

	// Rewardmenu
	case BEHAVIOR::ADDGLYPH:
		this->choosen = true;
		static_cast<RewardMenuState*>(this->pMS)->GETPlayer()->changeSpell((int)this->spellname, (int)this->glyph);
		Locator::getStatsHeader()->addGlyph((int)this->spellname, (int)this->glyph);
		this->nextButton->SETPrev(this->prevButton);
		this->prevButton->SETNext(this->nextButton);
		break;
		// Rewardmenu
	case BEHAVIOR::ADDENEMYUPG:
		this->choosen = true;
		//HERE GOES THE FUNCTION TO UPGRADE ENEMIES
		Locator::getStatsHeader()->addUpgrade((int)this->eneUpg);
		this->nextButton->SETPrev(this->prevButton);
		this->prevButton->SETNext(this->nextButton);
		break;
	case BEHAVIOR::REWSTARTGAME:
		static_cast<RewardMenuState*>(this->pMS)->startGame();
		break;

	// Stats window
	case BEHAVIOR::GOSTATS:
		this->pMS->statsWindow();
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


}