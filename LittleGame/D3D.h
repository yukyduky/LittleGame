#pragma once
#ifndef D3D_H
#define D3D_H

#include <d3d11.h>
#include <DirectXMath.h>
#include "ID3D.h"

class D3D : public ID3D
{
private:
	IDXGISwapChain* gSwapChain;
	ID3D11Device* gDevice;
	ID3D11DeviceContext* gDevCon;
	HWND hwnd;
	size_t wWidth;
	size_t wHeight;
public:
	virtual void initializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
	virtual void createSwapChain();
	virtual void createVertexBuffer(ID3D11Buffer** gVertexBuffer, void* v, size_t& stride, size_t& offset, size_t numVertices);
	virtual void createIndexBuffer(ID3D11Buffer** gIndexBuffer, DWORD* data, size_t& numIndices);
	virtual void setVertexBuffer(ID3D11Buffer** gVertexBuffer, size_t& stride, size_t& offset);
	virtual void setIndexBuffer(ID3D11Buffer* gIndexBuffer, size_t offset);
	virtual void createConstantBuffer(ID3D11Buffer ** gBuffer, int bufferSize);
	virtual void mapConstantBuffer(ID3D11Buffer** gBuffer, void* cbPtr, int structSize);

	virtual size_t& GETwWidth();
	virtual size_t& GETwHeight();
	virtual HWND& GEThwnd();
	virtual ID3D11Device*& GETgDevice();
	virtual ID3D11DeviceContext*& GETgDevCon();
	virtual virtual IDXGISwapChain*& GETswapChain();
};


#endif // !D3D_H
