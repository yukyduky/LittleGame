#include "D2D.h"


D2D::D2D() :
	m_pDirect2dFactory(nullptr),
	m_pRenderTarget(nullptr),
	m_pDirectWriteFactory(nullptr),
	m_pTextFormat(nullptr),
	pGridColor(nullptr)
{
}

D2D::~D2D()
{
	SafeRelease(&this->m_pDirect2dFactory);
	SafeRelease(&this->m_pDirectWriteFactory);
	SafeRelease(&this->m_pRenderTarget);
	SafeRelease(&this->m_pTextFormat);
	SafeRelease(&this->pGridColor);
}

HRESULT D2D::Initialize()
{
	HRESULT hr;

	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		this->CreateDeviceIndependentResources();

		this->CreateDeviceResources();
	}

	return E_NOTIMPL;
}

HRESULT D2D::CreateDeviceIndependentResources()
{
	static const WCHAR msc_fontName[] = L"Verdana";
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
		this->m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Cyan), &this->pGridColor);
	}


	return hr;
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

		this->m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

		// Draw a grid background.
			D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

			int width = static_cast<int>(rtSize.width);
			int height = static_cast<int>(rtSize.height);

			for (int x = 0; x < width; x += 10)
			{
				m_pRenderTarget->DrawLine(
					D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
					D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
					this->pGridColor,
					1.5f
				);
			}

			for (int y = 0; y < height; y += 10)
			{
				m_pRenderTarget->DrawLine(
					D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
					D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
					this->pGridColor,
					1.5f
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

void D2D::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}
