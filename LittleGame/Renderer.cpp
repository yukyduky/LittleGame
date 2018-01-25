#include "Renderer.h"
#include <Windows.h>
#include "Locator.h"


void Renderer::initShaders()
{
	this->geoShaders.CreateShaders(Locator::getD3D()->GETgDevice(), this->fileNameGeoVertex, this->fileNameGeoPixel, this->geoInputDesc, GEO_INPUT_DESC_SIZE);
	this->lightShaders.CreateShaders(Locator::getD3D()->GETgDevice(), this->fileNameLightVertex, this->fileNameLightPixel, this->lightInputDesc, LIGHT_INPUT_DESC_SIZE);
}

void Renderer::bindTextureToRTVAndSRV(ID3D11Texture2D** gTexure, ID3D11RenderTargetView** gRTV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT format)
{
	HRESULT hr;

	// Describe the texture
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.Format = format;
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
	hr = Locator::getD3D()->GETgDevice()->CreateTexture2D(&texDesc, nullptr, gTexure);
	if (FAILED(hr)) {
		MessageBox(0, "Create texture (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Rendertargetview
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	rtvDesc.Format = format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	// Create one rtv per output from the pixel shader
	hr = Locator::getD3D()->GETgDevice()->CreateRenderTargetView(*gTexure, &rtvDesc, gRTV);
	if (FAILED(hr)) {
		MessageBox(0, "Create RTV (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Shaderresourceview
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// Create one srv per texture to be loaded into the next pixel shader
	hr = Locator::getD3D()->GETgDevice()->CreateShaderResourceView(*gTexure, &srvDesc, gSRV);
	if (FAILED(hr)) {
		MessageBox(0, "Create SRV (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void Renderer::initSampler(ID3D11SamplerState** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc)
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

	hr = Locator::getD3D()->GETgDevice()->CreateSamplerState(&sampDesc, gSampler);
	if (FAILED(hr)) {
		MessageBox(0, "Create Samplerstate - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void Renderer::createQuad()
{
	struct Vertex
	{
		float x, y, z, w;
	};

	Vertex v[] =
	{
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
	};

	// Describe the vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	memset(&vertexBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(v);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	// Set the vertex buffer data
	D3D11_SUBRESOURCE_DATA vertexData;
	memset(&vertexData, 0, sizeof(vertexData));
	vertexData.pSysMem = &v;

	HRESULT hr = Locator::getD3D()->GETgDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &this->gQuadVertexBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Vertex buffer - Failed", "Error", MB_OK);
		_exit(0);
	}

	this->vertBufferStride = sizeof(Vertex);
	this->vertBufferOffset = 0;
}

void Renderer::createViewport()
{
	memset(&this->viewport, 0, sizeof(D3D11_VIEWPORT));

	this->viewport.TopLeftX = 0;
	this->viewport.TopLeftY = 0;
	this->viewport.Width = Locator::getD3D()->GETwWidth();
	this->viewport.Height = Locator::getD3D()->GETwHeight();
	this->viewport.MinDepth = 0.0f;
	this->viewport.MaxDepth = 1.0f;
}

void Renderer::createBackBufferRTV()
{
	HRESULT hr;

	// Describe the Buffer
	DXGI_MODE_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = Locator::getD3D()->GETwWidth();
	bufferDesc.Height = Locator::getD3D()->GETwHeight();
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Create the BackBuffer
	ID3D11Texture2D* BackBuffer;
	hr = Locator::getD3D()->GETswapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	if (FAILED(hr)) {
		MessageBox(0, "Swapchain backbuffer - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Create the Render Target
	hr = Locator::getD3D()->GETgDevice()->CreateRenderTargetView(BackBuffer, nullptr, &this->gFinalRTV);
	if (FAILED(hr)) {
		MessageBox(0, "Create Render Target View - Failed", "Error", MB_OK);
		_exit(0);
	}
	BackBuffer->Release();
}

void Renderer::createDepthStencilView(size_t width, size_t height, ID3D11DepthStencilView ** gDSV, ID3D11Texture2D ** gDSB)
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
	hr = Locator::getD3D()->GETgDevice()->CreateTexture2D(&depthStencilDesc, nullptr, gDSB);
	if (FAILED(hr)) {
		MessageBox(0, "Create Depth Texture - Failed", "Error", MB_OK);
		_exit(0);
	}

	hr = Locator::getD3D()->GETgDevice()->CreateDepthStencilView(*gDSB, nullptr, gDSV);
	if (FAILED(hr)) {
		MessageBox(0, "Create Depth Stencil - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void Renderer::init()
{
	this->clearColor[0] = 255.0f;
	this->clearColor[1] = 0.0f;
	this->clearColor[2] = 255.0f;
	this->clearColor[3] = 255.0f;

	this->createBackBufferRTV();
	this->createDepthStencilView(Locator::getD3D()->GETwWidth(), Locator::getD3D()->GETwHeight(), &this->gDSV, &this->gDSB);
	this->initShaders();
	for (int i = 0; i < NUM_DEFERRED_OUTPUTS; i++) {
		this->bindTextureToRTVAndSRV(&this->gDeferredTexs[i], &this->gRTVs[i], &this->gSRVs[i], Locator::getD3D()->GETwWidth(), Locator::getD3D()->GETwHeight(), DXGI_FORMAT_R32G32B32A32_FLOAT);
	}
	this->createQuad();
	this->initSampler(&this->gSampler, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_COMPARISON_ALWAYS);
}

void Renderer::firstPass()
{
	Locator::getD3D()->GETgDevCon()->ClearRenderTargetView(gFinalRTV, this->clearColor.data());
	for (auto &i : this->gRTVs) {
		Locator::getD3D()->GETgDevCon()->ClearRenderTargetView(i, this->clearColor.data());
	}
	Locator::getD3D()->GETgDevCon()->ClearDepthStencilView(this->gDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	this->geoShaders.SetShaders(Locator::getD3D()->GETgDevCon());
	Locator::getD3D()->GETgDevCon()->RSSetViewports(1, &this->viewport);

	Locator::getD3D()->GETgDevCon()->OMSetRenderTargets(NUM_DEFERRED_OUTPUTS, this->gRTVs.data(), this->gDSV);
}

void Renderer::secondPass()
{
	Locator::getD3D()->GETgDevCon()->ClearRenderTargetView(gFinalRTV, this->clearColor.data());
	Locator::getD3D()->GETgDevCon()->ClearDepthStencilView(this->gDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	this->lightShaders.SetShaders(Locator::getD3D()->GETgDevCon());

	Locator::getD3D()->GETgDevCon()->IASetVertexBuffers(0, 1, &this->gQuadVertexBuffer, &vertBufferStride, &vertBufferOffset);
	Locator::getD3D()->GETgDevCon()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Locator::getD3D()->GETgDevCon()->OMSetRenderTargets(1, &this->gFinalRTV, this->gDSV);

	//Locator::getD3D()->GETgDevCon()->PSSetShaderResources(0, NUM_DEFERRED_OUTPUTS, this->gSRVs.data());

	// Draw the final texture over the whole screen
	Locator::getD3D()->GETgDevCon()->Draw(4, 0);
	// Present the backbuffer to the screen
	Locator::getD3D()->GETswapChain()->Present(0, 0);
}
