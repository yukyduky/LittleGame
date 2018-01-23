#pragma once
#ifndef FORWARDPIPELINETEST_H_
#define FORWARDPIPELINETEST_H_
#include "D3D.h"
#include <vector>


struct tVertex
{
	float x, y, z;
	tVertex (float x, float y, float z) 
		: x(x), y(y), z(z){}
};

class FPLT
{
private:
	std::vector<tVertex> vertices;
	std::vector<tVertex> colors;
	std::vector<DWORD> indices;

	ID3D11VertexShader* vShader;
	ID3D11PixelShader* pShader;
	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;
	ID3D10Blob* VS_Buffer;
	ID3D10Blob* PS_Buffer;
	ID3D11InputLayout* vLayout;
	HRESULT hr;
	
	const wchar_t* fileNameVertex = L"forwardVertex.hlsl";
	const wchar_t* fileNamePixel = L"forwardPixel.hlsl";
	//The input-layout description
	D3D11_INPUT_ELEMENT_DESC layout[2] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

public:
	FPLT();
	~FPLT();

	void init();

};


#endif FORWARDPIPELINETEST_H_