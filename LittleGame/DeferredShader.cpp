#include "DeferredShader.h"

DeferredShader::DeferredShader() {
	this->VertexLayout = nullptr;
	this->VertexShader = nullptr;
	this->GeometryShader = nullptr;
	this->PixelShader = nullptr;
	this->SamplerState = nullptr;
}

void DeferredShader::initializePipeline(ID3D11Device** pgDevice) {
	HRESULT hr;
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//							    	Vertex Shader									//
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/*
	- Create VertexShader
	- Create InputLayout
	*/
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(
		L"DefVertex.hlsl",
		nullptr,
		nullptr,
		"VertexMain",
		"vs_5_1",
		0,
		0,
		&pVS,
		nullptr
	);
	hr = (*pgDevice)->CreateVertexShader(
		pVS->GetBufferPointer(), 
		pVS->GetBufferSize(), nullptr,
		&this->VertexShader
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create a VertexShader", "ERROR: DeferredShader::initializeShaders()", MB_OK);
	}

	D3D11_INPUT_ELEMENT_DESC InputLayoutDescription[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	hr = (*pgDevice)->CreateInputLayout(
		InputLayoutDescription, 
		ARRAYSIZE(InputLayoutDescription), 
		pVS->GetBufferPointer(), 
		pVS->GetBufferSize(), 
		&this->VertexLayout
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create a VertexLayout", "ERROR: DeferredShader::initializeShaders()", MB_OK);
	}
	// Clean up
	pVS->Release();

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//							    	Geometry Shader									//
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	ID3DBlob* pGS = nullptr;
	ID3DBlob* error_GS = nullptr;

	D3DCompileFromFile(
		L"DefGeometry.hlsl",
		nullptr,
		nullptr,
		"GeometryMain",
		"gs_5_1",
		0,
		0,
		&pGS,
		&error_GS
	);
	
	if (error_GS)
	{
		OutputDebugStringA((char*)error_GS->GetBufferPointer());
		error_GS->Release();
	}

	hr = (*pgDevice)->CreateGeometryShader(
		pGS->GetBufferPointer(),
		pGS->GetBufferSize(),
		nullptr,
		&this->GeometryShader
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create a GeometryShader", "ERROR: DeferredShader::initializeShaders()", MB_OK);
	}
	// Clean up
	pGS->Release();

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//							    	Pixel Shader									//
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(
		L"DefPixel.hlsl",
		nullptr,
		nullptr,
		"PixelMain",
		"ps_5_1",
		0,
		0,
		&pPS,
		nullptr
	);
	hr = (*pgDevice)->CreatePixelShader(
		pPS->GetBufferPointer(),
		pPS->GetBufferSize(),
		nullptr,
		&this->PixelShader
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create a PixelShader", "ERROR: DeferredShader::initializeShaders()", MB_OK);
	}

	pPS->Release();

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//							    	SamplerState									//
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	D3D11_SAMPLER_DESC SamplerDescription;
	SamplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // Linear interpolation for Minification,Magnification,Mip-level-Sampling.
	SamplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;	// Keep repeating the texture,
	SamplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;	// in case of values not between,
	SamplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	// 0-1.
	SamplerDescription.MipLODBias = 0.0f;	// Offset from the calculated MipMap level.
	SamplerDescription.MaxAnisotropy = 1;	// Only relevant if .filter = ANISOTROPIC|COMPARISON_ANISOTROPIC
	SamplerDescription.ComparisonFunc = D3D11_COMPARISON_ALWAYS; // Comparison will always pass; Difference between source- & destination-data is irrelevant.
	SamplerDescription.BorderColor[0] = 0; // Bordercolour to be used,
	SamplerDescription.BorderColor[1] = 0; // if .AdressX is set to
	SamplerDescription.BorderColor[2] = 0; // TEXTURE_ADDRESS_BORDER
	SamplerDescription.BorderColor[3] = 0;
	SamplerDescription.MinLOD = 0;					// Lower end of the mipmap range to clamp access to. (0 is the largest and most detailed mipmaplevel and higher levels are smaller and less detailed)
	SamplerDescription.MaxLOD = D3D11_FLOAT32_MAX;	// Upper end of the mipmap range to clamp access to. (No upper limit = D3D11_FLOAT32_MAX)

	hr = (*pgDevice)->CreateSamplerState(
		&SamplerDescription,
		&this->SamplerState
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create a PixelShader", "ERROR: DeferredShader::initializeShaders()", MB_OK);
	}
}


void DeferredShader::initialize(ID3D11Device** pgDevice) {
	this->initializePipeline(pgDevice);
}


void DeferredShader::activatePipeline(ID3D11DeviceContext** pgDevCon) {
	// Set InputLayout & PrimitiveTopology
	(*pgDevCon)->IASetInputLayout(this->VertexLayout);
	(*pgDevCon)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set all the shaders to the pipeline
	(*pgDevCon)->VSSetShader(this->VertexShader, nullptr, 0);
	(*pgDevCon)->HSSetShader(nullptr, nullptr, 0);
	(*pgDevCon)->DSSetShader(nullptr, nullptr, 0);
	(*pgDevCon)->GSSetShader(this->GeometryShader, nullptr, 0);
	(*pgDevCon)->PSSetShader(this->PixelShader, nullptr, 0);

	// Set Sampler States in the relevant shader.
	(*pgDevCon)->PSSetSamplers(0, 1, &this->SamplerState);
}


void DeferredShader::render() {

}


void DeferredShader::cleanUp() {
	this->VertexLayout->Release();
	this->VertexShader->Release();
	this->GeometryShader->Release();
	this->PixelShader->Release();
	this->SamplerState->Release();
	
	this->VertexLayout = nullptr;
	this->VertexShader = nullptr;
	this->GeometryShader = nullptr;
	this->PixelShader = nullptr;
	this->SamplerState = nullptr;
}