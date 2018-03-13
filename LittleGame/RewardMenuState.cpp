#include "RewardMenuState.h"
#include "GameManager.h"
#include "Button.h"
#include "StateManager.h"
//#include "Spell.h"

RewardMenuState RewardMenuState::sRewardMenuState;

WCHAR * RewardMenuState::getGlyphName(int name, int glyph)
{
	WCHAR* text = nullptr;

	switch (name)
	{
	case 0: //NAME::AUTOATTACK:
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"AutoA NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"AutoA \n Tripple-burst";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"AutoA \n Sniper";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"AutoA \n Firerate";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	case 1: //NAME::FIRE:
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"Fire NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"Fire \n Flamethrower";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"Fire \n Enlarge";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"Fire \n Railgun";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	case 2: //NAME::BOMB:
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"Bomb NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"Bomb \n Splinter Bomb";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"Bomb \n Mine";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"Bomb \n Black-hole";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	case 3: //NAME::DASH:
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"Dash NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"Dash \n Retreat";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"Dash \n Long-dash";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"Dash \n Everlasting";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	case 4: //NAME::BUFF:
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"Buff NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"Buff \n Berserk-mode";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"Buff \n Fear";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"Buff \n Keep Speed";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	default:
		text = L"ERROR";
		break;
	}

	return text;
}

RewardMenuState * RewardMenuState::getInstance()
{
	return &sRewardMenuState;
}

void RewardMenuState::init()
{	
	MenuState::init();
	this->displayMenu(this->initLootMenu());
}

void RewardMenuState::handleEvents(GameManager * gm) {
	MSG msg;
	GLOBALMESSAGES globalmsg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed or the quit bool is true
		if (msg.message == WM_QUIT) {
			gm->quit();
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.wParam)
			{
			case VK_UP:
			case 0x57:
				this->currMenu->goUp();
				break;
			case VK_DOWN:
			case 0x53:
				this->currMenu->goDown();
				break;
			case VK_RETURN:
			case VK_SPACE:
				this->currMenu->pressButton();
				if (this->currMenu->GETCurrent()->GETBehavior() == BEHAVIOR::ADDGLYPH)
				{
					if (this->nrOfLoot > 0)
					{
						this->displayMenu(this->initLootMenu());
					}
					else
					{
						this->displayMenu(this->initEnemyUpgradeMenu());
					}
				}
				else if (this->currMenu->GETCurrent()->GETBehavior() == BEHAVIOR::ADDENEMYUPG)
				{
					this->displayMenu(this->initNextLevelMenu());
				}
				break;
			default:
				break;
			}
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	while (Locator::getGlobalEvents()->pollEvent(globalmsg)) {
		if (globalmsg == GLOBALMESSAGES::STARTGAME) {
			StateManager::changeState(GamePlayState::getInstance());
		}
		else if (globalmsg == GLOBALMESSAGES::RESUMEGAME) {
			StateManager::popState();
		}
	}
}


Menu * RewardMenuState::initLootMenu()
{
	Menu* menu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	WCHAR* text = nullptr;
	std::wstring textStr;
	int nextID;

	// Because the loot is presented at the start
	this->nrOfLoot--;


	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(this->newID(),
		{ 0.0f,0.0f, 400.0f,700.0f }, D2D1::ColorF::DarkMagenta);
	menu->addQuad(object);
	textStr = L"Next level: " + std::to_wstring(Locator::getStatsHeader()->getStats().level) + L" of 10";
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,-100.0f, 300.0f,100.0f }, D2D1::ColorF::DeepSkyBlue,
		textStr);
	menu->addQuad(object);

	//Loadout
	this->addLoadOut(menu);
	
	//Buttons
	XMFLOAT2 start{ 100.0f, 50.0f};

	std::list<XMINT2> prev;

	for (int j = 0; j < 3; j++)
	{
		bool cpyFound = true;
		NAME name;
		GLYPHTYPE glyph;
		D2D1::ColorF color = D2D1::ColorF::WhiteSmoke;

		while (cpyFound)
		{
			name = (NAME)Locator::getRandomGenerator()->GenerateInt(0, 4 /*Number of player spells*/ );
			glyph = (GLYPHTYPE)Locator::getRandomGenerator()->GenerateInt(1, (int)GLYPHTYPE::SIZE - 1);

			cpyFound = false;
			for (auto &i : prev)
			{
				if (i.x == (int)name && i.y == (int)glyph)
				{
					cpyFound = true;
				}
			}
		}
		prev.push_back({ (int)name, (int)glyph });

		switch (name)
		{
		case NAME::AUTOATTACK:
			color = D2D1::ColorF::DarkGoldenrod;
			break;
		case NAME::FIRE:
			color = D2D1::ColorF::Orchid;
			break;
		case NAME::BOMB:
			color = D2D1::ColorF::Gray;
			break;
		case NAME::DASH:
			color = D2D1::ColorF::Orange;
			break;
		case NAME::BUFF:
			color = D2D1::ColorF::RoyalBlue;
			break;
		}

		text = this->getGlyphName((int)name, (int)glyph);

		pButton = new Button(this, this->newID(),
			{ start.x,start.y, 200.0f,100.0f }, color,
			text, BEHAVIOR::ADDGLYPH,
			name, glyph);
		menu->addButton(pButton);

		start.y += 105.0f;
	}

	start.y = 380.0f;

	nextID = this->newID();
	text = L"End to stats";
	pButton = new Button(this, nextID,
		{ 100.0f,start.y, 200.0f,100.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTATS);
	menu->addButton(pButton);

	start.y += 120.0f;
	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this, nextID,
		{ 100.0f,start.y, 200.0f,100.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);

	return menu;
}

Menu * RewardMenuState::initEnemyUpgradeMenu()
{
	Menu* menu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	WCHAR* text = nullptr;
	std::wstring textStr;
	int nextID;

	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(this->newID(),
		{ 0.0f,0.0f, 400.0f,700.0f }, D2D1::ColorF::DarkMagenta);
	menu->addQuad(object);
	textStr = L"Next level: " + std::to_wstring(Locator::getStatsHeader()->getStats().level) + L" of 10";
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,-100.0f, 300.0f,100.0f }, D2D1::ColorF::DeepSkyBlue,
		textStr);
	menu->addQuad(object);

	//Loadout
	this->addLoadOut(menu);

	//Buttons
	XMFLOAT2 start{ 30.0f, 50.0f };

	std::list<int> prev;
	for (int j = 0; j < 3; j++)
	{
		bool cpyFound = true;
		ENEMYUPGRADE eneUpg;
		D2D1::ColorF color = D2D1::ColorF::DarkSlateGray;

		while (cpyFound)
		{
			eneUpg = (ENEMYUPGRADE)Locator::getRandomGenerator()->GenerateInt(0, (int)ENEMYUPGRADE::SIZE - 1);

			cpyFound = false;
			for (auto &i : prev)
			{
				if (i == (int)eneUpg)
				{
					cpyFound = true;
				}
			}
		}
		prev.push_back((int)eneUpg);

		switch (eneUpg)
		{
		case ENEMYUPGRADE::DAMAGE:
			text = L"Damage";
			break;
		case ENEMYUPGRADE::HEALTH:
			text = L"Health";
			break;
		case ENEMYUPGRADE::AMOUNT:
			text = L"Amount";
			break;
		case ENEMYUPGRADE::SPEED:
			text = L"Speed";
			break;
		default:
			text = L"ERROR";
			break;
		}

		pButton = new Button(this, this->newID(),
			{ start.x,start.y, 100.0f,100.0f }, color,
			text, BEHAVIOR::ADDENEMYUPG,
			eneUpg);
		menu->addButton(pButton);

		start.x += 120.0f;
	}
	start.x = 30.0f;

	start.y = 380.0f;

	nextID = this->newID();
	text = L"End to stats";
	pButton = new Button(this, nextID,
		{ 100.0f,start.y, 200.0f,100.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTATS);
	menu->addButton(pButton);

	start.y += 120.0f;

	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this, nextID,
		{ 100.0f,start.y, 200.0f,100.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);

	return menu;
}

Menu * RewardMenuState::initNextLevelMenu()
{
	Menu* menu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	WCHAR* text = nullptr;
	std::wstring textStr;
	int nextID;

	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(this->newID(),
		{ 0.0f,0.0f, 400.0f,700.0f }, D2D1::ColorF::DarkMagenta);
	menu->addQuad(object);
	textStr = L"Next level: " + std::to_wstring(Locator::getStatsHeader()->getStats().level) + L" of 10";
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,-100.0f, 300.0f,100.0f }, D2D1::ColorF::DeepSkyBlue,
		textStr);
	menu->addQuad(object);

	//Loadout
	this->addLoadOut(menu);

	//Buttons
	XMFLOAT2 start{ 30.0f, 50.0f };

	text = L"Next level";
	pButton = new Button(this, this->newID(),
		{ 100.0f,50.0f, 200.0f,150.0f }, D2D1::ColorF::GreenYellow,
		text, BEHAVIOR::REWSTARTGAME);
	menu->addButton(pButton);

	start.y = 380.0f;

	nextID = this->newID();
	text = L"End to stats";
	pButton = new Button(this, nextID,
		{ 100.0f,start.y, 200.0f,100.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTATS);
	menu->addButton(pButton);

	start.y += 120.0f;

	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this, nextID,
		{ 100.0f,start.y, 200.0f,100.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);

	return menu;
}

void RewardMenuState::provide(ActorObject * player)
{
	this->player = player;

	for (int i = 0; i < 5; i++)
	{
		this->player->changeSpell(i, Locator::getStatsHeader()->getStats().glyphs[i]);
	}
}

void RewardMenuState::startGame()
{
	this->player->switchSpell();
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::RESUMEGAME);
}
