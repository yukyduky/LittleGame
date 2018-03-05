#include "StatisticsMenuState.h"

StatisticsMenuState StatisticsMenuState::sStatisticsMenuState;

StatisticsMenuState * StatisticsMenuState::getInstance()
{
	return &sStatisticsMenuState;
}

void StatisticsMenuState::init()
{
	MenuState::init();

	this->displayMenu(this->initStatsMenu());
}

Menu * StatisticsMenuState::initStatsMenu()
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

	//Buttons
	text = L"Quit";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,450.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);


	return menu;
}
