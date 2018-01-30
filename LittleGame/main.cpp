#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include <crtdbg.h>
#include "ID3D.h"
#include "D3D.h"

// ----- TEST
#include "ActorObject.h"
#include "ControllerComponent.h"
#include "KeyboardComponent.h"
// ----- TEST


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameManager gm;

	ID3D* d3d = new D3D();
	Locator::provide(d3d);

	Locator::getD3D()->initializeWindow(hInstance, true, 800, 600, true);
	Locator::getD3D()->createSwapChain();

	// Initialize the game
	gm.init(hInstance, nCmdShow);

	// ----- TEST
	//ActorObject actor(0);
	//ControllerComponent controller(actor, 0);
	//KeyboardComponent keyboard(actor);


	// ----- TEST


	// Game loop
	while (gm.getIsRunning()) {
		// Update delta time
		Locator::getGameTime()->UpdateFrameTime();
		// Handle events & update & render
		gm.handleEvents();
		gm.update();
		gm.render();

		//controller.execute();
		//keyboard.execute();
	}

	gm.cleanup();
	d3d->cleanup();
	delete d3d;

	return 0;
}
