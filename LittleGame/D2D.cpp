#include "D2D.h"

HRESULT D2D::Initialize()
{
	HRESULT hr;

	this->closeMenu();

	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	//if (true)
	{
		this->CreateDeviceIndependentResources();

		this->CreateDeviceResources();
	}


	return E_NOTIMPL;
}

HRESULT D2D::CreateDeviceIndependentResources()
{
	// Will load a default font if the font is not installed on the PC
	static const WCHAR msc_fontName[] = L"Verdana"; // Verdana, Rockwell, Agency FB
	static const FLOAT msc_fontSize = 20;
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->m_pDirect2dFactory);

	//Setup text
	if (SUCCEEDED(hr))
	{

		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(this->m_pDirectWriteFactory),
			reinterpret_cast<IUnknown **>(&this->m_pDirectWriteFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = this->m_pDirectWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&this->m_pTextFormat
		);

	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		this->m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		this->m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	if (SUCCEEDED(hr))
	{
		// Create the WICFactory for image proccesing.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&this->pIWICFactory
		);
	}

	return hr;
}

HRESULT D2D::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!this->m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(Locator::getD3D()->GEThwnd(), &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		// Create a Direct2D render target.
		hr = this->m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_IGNORE)),
			D2D1::HwndRenderTargetProperties(Locator::getD3D()->GEThwnd(), size),
			&this->m_pRenderTarget
		);

		//Create the colorBrush for the grid in the background
		this->m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->pGridColor);
	}

	return hr;
}

void D2D::saveScreenshot()
{
	this->closeMenu();

	RECT rc;
	GetClientRect(Locator::getD3D()->GEThwnd(), &rc);

	HDC hdcScreen;
	HDC hdcWindow;
	HDC hdcMemDC = NULL;
	HBITMAP hbmScreen = NULL;
	BITMAP bmpScreen;

	// Retrieve the handle to a display device context for the client 
	// area of the window. 
	hdcScreen = GetDC(NULL);
	hdcWindow = GetDC(Locator::getD3D()->GEThwnd());

	// Create a compatible DC which is used in a BitBlt from the window DC
	hdcMemDC = CreateCompatibleDC(hdcWindow);

	//This is the best stretch mode
	SetStretchBltMode(hdcWindow, HALFTONE);

	// Create a compatible bitmap from the Window DC
	hbmScreen = CreateCompatibleBitmap(hdcWindow, rc.right - rc.left, rc.bottom - rc.top);

	// Select the compatible bitmap into the compatible memory DC.
	SelectObject(hdcMemDC, hbmScreen);

	// Bit block transfer into our compatible memory DC.
	BitBlt(hdcMemDC,
		0, 0,
		rc.right - rc.left, rc.bottom - rc.top,
		hdcWindow,
		0, 0,
		SRCCOPY);

	// Get the BITMAP from the HBITMAP
	GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char *lpbitmap = (char *)GlobalLock(hDIB);

	// Gets the "bits" from the bitmap and copies them into a buffer 
	// which is pointed to by lpbitmap.
	GetDIBits(hdcWindow, hbmScreen, 0,
		(UINT)bmpScreen.bmHeight,
		lpbitmap,
		(BITMAPINFO *)&bi, DIB_RGB_COLORS);

	// A file is created, this is where we will save the screen capture.
	HANDLE hFile = CreateFile("include/screenSaved.bmp",
		GENERIC_ALL,
		FILE_SHARE_DELETE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size
	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	//Size of the file
	bmfHeader.bfSize = dwSizeofDIB;

	//bfType must always be BM for Bitmaps
	bmfHeader.bfType = 0x4D42; //BM   

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	//Unlock and Free the DIB from the heap
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	//Close the handle for the file that was created
	CloseHandle(hFile);
}

void D2D::loadBitmap()
{
	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(Locator::getD3D()->GEThwnd(), &rc);

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top
	);

	//Create a texture
	IWICBitmapDecoder *pDecoder = nullptr;
	IWICBitmapFrameDecode *pSource = nullptr;
	IWICStream *pStream = nullptr;
	IWICFormatConverter *pConverter = nullptr;
	IWICBitmapScaler *pScaler = nullptr;

	this->m_pRenderTarget->CreateBitmap(
		size,
		D2D1::BitmapProperties(
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_IGNORE),
			size.width,
			size.height),
		&this->pBitmap
	);

	//this->uri = L"include/screenSaved.bmp";
	hr = this->pIWICFactory->CreateDecoderFromFilename(
		L"include/screenSaved.bmp",
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);

	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	if (SUCCEEDED(hr))
	{

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = this->m_pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			&this->pBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);
}

void D2D::DiscardDeviceResources()
{
	SafeRelease(&this->m_pRenderTarget);;
	SafeRelease(&this->m_pTextFormat);
	SafeRelease(&this->pGridColor);
}

HRESULT D2D::OnRender(std::vector<MenuObject*> objects)
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();
	
	if (SUCCEEDED(hr))
	{
		this->m_pRenderTarget->BeginDraw();

		this->m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		this->m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkRed));
		
		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

		FLOAT width = static_cast<FLOAT>(rtSize.width);
		FLOAT height = static_cast<FLOAT>(rtSize.height);

		//Background picture
		if (this->pBitmap)
		{
			this->m_pRenderTarget->DrawBitmap(this->pBitmap,
				D2D1::RectF(
					0,
					0,
					width,
					height
				)
			);
		}

		// Draw a grid background.

			for (int x = 0; x < width; x += 5)
			{
				m_pRenderTarget->DrawLine(
					D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
					D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
					this->pGridColor,
					2.5f
				);
			}

			for (int y = 0; y < height; y += 5)
			{
				m_pRenderTarget->DrawLine(
					D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
					D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
					this->pGridColor,
					2.5f
				);
			}

		for (auto &i : objects)
		{
			i->render();
		}

		hr = m_pRenderTarget->EndDraw();
	}

	// If something went wrong in EndDraw() it will discard it and redraw
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
	return hr;
}

void D2D::closeMenu()
{
		//SafeRelease(&this->pIWICFactory);
		SafeRelease(&this->pBitmap);
	
		//Removes the screenshot from the directory
		DeleteFile("include/screenSaved.bmp");
}

void D2D::cleanUp()
{
	// D2D device
	SafeRelease(&this->m_pDirect2dFactory);
	// Render target, dose all calls to render
	SafeRelease(&this->m_pRenderTarget);
	// D2D device for text
	SafeRelease(&this->m_pDirectWriteFactory);
	// Holds formating for text, ea Font
	SafeRelease(&this->m_pTextFormat);
	//Background
	SafeRelease(&this->pGridColor);
	// Image factory
	SafeRelease(&this->pIWICFactory);
	// Background-screenshot
	this->closeMenu();
}
