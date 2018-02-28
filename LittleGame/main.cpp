#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include "ID3D.h"
#include "ID2D.h"
#include "D3D.h"
#include "D2D.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtMemState s1;
	_CrtMemCheckpoint(&s1);
	// 7295 addComponent (AIComponent)
	// 258, 365, 380, 381 something in audiomanager
	// 1936 something with the quadtree initialization
	// 6054 something with KeyboardInput
	// 6063, 6074 something in KeyboardInput or InputComponent
	//	_CrtSetBreakAlloc(6114);
#endif

	ID3D* d3d = new D3D();
	ID2D* d2d = new D2D();

	Locator::provide(d3d);
	Locator::provide(d2d);

	Locator::getD3D()->initializeWindow(hInstance, true, 1920, 1080, true);
	Locator::getD3D()->createSwapChain();

	Locator::getD2D()->Initialize();
	
	GameManager gm;
	// Initialize the game
	gm.init(hInstance, nCmdShow);
	double deltaTime = 0.0;
	double timeLastFrame = 0.0;
	int frames = 0;
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

		if (timeLastFrame > 1000.0) {
			sprintf_s(msgbuf, "FPS: %d\n", frames);
			frames = 0;
			timeLastFrame = 0.0;
			OutputDebugStringA(msgbuf);
		}
	}

	gm.cleanUp();
	d3d->cleanup();
	delete d3d;

#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	_CrtMemDumpAllObjectsSince(&s1);
#endif
	return 0;
}
