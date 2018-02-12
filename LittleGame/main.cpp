#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include "ID3D.h"
#include "D3D.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_CrtSetBreakAlloc(246); // 1134 1133 1132

	ID3D* d3d = new D3D();
	Locator::provide(d3d);

	Locator::getD3D()->initializeWindow(hInstance, true, 1920, 1080, true);
	Locator::getD3D()->createSwapChain();

	GameManager gm;
	// Initialize the game
	gm.init(hInstance, nCmdShow);
	double deltaTime;
	double timeLastFrame = 0;
	int frames = 0;
	float tester123 = 0.0f;
	char msgbuf[20];

	// Game loop
	while (gm.getIsRunning()) {
		// Update delta time
		Locator::getGameTime()->UpdateFrameTime();
		deltaTime = Locator::getGameTime()->getDeltaTime();
		timeLastFrame += deltaTime * 1000;
		
		// Handle events & update & render
		gm.handleEvents();
		gm.update();
		gm.render();
		frames++;

		if (timeLastFrame > 300.0) {
			sprintf_s(msgbuf, "FPS: %d\n", frames);
			frames = 0;
			timeLastFrame = 0;
			OutputDebugStringA(msgbuf);
			tester123 = Locator::getRandomGenerator()->GenerateFloat(32, 38);
			sprintf_s(msgbuf, "FLOAT: %f\n", tester123);
			OutputDebugStringA(msgbuf);
		}

	}

	gm.cleanUp();
	d3d->cleanup();
	delete d3d;

	_CrtDumpMemoryLeaks();
	return 0;
}
