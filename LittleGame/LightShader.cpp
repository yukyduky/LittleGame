#include "LightShader.h"


LightShader::LightShader() {

}

void LightShader::initializePipeline(ID3D11Device** pgDevice) {
	HRESULT hr;
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//									Vertex Shader									//			
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(
		L"LightVertex.hlsl",
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
		pVS->GetBufferSize(),
		nullptr,
		&this->VertexShader
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create a VertexShader", "ERROR: LightShader::initializePipeline()", MB_OK);
	}
	// Clean up
	pVS->Release();

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//									Pixel Shader									//			
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(
		L"LightPixel.hlsl",
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
		MessageBox(NULL, "Failed to create a PixelShader", "ERROR: LightShader::initializePipeline()", MB_OK);
	}
	// Clean up
	pPS->Release();

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//									Sampler State									//			
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	D3D11_SAMPLER_DESC SamplerStateDescription;
	SamplerStateDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerStateDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerStateDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerStateDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerStateDescription.MipLODBias = 0.0f;
	SamplerStateDescription.MaxAnisotropy = 1.0f;
	SamplerStateDescription.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SamplerStateDescription.BorderColor[4] = (1.0f, 1.0f, 1.0f, 1.0f);
	SamplerStateDescription.MinLOD = -3.402823466e+38F;
	SamplerStateDescription.MaxLOD = 3.402823466e+38F;

	(*pgDevice)->CreateSamplerState(&SamplerStateDescription, &this->SamplerState);
}


void LightShader::initialize(ID3D11Device** pgDevice) {
	this->initializePipeline(pgDevice);
}


void LightShader::setPipeline(ID3D11DeviceContext** pgDevCon, ID3D11RenderTargetView* *BackBufferRTV) {
	// Activates the BackBuffer & DepthStencilView as RenderTargets in the OutputMerger stage
	(*pgDevCon)->OMSetRenderTargets(
		1,
		BackBufferRTV,
		nullptr
	);

	// Set Shaders
	(*pgDevCon)->VSSetShader(this->VertexShader, nullptr, 0);
	(*pgDevCon)->HSSetShader(nullptr, nullptr, 0);
	(*pgDevCon)->DSSetShader(nullptr, nullptr, 0);
	(*pgDevCon)->GSSetShader(nullptr, nullptr, 0);
	(*pgDevCon)->PSSetShader(this->PixelShader, nullptr, 0);
	// Set Sampler
	(*pgDevCon)->PSSetSamplers(0, 1, &this->SamplerState);
}


void LightShader::render(ID3D11DeviceContext** pDevCon) {
	// Set inputlayout and vertexbuffers to null so that we can use vertexId to generate the quad
	// in the vertexshader.
	(*pDevCon)->IASetInputLayout(nullptr);
	(*pDevCon)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	// Pretty important!
	(*pDevCon)->IASetVertexBuffers(
		0,
		0,
		nullptr,
		nullptr,
		nullptr
	);

	(*pDevCon)->Draw(4, 0);
}



void LightShader::cleanUp() {
	this->VertexShader->Release();
	this->PixelShader->Release();
	this->SamplerState->Release();
}