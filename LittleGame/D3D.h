#pragma once
#ifndef D3D_H
#define D3D_H

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <WICTextureLoader.h>
#include "SimpleMath.h"

struct Vertex
{
	Vertex(float x, float y, float z, float r, float g, float b, float a)
		: pos(x, y, z), color(r, g, b, a) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

class D3D
{
private:
	// COMs
	static IDXGISwapChain* gSwapChain;
	static ID3D11Device* gDevice;
	static ID3D11DeviceContext* gDevCon;
	static ID3D11RenderTargetView* gRTV;
	static ID3D11DepthStencilView* gDSV;
	static ID3D11Texture2D* gDSB;

	// VARIABLES
	static HWND hwnd;
	static int wWidth;
	static int wHeight;

	/// FUNCTIONS
	// INITIALIZATION FUNCTIONS
	static void createSwapChain();
	static void createBackBufferRTV(ID3D11RenderTargetView** gRTV);

	// SHADER SETUP FUNCTIONS
	static void compileShaders(LPCSTR entryPoint, LPCSTR target, const wchar_t* fileName, ID3DBlob** gBlob);
	static void createInputLayout(ID3DBlob* gBlob, ID3D11InputLayout** gInputLayout, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize);
	static void createVertexShader(ID3DBlob* gBlob, ID3D11VertexShader** gVertexShader);
	static void createPixelShader(ID3DBlob* gBlob, ID3D11PixelShader** gPixelShader);
	static void createGeometryShader(ID3DBlob* gBlob, ID3D11GeometryShader** gGeometryShader);
	static void createHullShader(ID3DBlob* gBlob, ID3D11HullShader** gHullShader);
	static void createDomainShader(ID3DBlob* gBlob, ID3D11DomainShader** gDomainShader);

public:
	// INITIALIZATION FUNCTIONS
	static void initializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
	static void initializeDirectX();
	static D3D11_VIEWPORT createViewPort(int width, int height);
	static void setViewPort(D3D11_VIEWPORT* vp);
	static void createDepthStencilView(int width, int height, ID3D11DepthStencilView** gDSV, ID3D11Texture2D** gDSB);
	static void createVertexBuffer(PrimitiveVertexData * v, ID3D11Buffer ** gVertexBuffer, int bufferSize);

	// SHADER SETUP FUNCTIONS
	static void createFixedShaders(ID3D11InputLayout** gInputLayout, ID3D11VertexShader** gVertexShader, ID3D11PixelShader** gPixelShader, const wchar_t* fileNameVertex, const wchar_t* fileNamePixel, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize);
	static void createGeoShaders(ID3D11GeometryShader** gGeometryShader, const wchar_t* fileNameGeometry);
	static void createTesselationShaders(ID3D11HullShader** gHullShader, ID3D11DomainShader** gDomainShader, const wchar_t* fileNameHull, const wchar_t* fileNameDomain);
	static void setFixedShaders(ID3D11VertexShader* gVertexShader, ID3D11PixelShader* gPixelShader);
	static void setGeoShaders(ID3D11GeometryShader* gGeometryShader);
	static void setTesselationShaders(ID3D11HullShader* gHullShader, ID3D11DomainShader* gDomainShader);
	static void setInputLayout(ID3D11InputLayout* gInputLayout);

	// STATE CREATIONS
	static void createRasterizerState(ID3D11RasterizerState** gRastState, D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, int depthBias, float depthBiasClamp, float slopedDepthBias);
	static void createSampler(ID3D11SamplerState** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc);
	static void setRasterizerState(ID3D11RasterizerState* gRastState);

	// RENDERTARGET AND SHADER-RESOURCE FUNCTIONS
	static void clearRendertarget(ID3D11RenderTargetView* gRTV);
	static void clearDepthStencilView(ID3D11DepthStencilView* gDSV, size_t clearFlags);
	static void setRenderTargets(size_t numViews, ID3D11RenderTargetView** gRTV, ID3D11DepthStencilView* gDSV);
	static void createTextureFromFile(ID3D11ShaderResourceView** gSRV, const wchar_t* fileName);
	static void bindTextureToRTVAndSRV(ID3D11Texture2D** gTexure, ID3D11RenderTargetView** gRTV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT texFormat, DXGI_FORMAT rtvFormat, DXGI_FORMAT srvFormat);
	static void bindTextureToDSVAndSRV(ID3D11Texture2D** gTexure, ID3D11DepthStencilView** gDSV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT texFormat, DXGI_FORMAT dsvFormat, DXGI_FORMAT srvFormat);
	static void vsSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV);
	static void psSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV);
	static void gsSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV);
	static void hsSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV);
	static void dsSetShaderResource(size_t start, size_t numViews, ID3D11ShaderResourceView* gSRV);
	static void vsSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler);
	static void psSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler);
	static void gsSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler);
	static void hsSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler);
	static void dsSetSampler(size_t start, size_t numSamplers, ID3D11SamplerState* gSampler);
	static void createIndexBuffer(DWORD* indices, ID3D11Buffer** gIndexBuffer, int bufferSize);
	static void createVertexBuffer(Vertex* v, ID3D11Buffer** gVertexBuffer, int bufferSize);

	// CONSTANT BUFFERS
	static void mapBuffer(ID3D11DeviceContext* gDevCon, ID3D11Buffer** gBuffer, void * cbPtr, int structSize);
	static void createConstantBuffer(ID3D11Device * gDevice, ID3D11Buffer ** gBuffer, int bufferSize);

	// RENDER FUNCTIONS
	static void setIndexBuffer(ID3D11Buffer* gIndexBuffer, DXGI_FORMAT format, size_t offset);
	static void setVertexBuffer(size_t start, size_t numBuffers, ID3D11Buffer** gVertexBuffer, size_t* stride, size_t* offset);
	static void setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	static void draw(size_t numVertices, size_t start);
	static void drawIndexed(size_t numIndex, size_t start, int baseVertexLoc);
	static void swapBackBuffer();

	// GET FUNCTIONS
	static int						getWidth();
	static int						getHeight();
	static IDXGISwapChain*&			GETgSwapChain();
	static ID3D11Device*&			GETgDevice();
	static ID3D11DeviceContext*&	GETgDevCon();
	static ID3D11RenderTargetView*&	GETgRTV();
	static ID3D11DepthStencilView*&	GETgDSV();
	static ID3D11Texture2D*&		GETgDSB();


	// RELEASE OF MEMORY
	static void Release();
};

//______________________________________________//
//                                              //
//                 END OF D3D                   //
//______________________________________________//
//////////////////////////////////////////////////
#endif
