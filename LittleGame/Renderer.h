#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <d3d11.h>
#include <array>
#include "Shader.h"

const int NUM_BACKGROUND_IMAGES = 39;
const int NUM_DEFERRED_OUTPUTS = 3;
const int GEOCOLOR_INPUT_DESC_SIZE = 3;
const int GEOTEX_INPUT_DESC_SIZE = 3;
const int LIGHT_INPUT_DESC_SIZE = 1;

enum class SHADERTYPE { COLOR, TEXTURE };

class Renderer
{
private:
	std::array<ID3D11RenderTargetView*, NUM_DEFERRED_OUTPUTS> gRTVs;
	std::array<ID3D11ShaderResourceView*, NUM_DEFERRED_OUTPUTS> gSRVs;
	std::array<ID3D11Texture2D*, NUM_DEFERRED_OUTPUTS> gDeferredTexs;
	ID3D11RenderTargetView* gFinalRTV = nullptr;
	ID3D11DepthStencilView* gDSV = nullptr;
	ID3D11Texture2D* gDSB = nullptr;
	ID3D11SamplerState* gSampler = nullptr;
	ID3D11Buffer* gQuadVertexBuffer = nullptr;
	D3D11_VIEWPORT viewport;
	std::array<ID3D11ShaderResourceView*, NUM_BACKGROUND_IMAGES> gBackgroundSRVs;

	size_t currBackgroundFrame = 0;
	float currBackgroundFrameTime = 0.0f;
	size_t vertBufferStride = 0;
	size_t vertBufferOffset = 0;
	Shader geoColorShaders;
	Shader geoTexShaders;
	Shader lightShaders;
	Shader* currentGeoShaders = nullptr;
	Shader* currentLightShaders = nullptr;

	std::array<float, 4> clearColor;

	void initShaders();
	void loadBackgroundTexture();
	void updateBackgroundFrame();
	void bindTextureToRTVAndSRV(ID3D11Texture2D** gTexure, ID3D11RenderTargetView** gRTV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT format);
	void initSampler(ID3D11SamplerState** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc);
	void createQuad();
	void createViewport();
	void createBackBufferRTV();
	void createDepthStencilView(size_t width, size_t height, ID3D11DepthStencilView** gDSV, ID3D11Texture2D** gDSB);
public:
	Renderer() : gRTVs(), gSRVs(), gDeferredTexs() {}
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Intializes the clear color
	2. Sets the current shadertype
	3. Creates the backbuffer rendertargetview aka the final rendertargetview
	4. Intializes the shaders
	5. Binds the deferred rendertargetviews with the deferred shaderresourceviews
	6. Creates the Quad data
	7. Initializes the sampler
	8. Creates the viewport
	*/
	void init();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Clears the final and the deferred rendertargetviews
	2. Clears the depthstencilview
	3. Sets current shaders to geo shaders
	4. Sets the viewport to the default one
	5. Sets the rendertarget to the deferred rendertargetview
	*/
	void firstPass();
	void secondPassSetup();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Sets current shaders to light shaders
	2. Sets the vertex buffer for the Quad
	3. Switches to trianglestrip topology
	4. Unbinds the deferred rendertargetviews
	5. Binds the deferred shaderresourceviews to the pixel shader
	6. Sets the rendertarget to the final rendertargetview
	7. Draws the Quad
	8. Presents the backbuffer
	9. Unbinds the deferred shaderresourceviews
	*/
	void secondPass();
	void setShaderType(SHADERTYPE type);
	void cleanUp();
private:
	const D3D11_INPUT_ELEMENT_DESC geoTexInputDesc[GEOTEX_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORDS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const D3D11_INPUT_ELEMENT_DESC geoColorInputDesc[GEOCOLOR_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const D3D11_INPUT_ELEMENT_DESC lightInputDesc[LIGHT_INPUT_DESC_SIZE] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	const wchar_t* fileNameLightVertex = L"lightPassVert.hlsl";
	const wchar_t* fileNameLightPixel = L"lightPassPixel.hlsl";

	const wchar_t* fileNameGeoColorVertex = L"geoPassVertColor.hlsl";
	const wchar_t* fileNameGeoColorPixel = L"geoPassPixelColor.hlsl";

	const wchar_t* fileNameGeoTexVertex = L"geoPassVertTex.hlsl";
	const wchar_t* fileNameGeoTexPixel = L"geoPassPixelTex.hlsl";
};

#endif // !RENDERER_H
