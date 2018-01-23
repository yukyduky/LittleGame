#include "D3D.h"
LRESULT CALLBACK wndProc(HWND hwnd, size_t msg, WPARAM wParam, LPARAM lParam);

IDXGISwapChain* D3D::gSwapChain = nullptr;
ID3D11Device* D3D::gDevice = nullptr;
ID3D11DeviceContext* D3D::gDevCon = nullptr;
ID3D11RenderTargetView* D3D::gRTV = nullptr;
ID3D11DepthStencilView* D3D::gDSV = nullptr;
ID3D11Texture2D* D3D::gDSB = nullptr;

HWND D3D::hwnd = nullptr;
int D3D::wWidth = 800;
int D3D::wHeight = 600;

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

void D3D::createBackBufferRTV(ID3D11RenderTargetView** gRTV)
{
	HRESULT hr;

	// Describe the Buffer
	DXGI_MODE_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = wWidth;
	bufferDesc.Height = wHeight;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Create the BackBuffer
	ID3D11Texture2D* BackBuffer;
	hr = gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	if (FAILED(hr)) {
		MessageBox(0, "Swapchain backbuffer - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Create the Render Target
	hr = gDevice->CreateRenderTargetView(BackBuffer, nullptr, gRTV);
	if (FAILED(hr)) {
		MessageBox(0, "Create Render Target View - Failed", "Error", MB_OK);
		_exit(0);
	}
	BackBuffer->Release();
}


void D3D::compileShaders(LPCSTR entryPoint, LPCSTR target, const wchar_t * fileName, ID3DBlob** gBlob)
{
	HRESULT hr;

	hr = D3DCompileFromFile(
		fileName,			// filename
		nullptr,			// optional macros
		nullptr,			// optional include files
		entryPoint,			// entry point
		target,				// shader model (target)
		0,					// shader compile options			// here DEBUGGING OPTIONS
		0,					// effect compile options
		gBlob,				// double pointer to ID3DBlob		
		nullptr				// pointer for Error Blob messages.
							// how to use the Error blob, see here
							// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);
	if (FAILED(hr)) {
		MessageBox(0, "Compile Shader - Failed", "Error", MB_OK);
		_exit(0);
	}


}

void D3D::createInputLayout(ID3DBlob* gBlob, ID3D11InputLayout** gInputLayout, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize)
{
	HRESULT hr;

	hr = gDevice->CreateInputLayout(inputDesc, inputDescSize, gBlob->GetBufferPointer(), gBlob->GetBufferSize(), gInputLayout);
	if (FAILED(hr)) {
		MessageBox(0, "Input Layout - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createVertexShader(ID3DBlob* gBlob, ID3D11VertexShader** gVertexShader)
{
	HRESULT hr;

	hr = gDevice->CreateVertexShader(gBlob->GetBufferPointer(), gBlob->GetBufferSize(), nullptr, gVertexShader);
	if (FAILED(hr)) {
		MessageBox(0, "Vertex Shader - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createPixelShader(ID3DBlob* gBlob, ID3D11PixelShader** gPixelShader)
{
	HRESULT hr;

	hr = gDevice->CreatePixelShader(gBlob->GetBufferPointer(), gBlob->GetBufferSize(), nullptr, gPixelShader);
	if (FAILED(hr)) {
		MessageBox(0, "Pixel Shader - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createGeometryShader(ID3DBlob* gBlob, ID3D11GeometryShader** gGeometryShader)
{
	HRESULT hr;

	hr = gDevice->CreateGeometryShader(gBlob->GetBufferPointer(), gBlob->GetBufferSize(), nullptr, gGeometryShader);
	if (FAILED(hr)) {
		MessageBox(0, "Geometry Shader - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createHullShader(ID3DBlob* gBlob, ID3D11HullShader** gHullShader)
{
	HRESULT hr;

	hr = gDevice->CreateHullShader(gBlob->GetBufferPointer(), gBlob->GetBufferSize(), nullptr, gHullShader);
	if (FAILED(hr)) {
		MessageBox(0, "Hull Shader - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createDomainShader(ID3DBlob* gBlob, ID3D11DomainShader** gDomainShader)
{
	HRESULT hr;

	hr = gDevice->CreateDomainShader(gBlob->GetBufferPointer(), gBlob->GetBufferSize(), nullptr, gDomainShader);
	if (FAILED(hr)) {
		MessageBox(0, "Domain Shader - Failed", "Error", MB_OK);
		_exit(0);
	}
}


void D3D::initializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
{
	wWidth = width;
	wHeight = height;

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

	hwnd = CreateWindowEx(
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
	if (!hwnd) {
		MessageBox(nullptr, "Error creating window", "Error", MB_OK | MB_ICONERROR);
		_exit(0);
	}

	// Display and update the window
	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);
}

void D3D::initializeDirectX()
{
	createSwapChain();
	createBackBufferRTV(&gRTV);
	createDepthStencilView(wWidth, wHeight, &gDSV, &gDSB);
}

D3D11_VIEWPORT D3D::createViewPort(int width, int height)
{
	D3D11_VIEWPORT viewport;
	memset(&viewport, 0, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	return viewport;
}

void D3D::setViewPort(D3D11_VIEWPORT* vp)
{
	gDevCon->RSSetViewports(1, vp);
}

void D3D::createDepthStencilView(int width, int height, ID3D11DepthStencilView** gDSV, ID3D11Texture2D** gDSB)
{
	HRESULT hr;

	// Describe the Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	memset(&depthStencilDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));

	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	// Creates the Depth/Stencil View
	hr = gDevice->CreateTexture2D(&depthStencilDesc, nullptr, gDSB);
	if (FAILED(hr)) {
		MessageBox(0, "Create Depth Texture - Failed", "Error", MB_OK);
		_exit(0);
	}

	hr = gDevice->CreateDepthStencilView(*gDSB, nullptr, gDSV);
	if (FAILED(hr)) {
		MessageBox(0, "Create Depth Stencil - Failed", "Error", MB_OK);
		_exit(0);
	}
}


void D3D::createFixedShaders(ID3D11InputLayout** gInputLayout, ID3D11VertexShader** gVertexShader, ID3D11PixelShader** gPixelShader, const wchar_t* fileNameVertex, const wchar_t* fileNamePixel, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize)
{
	ID3DBlob* gBlob = nullptr;

	// Compile Vertex shader
	compileShaders(LPCSTR("VS"), LPCSTR("vs_5_0"), fileNameVertex, &gBlob);

	// Create Vertex shader
	createVertexShader(gBlob, gVertexShader);

	// Create Input layout
	createInputLayout(gBlob, gInputLayout, inputDesc, inputDescSize);

	gBlob->Release();

	// Compile Pixel shader
	compileShaders(LPCSTR("PS"), LPCSTR("ps_5_0"), fileNamePixel, &gBlob);

	// Create Pixel shader
	createPixelShader(gBlob, gPixelShader);

	gBlob->Release();
}

void D3D::createGeoShaders(ID3D11GeometryShader** gGeometryShader, const wchar_t* fileNameGeometry)
{
	ID3DBlob* gBlob = nullptr;

	// Compile Geometry shader
	compileShaders(LPCSTR("GS"), LPCSTR("gs_5_0"), fileNameGeometry, &gBlob);

	// Create Geometry shader
	createGeometryShader(gBlob, gGeometryShader);

	gBlob->Release();
}

void D3D::createTesselationShaders(ID3D11HullShader** gHullShader, ID3D11DomainShader** gDomainShader, const wchar_t* fileNameHull, const wchar_t* fileNameDomain)
{
	ID3DBlob* gBlob = nullptr;

	// Compile Geometry shader
	compileShaders(LPCSTR("HS"), LPCSTR("hs_5_0"), fileNameHull, &gBlob);

	// Create Geometry shader
	createHullShader(gBlob, gHullShader);

	gBlob->Release();

	// Compile Geometry shader
	compileShaders(LPCSTR("DS"), LPCSTR("ds_5_0"), fileNameDomain, &gBlob);

	// Create Geometry shader
	createDomainShader(gBlob, gDomainShader);

	gBlob->Release();
}

void D3D::setFixedShaders(ID3D11VertexShader* gVertexShader, ID3D11PixelShader* gPixelShader)
{
	gDevCon->VSSetShader(gVertexShader, nullptr, 0);
	gDevCon->PSSetShader(gPixelShader, nullptr, 0);
}

void D3D::setGeoShaders(ID3D11GeometryShader* gGeometryShader)
{
	gDevCon->GSSetShader(gGeometryShader, nullptr, 0);
}

void D3D::setTesselationShaders(ID3D11HullShader* gHullShader, ID3D11DomainShader* gDomainShader)
{
	gDevCon->HSSetShader(gHullShader, nullptr, 0);
	gDevCon->DSSetShader(gDomainShader, nullptr, 0);
}

void D3D::setInputLayout(ID3D11InputLayout* gInputLayout)
{
	gDevCon->IASetInputLayout(gInputLayout);
}


void D3D::createRasterizerState(ID3D11RasterizerState** gRastState, D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, int depthBias, float depthBiasClamp, float slopedDepthBias)
{
	HRESULT hr;

	D3D11_RASTERIZER_DESC rastDesc;
	memset(&rastDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
	rastDesc.CullMode = cullMode;
	rastDesc.FillMode = fillMode;
	rastDesc.FrontCounterClockwise = false;
	rastDesc.DepthBias = depthBias;
	rastDesc.DepthBiasClamp = depthBiasClamp;
	rastDesc.SlopeScaledDepthBias = slopedDepthBias;

	hr = gDevice->CreateRasterizerState(&rastDesc, gRastState);
	if (FAILED(hr)) {
		MessageBox(0, "Create Default Rasterizer - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createSampler(ID3D11SamplerState** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc)
{
	HRESULT hr;

	D3D11_SAMPLER_DESC sampDesc;
	memset(&sampDesc, 0, sizeof(D3D11_SAMPLER_DESC));
	sampDesc.Filter = filter;
	sampDesc.AddressU = texAdressModeU;
	sampDesc.AddressV = texAdressModeV;
	sampDesc.AddressW = texAdressModeW;
	sampDesc.ComparisonFunc = compFunc;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = gDevice->CreateSamplerState(&sampDesc, gSampler);
	if (FAILED(hr)) {
		MessageBox(0, "Create Samplerstate - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::setRasterizerState(ID3D11RasterizerState* gRastState)
{
	gDevCon->RSSetState(gRastState);
}


void D3D::clearRendertarget(ID3D11RenderTargetView* gRTV)
{
	gDevCon->ClearRenderTargetView(gRTV, DirectX::SimpleMath::Color(255.0f, 0.0f, 255.0f, 1.0f));
}

void D3D::clearDepthStencilView(ID3D11DepthStencilView* gDSV, size_t clearFlags)
{
	gDevCon->ClearDepthStencilView(gDSV, clearFlags, 1.0f, 0);
}

void D3D::setRenderTargets(size_t numViews, ID3D11RenderTargetView** gRTV, ID3D11DepthStencilView* gDSV)
{
	gDevCon->OMSetRenderTargets(numViews, gRTV, gDSV);
}

void D3D::createTextureFromFile(ID3D11ShaderResourceView** gSRV, const wchar_t* fileName)
{
	HRESULT hr;

	hr = DirectX::CreateWICTextureFromFile(gDevice, fileName, nullptr, gSRV, NULL);
	if (FAILED(hr)) {
		MessageBox(0, "Create WIC texture from file - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::bindTextureToRTVAndSRV(ID3D11Texture2D** gTexure, ID3D11RenderTargetView** gRTV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT texFormat, DXGI_FORMAT rtvFormat, DXGI_FORMAT srvFormat)
{
	HRESULT hr;

	// Describe the texture
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.Format = texFormat;
	texDesc.CPUAccessFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	// Create one texture per rendertarget
	hr = gDevice->CreateTexture2D(&texDesc, nullptr, gTexure);
	if (FAILED(hr)) {
		MessageBox(0, "Create texture (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Rendertargetview
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	rtvDesc.Format = rtvFormat;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	// Create one rtv per output from the pixel shader
	hr = gDevice->CreateRenderTargetView(*gTexure, &rtvDesc, gRTV);
	if (FAILED(hr)) {
		MessageBox(0, "Create RTV (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Shaderresourceview
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = srvFormat;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// Create one srv per texture to be loaded into the next pixel shader
	hr = gDevice->CreateShaderResourceView(*gTexure, &srvDesc, gSRV);
	if (FAILED(hr)) {
		MessageBox(0, "Create SRV (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::bindTextureToDSVAndSRV(ID3D11Texture2D** gTexure, ID3D11DepthStencilView** gDSV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT texFormat, DXGI_FORMAT dsvFormat, DXGI_FORMAT srvFormat)
{
	HRESULT hr;

	// Describe the texture
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.Format = texFormat;
	texDesc.CPUAccessFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	// Create the texture to draw the shadowmap on
	hr = gDevice->CreateTexture2D(&texDesc, nullptr, gTexure);
	if (FAILED(hr)) {
		MessageBox(0, "Create texture (DSV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the depthstencilview
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	memset(&dsvDesc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvDesc.Flags = 0;
	dsvDesc.Format = dsvFormat;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = gDevice->CreateDepthStencilView(*gTexure, &dsvDesc, gDSV);
	if (FAILED(hr)) {
		MessageBox(0, "Create DSV (DSV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Shaderresourceview
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = srvFormat;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// Create the SRV for the shadowmap
	hr = gDevice->CreateShaderResourceView(*gTexure, &srvDesc, gSRV);
	if (FAILED(hr)) {
		MessageBox(0, "Create SRV (DSV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::vsSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV)
{
	gDevCon->VSSetShaderResources(start, numViews, &gSRV);
}

void D3D::psSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV)
{
	gDevCon->PSSetShaderResources(start, numViews, &gSRV);
}

void D3D::gsSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV)
{
	gDevCon->GSSetShaderResources(start, numViews, &gSRV);
}

void D3D::hsSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV)
{
	gDevCon->HSSetShaderResources(start, numViews, &gSRV);
}

void D3D::dsSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV)
{
	gDevCon->DSSetShaderResources(start, numViews, &gSRV);
}

void D3D::vsSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler)
{
	gDevCon->VSSetSamplers(start, numSamplers, &gSampler);
}

void D3D::psSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler)
{
	gDevCon->PSSetSamplers(start, numSamplers, &gSampler);
}

void D3D::gsSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler)
{
	gDevCon->GSSetSamplers(start, numSamplers, &gSampler);
}

void D3D::hsSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler)
{
	gDevCon->HSSetSamplers(start, numSamplers, &gSampler);
}

void D3D::dsSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler)
{
	gDevCon->DSSetSamplers(start, numSamplers, &gSampler);
}

void D3D::createIndexBuffer(DWORD* indices, ID3D11Buffer** gIndexBuffer, int bufferSize)
{
	HRESULT hr;

	// Describe the index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	memset(&indexBufferDesc, 0, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = bufferSize;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Set the index buffer data
	D3D11_SUBRESOURCE_DATA indexData;

	indexData.pSysMem = indices;
	hr = gDevice->CreateBuffer(&indexBufferDesc, &indexData, gIndexBuffer);
	if (FAILED(hr)) {
		MessageBox(0, "Box Index Buffer - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void D3D::createVertexBuffer(Vertex* v, ID3D11Buffer** gVertexBuffer, int bufferSize)
{
	HRESULT hr;

	//Create Buffer description for vertex buffer.
	D3D11_BUFFER_DESC vBuffDesc;
	ZeroMemory(&vBuffDesc, sizeof(vBuffDesc));
	vBuffDesc.Usage = D3D11_USAGE_DEFAULT;
	vBuffDesc.ByteWidth = bufferSize;
	vBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBuffDesc.CPUAccessFlags = 0;
	vBuffDesc.MiscFlags = 0;

	//Create vertex subresource data.
	D3D11_SUBRESOURCE_DATA vBuffData;
	ZeroMemory(&vBuffData, sizeof(vBuffData));
	vBuffData.pSysMem = v;

	hr = gDevice->CreateBuffer(&vBuffDesc, &vBuffData, gVertexBuffer);
	if (FAILED(hr)) {
		MessageBox(0, "createVertexBuffer - Failed", "Error", MB_OK);
		_exit(0);
	}
}

ID3D11RenderTargetView& D3D::getgRTV()
{
	return *gRTV;
}

void D3D::mapBuffer(ID3D11DeviceContext* gDevCon, ID3D11Buffer** gBuffer, void* cbPtr, int structSize)
{
	HRESULT hr;

	// Map constant buffer so that we can write to it.
	D3D11_MAPPED_SUBRESOURCE dataPtr;
	hr = gDevCon->Map(*gBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &dataPtr);
	if (FAILED(hr)) {
		MessageBox(0, "Buffer mapping - Failed", "Error", MB_OK);
		_exit(0);
	}
	// copy memory from CPU to GPU the entire struct
	memcpy(dataPtr.pData, cbPtr, structSize);
	// UnMap constant buffer so that we can use it again in the GPU
	gDevCon->Unmap(*gBuffer, 0);
}

void D3D::createConstantBuffer(ID3D11Device* gDevice, ID3D11Buffer** gBuffer, int bufferSize)
{
	HRESULT hr;

	// Describes the constant buffer
	D3D11_BUFFER_DESC cbBufferDesc;
	memset(&cbBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	cbBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbBufferDesc.ByteWidth = bufferSize;
	cbBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbBufferDesc.MiscFlags = 0;

	hr = gDevice->CreateBuffer(&cbBufferDesc, nullptr, gBuffer);
	if (FAILED(hr)) {
		MessageBox(0, "Create Constant Buffer - Failed", "Error", MB_OK);
		_exit(0);
	}
}


void D3D::setIndexBuffer(ID3D11Buffer * gIndexBuffer, DXGI_FORMAT format, size_t offset)
{
	gDevCon->IASetIndexBuffer(gIndexBuffer, format, offset);
}

void D3D::setVertexBuffer(size_t start, size_t numBuffers, ID3D11Buffer** gVertexBuffer, size_t* stride, size_t* offset)
{
	gDevCon->IASetVertexBuffers(start, numBuffers, gVertexBuffer, stride, offset);
}

void D3D::setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	gDevCon->IASetPrimitiveTopology(topology);
}

void D3D::draw(size_t numVertices, size_t start)
{
	gDevCon->Draw(numVertices, start);
}

void D3D::drawIndexed(size_t numIndex, size_t start, int baseVertexLoc)
{
	gDevCon->DrawIndexed(numIndex, start, baseVertexLoc);
}

void D3D::swapBackBuffer()
{
	gSwapChain->Present(0, 0);
}


int D3D::getWidth()
{
	return wWidth;
}

int D3D::getHeight()
{
	return wHeight;
}


void D3D::Release()
{
	gSwapChain->Release();
	gDevice->Release();
	gDevCon->Release();
	gRTV->Release();
	gDSV->Release();
	gDSB->Release();
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