#include "DeferredRendering.h"
#include "D3D.h"


void DeferredRendering::initShaders()
{
	D3D::createFixedShaders(&gGeoInputLayout, &this->gGeoVertex, &this->gGeoPixel, this->fileNameGeoVertex, this->fileNameGeoPixel, this->geoInputDesc, GEO_INPUT_DESC_SIZE);
	D3D::createFixedShaders(&gLightInputLayout, &this->gLightVertex, &this->gLightPixel, this->fileNameLightVertex, this->fileNameLightPixel, this->lightInputDesc, LIGHT_INPUT_DESC_SIZE);
}

void DeferredRendering::bindTextureToRTVAndSRV()
{
	DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	for (int i = 0; i < NUM_DEFERRED_OUTPUTS; i++) {
		D3D::bindTextureToRTVAndSRV(&this->gDeferredTexs[i], &this->gRTVs[i], &this->gSRVs[i], D3D::getWidth(), D3D::getHeight(), format, format, format);
	}
}

void DeferredRendering::initSampler()
{
	D3D::createSampler(&this->gSampler, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_COMPARISON_ALWAYS);
}

void DeferredRendering::createQuad()
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

	HRESULT hr = D3D::GETgDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &this->gQuadVertexBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, "Create Vertex buffer - Failed", "Error", MB_OK);
		_exit(0);
	}

	this->vertBufferStride = sizeof(Vertex);
	this->vertBufferOffset = 0;
}

void DeferredRendering::createViewport()
{
	this->viewport = D3D::createViewPort(D3D::getWidth(), D3D::getHeight());
}

DeferredRendering::DeferredRendering()
{
}

void DeferredRendering::init()
{
	this->initShaders();
	this->bindTextureToRTVAndSRV();
	this->createQuad();
	this->initSampler();
}

void DeferredRendering::firstPass()
{
	D3D::clearRendertarget(D3D::GETgRTV());
	for (auto &i : this->gRTVs) {
		D3D::clearRendertarget(i);
	}
	D3D::clearDepthStencilView(D3D::GETgDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL);

	D3D::setFixedShaders(this->gGeoVertex, this->gGeoPixel);
	D3D::setInputLayout(gGeoInputLayout);

	D3D::setViewPort(&this->viewport);

	D3D::setRenderTargets(NUM_DEFERRED_OUTPUTS, this->gRTVs.data(), D3D::GETgDSV());
}

void DeferredRendering::secondPass()
{
	D3D::setFixedShaders(this->gLightVertex, this->gLightPixel);
	D3D::setInputLayout(gLightInputLayout);

	D3D::setVertexBuffer(0, 1, &this->gQuadVertexBuffer, &this->vertBufferStride, &this->vertBufferOffset);

	D3D::setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D::setRenderTargetToFinalRTV();

	D3D::psSetShaderResource(0, NUM_DEFERRED_OUTPUTS, this->gSRVs.data());
	D3D::psSetSampler(0, 1, &this->gSampler);

	D3D::draw(4, 0);

	D3D::swapBackBuffer();
}
