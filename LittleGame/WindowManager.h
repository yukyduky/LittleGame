#pragma once
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <Windows.h>

class WindowManager
{
private:
	HWND hwnd;
public:
	void InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
};

#endif // !WINDOWMANAGER_H
