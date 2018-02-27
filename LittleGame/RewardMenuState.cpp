#include "RewardMenuState.h"
#include "GameManager.h"
#include "Button.h"
#include "StateManager.h"

RewardMenuState RewardMenuState::sRewardMenuState;

RewardMenuState * RewardMenuState::getInstance()
{
	return &sRewardMenuState;
}

void RewardMenuState::init()
{
	MenuState::init();

	this->displayMenu(this->initRewardMenu());
}


Menu * RewardMenuState::initRewardMenu()
{
	Menu* menu;
	MenuObject* object;
	Button* pButton;
	WCHAR* text;
	int nextID;

	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(this->objD2D.GETRenderTarget(), nextID);
	menu->addQuad(object);

	//Buttons
	nextID = this->newID();
	text = L"Next level";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,50, 200,150 }, D2D1::ColorF::GreenYellow,
		text, BEHAVIOR::REWSTARTGAME);
	menu->addButton(pButton);

	nextID = this->newID();
	text = L"Auto Glyph1";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,250, 200,50 }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::ADDGLYPH,
		NAME::FIRE, GLYPHTYPE::GLYPH1);
	menu->addButton(pButton);

	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,350, 200,50 }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);


	//this->menus[MENUS::START] = menu;
	return menu;
}

void RewardMenuState::provide(ActorObject* player)
{
	this->player = player;
}

void RewardMenuState::startGame()
{
	this->player->switchSpell();
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::RESUMEGAME);
}
