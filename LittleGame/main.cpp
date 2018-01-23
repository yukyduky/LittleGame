#include <Windows.h>
#include "D3D.h"
#include "GameManager.h"
#include "Locator.h"
#include <crtdbg.h>
#include "ForwardPipelineTest.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameManager gm;

	// Initialize window
	D3D::initializeWindow(hInstance, true, 1920, 1080, true);

	// Initialize DirectX
	D3D::initializeDirectX();

	// Initialize the game
	gm.init(hInstance, nCmdShow);

	FPLT test;
	test.init();

	// Game loop
	while (gm.getIsRunning()) {
		// Update delta time
		Locator::getGameTime()->UpdateFrameTime();
		// Handle events & update & render
		gm.handleEvents();
		gm.update();
		gm.render();
	}

	gm.cleanup();

	return 0;
}
