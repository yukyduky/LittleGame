#include "MenuStatisticsState.h"

MenuStatisticsState MenuStatisticsState::sStatisticsMenuState;

MenuStatisticsState * MenuStatisticsState::getInstance()
{
	return &sStatisticsMenuState;
}

void MenuStatisticsState::init()
{
	MenuState::init();

	this->displayMenu(this->initStatsMenu());
}

Menu * MenuStatisticsState::initStatsMenu()
{
	Menu* menu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	const WCHAR* text = nullptr;
	std::wstring textStr;
	int nextID;

	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(nextID);
	menu->addQuad(object);

	if (Locator::getStatsHeader()->gameCompleted()) // Won
	{
		textStr = L"VICTORY! \nYou completed all 10 levels!";
		nextID = this->newID();
		object = new MenuObject(nextID,
			{ 50.0f,-100.0f, 300.0f,100.0f }, D2D1::ColorF::DeepSkyBlue,
			textStr);
		menu->addQuad(object);
	}
	else // Lost
	{
		textStr = L"GAME OVER! \n Last level: " + std::to_wstring(Locator::getStatsHeader()->getStats().level) + L" of 10";
		nextID = this->newID();
		object = new MenuObject(nextID,
			{ 50.0f,-100.0f, 300.0f,100.0f }, D2D1::ColorF::DeepSkyBlue,
			textStr);
		menu->addQuad(object);
	}


	//Loadout
	this->addLoadOut(menu);


	// Info 
	textStr = L"Kills: " + std::to_wstring(Locator::getStatsHeader()->getStats().kills);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,50.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Damage taken: " + std::to_wstring(Locator::getStatsHeader()->getStats().damageTaken);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,100.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Auto Glyph: " + std::to_wstring(Locator::getStatsHeader()->getStats().glyphs[0]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,150.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Fire Glyph: " + std::to_wstring(Locator::getStatsHeader()->getStats().glyphs[1]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,200.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Bomb Glyph: " + std::to_wstring(Locator::getStatsHeader()->getStats().glyphs[2]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,250.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Dash Glyph: " + std::to_wstring(Locator::getStatsHeader()->getStats().glyphs[3]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,300.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Buff Glyph: " + std::to_wstring(Locator::getStatsHeader()->getStats().glyphs[4]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,350.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Enemy Damage: " + std::to_wstring(Locator::getStatsHeader()->getStats().enemyUpg[0]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,400.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Enemy Health: " + std::to_wstring(Locator::getStatsHeader()->getStats().enemyUpg[1]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,450.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Enemy Amount: " + std::to_wstring(Locator::getStatsHeader()->getStats().enemyUpg[2]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,500.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	textStr = L"Enemy Speed: " + std::to_wstring(Locator::getStatsHeader()->getStats().enemyUpg[3]);
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,550.0f, 300.0f,50.0f }, D2D1::ColorF::DarkGoldenrod,
		textStr);
	menu->addQuad(object);

	//Buttons
	text = L"Restart";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,650.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::RESTARTGAME);
	menu->addButton(pButton);
	text = L"Quit";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,720.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);

	return menu;
}
