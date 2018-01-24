#pragma once
#ifndef DEFERREDRENDERING_H
#define DEFERREDRENDERING_H

#include <d3d11.h>
#include <array>

const int NUM_DEFERRED_OUTPUTS = 1;
const int GEO_INPUT_DESC_SIZE = 3;
const int LIGHT_INPUT_DESC_SIZE = 1;

class DeferredRendering
{
private:
	std::array<ID3D11RenderTargetView*, NUM_DEFERRED_OUTPUTS> gRTVs;
	std::array<ID3D11ShaderResourceView*, NUM_DEFERRED_OUTPUTS> gSRVs;
	std::array<ID3D11Texture2D*, NUM_DEFERRED_OUTPUTS> gDeferredTexs;
	ID3D11SamplerState* gSampler;
	ID3D11VertexShader* gGeoVertex;
	ID3D11PixelShader* gGeoPixel;
	ID3D11VertexShader* gLightVertex;
	ID3D11PixelShader* gLightPixel;
	ID3D11InputLayout* gGeoInputLayout;
	ID3D11InputLayout* gLightInputLayout;
	ID3D11Buffer* gQuadVertexBuffer;
	D3D11_VIEWPORT viewport;

	size_t vertBufferStride;
	size_t vertBufferOffset;

	void initShaders();
	void bindTextureToRTVAndSRV();
	void initSampler();
	void createQuad();
	void createViewport();
public:
	DeferredRendering();
	void init();
	void firstPass();
	void secondPass();
private:
	const D3D11_INPUT_ELEMENT_DESC geoInputDesc[GEO_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const D3D11_INPUT_ELEMENT_DESC lightInputDesc[LIGHT_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const wchar_t* fileNameGeoVertex = L"geoPassVert.hlsl";
	const wchar_t* fileNameGeoPixel = L"geoPassPixel.hlsl";
	const wchar_t* fileNameLightVertex = L"lightPassVert.hlsl";
	const wchar_t* fileNameLightPixel = L"lightPassPixel.hlsl";
};

#endif // !DEFERREDRENDERING_H
