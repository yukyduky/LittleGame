#pragma once
#ifndef ID2D_H
#define ID2D_H

#include "MenuObject.h"

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class ID2D
{
public:
	// Register the window class and call methods for instantiating drawing resources
	virtual HRESULT Initialize() = 0;

	// Draw content.
	virtual HRESULT OnRender(std::vector<MenuObject*> objects) = 0;
	virtual ID2D1HwndRenderTarget* GETRenderTarget() = 0;
	virtual IDWriteTextFormat* GETTextFormat() = 0;
};


#endif // !ID2D_H