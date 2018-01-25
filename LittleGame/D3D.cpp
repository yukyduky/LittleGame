#include "D3D.h"
LRESULT CALLBACK wndProc(HWND hwnd, size_t msg, WPARAM wParam, LPARAM lParam);

void D3D::initializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
{
	this->wWidth = width;
	this->wHeight = height;

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);					// Size of the windows class
	wc.style = CS_HREDRAW | CS_VREDRAW;				// Class styles
	wc.lpfnWndProc = wndProc;						// Name of the function that we chose to process messages
	wc.cbClsExtra = NULL;							// Extra bytes after the wc structure
	wc.cbWndExtra = NULL;							// Extra bytes after the windows instance
	wc.hInstance = hInstance;						// Instance of the current program
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);		// Titlebar icon
	wc.hCursor = LoadCursor(nullptr, nullptr);	// Default mouse icon
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 4);	// Window background color
	wc.lpszMenuName = nullptr;						// Name of the menu attached to the window if we had one
	wc.lpszClassName = LPCTSTR("Project");			// Name of the windows class
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);	// Taskbar icon
													// Error checking
	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, "Error registering class", "Error", MB_OK | MB_ICONERROR);
		_exit(0);
	}

	this->hwnd = CreateWindowEx(
		NULL,							// Extended style
		wc.lpszClassName,					// Name of windows class
		"Technique Project",				// Titlebar text
		WS_OVERLAPPEDWINDOW,			// Window style
		CW_USEDEFAULT, CW_USEDEFAULT,	// Starting positions of window
		width,							// Window width
		height,							// Window height
		nullptr,						// In case of a parent window
		nullptr,						// In case of a menu for the window
		hInstance,						// Instance of the current program
		nullptr							// Used for an MDI client window
	);

	// Error checking
	if (!this->hwnd) {
		MessageBox(nullptr, "Error creating window", "Error", MB_OK | MB_ICONERROR);
		_exit(0);
	}

	// Display and update the window
	ShowWindow(this->hwnd, ShowWnd);
	UpdateWindow(this->hwnd);
}

void D3D::createSwapChain()
{
	HRESULT hr;

	// Describe the SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	memset(&swapChainDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;                                  // one back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // use 32-bit color
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // how swap chain is to be used
	swapChainDesc.OutputWindow = hwnd;								// the window to be used
	swapChainDesc.SampleDesc.Count = 1;                             // how many multisamples
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// Create the SwapChain
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, NULL, D3D11_SDK_VERSION, &swapChainDesc, &gSwapChain, &gDevice, nullptr, &gDevCon);
	if (FAILED(hr)) {
		MessageBox(0, "Create Swapchain - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createVertexBuffer(ID3D11Buffer ** gVertexBuffer, PrimitiveVertexData* vertexData, size_t * stride, size_t * offset)
{
}

void D3D::createIndexBuffer(ID3D11Buffer ** gIndexBuffer, DWORD* indexData)
{
}

void D3D::setVertexBuffer(ID3D11Buffer ** gVertexBuffer, size_t * stride, size_t * offset)
{
	this->gDevCon->IASetVertexBuffers(0, 1, gVertexBuffer, stride, offset);
}

void D3D::setIndexBuffer(ID3D11Buffer * gIndexBuffer, size_t offset)
{
	this->gDevCon->IASetIndexBuffer(gIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
}

size_t & D3D::GETwWidth()
{
	return this->wWidth;
}

size_t & D3D::GETwHeight()
{
	return this->wHeight;
}

HWND & D3D::GEThwnd()
{
	return this->hwnd;
}

ID3D11Device *& D3D::GETgDevice()
{
	return this->gDevice;
}

ID3D11DeviceContext *& D3D::GETgDevCon()
{
	return this->gDevCon;
}

IDXGISwapChain *& D3D::GETswapChain()
{
	return this->gSwapChain;
}

LRESULT CALLBACK wndProc(HWND hwnd, size_t msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
