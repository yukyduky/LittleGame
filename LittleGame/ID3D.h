#pragma once
#ifndef ID3D_H
#define ID3D_H

#include <d3d11.h>
#include <DirectXMath.h>

struct PrimitiveVertexData
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT4 color;

	PrimitiveVertexData(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float a) :
		pos(x, y, z), normal(nx, ny, nz), color(r, g, b, a) {}
	PrimitiveVertexData(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 normal, DirectX::XMFLOAT4 color) :
		pos(pos), normal(normal), color(color) {}
	PrimitiveVertexData() {}
};

class ID3D
{
public:
	virtual void initializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed) = 0;
	virtual void createSwapChain() = 0;
	virtual void createVertexBuffer(ID3D11Buffer** gVertexBuffer, PrimitiveVertexData* vertexData, size_t* stride, size_t* offset) = 0;
	virtual void createIndexBuffer(ID3D11Buffer** gIndexBuffer, DWORD* indexData) = 0;
	virtual void setVertexBuffer(ID3D11Buffer** gVertexBuffer, size_t* stride, size_t* offset) = 0;
	virtual void setIndexBuffer(ID3D11Buffer* gIndexBuffer, size_t offset) = 0;

	virtual size_t& GETwWidth() = 0;
	virtual size_t& GETwHeight() = 0;
	virtual HWND& GEThwnd() = 0;
	virtual ID3D11Device*& GETgDevice() = 0;
	virtual ID3D11DeviceContext*& GETgDevCon() = 0;
	virtual IDXGISwapChain*& GETswapChain() = 0;
};


#endif // !D3D_H
