#pragma once
#ifndef D2D_H
#define D2D_H

#include "ID2D.h"

#include "Locator.h"

class D2D : public ID2D
{
public:
	// Register the window class and call methods for instantiating drawing resources
	virtual HRESULT Initialize();

	// Draw content.
	virtual HRESULT OnRender(std::vector<MenuObject*> objects);

	virtual ID2D1HwndRenderTarget* GETRenderTarget() { return this->m_pRenderTarget; }
	virtual IDWriteTextFormat* GETTextFormat() { return this->m_pTextFormat; }
	virtual void saveScreen() { this->saveScreenshot(); this->loadBitmap(); };
	virtual void closeMenu();
	virtual void cleanUp();
private:
	// D2D device
	ID2D1Factory* m_pDirect2dFactory = nullptr;
	// Render target, dose all calls to render
	ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
	// D2D device for text
	IDWriteFactory* m_pDirectWriteFactory = nullptr;
	// Holds formating for text, ea Font
	IDWriteTextFormat* m_pTextFormat = nullptr;

	// Initialize device-independent resources. Like factory
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	//Take a screenshot of the window and saves it to a .bmp
	void saveScreenshot();

	//Loads the pBitmap with the screenshot
	void loadBitmap();

	// Release device-dependent resource.
	void DiscardDeviceResources();

	//Background
	ID2D1SolidColorBrush * pGridColor = nullptr;

	IWICImagingFactory *pIWICFactory = nullptr;
	//PCWSTR uri = nullptr;
	UINT destinationWidth;
	UINT destinationHeight;
	ID2D1Bitmap* pBitmap = nullptr;
};


#endif // !D2D_H