#include "Shader.h"


Shader::Shader()
{
}

void Shader::SetShaders(ID3D11DeviceContext * gDevCon)
{
	SetVertexShader(gDevCon);
	SetPixelShader(gDevCon);
	SetInputlayout(gDevCon);
}

bool Shader::CreateShaders(ID3D11Device* gDevice, const wchar_t* fileNameVertex, const wchar_t* fileNamePixel, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize)
{
	// Create Vertex Shader
	if (!CreateVertexShader(gDevice, fileNameVertex, inputDesc, inputDescSize))
	{
		MessageBox(0, "Vertex Shader Initialization - Failed", "Error", MB_OK);
		return false;
	}

	// Create Pixel Shader
	if (!CreatePixelShader(gDevice, fileNamePixel))
	{
		MessageBox(0, "Pixel Shader Initialization - Failed", "Error", MB_OK);
		return false;
	}

	return true;
}

void Shader::Release()
{
	gVertexShader->Release();
	gPixelShader->Release();
	gVertexLayout->Release();
}

bool Shader::CreateVertexShader(ID3D11Device* gDevice, const wchar_t* fileName, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize)
{
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(
		fileName,		// filename
		nullptr,			// optional macros
		nullptr,			// optional include files
		"VS",				// entry point
		"vs_5_0",			// shader model (target)
		0,					// shader compile options			// here DEBUGGING OPTIONS
		0,					// effect compile options
		&pVS,				// double pointer to ID3DBlob		
		nullptr				// pointer for Error Blob messages.
							// how to use the Error blob, see here
							// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
		);

	// Create Vertex shader
	hr = gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &gVertexShader);
	if (FAILED(hr))
	{
		MessageBox(0, "Vertex Shader - Failed", "Error", MB_OK);
		return false;
	}

	// Create input layout
	if (!CreateInputLayout(gDevice, pVS, inputDesc, inputDescSize))
		return false;

	pVS->Release();

	return true;
}

bool Shader::CreatePixelShader(ID3D11Device* gDevice, const wchar_t* fileName)
{
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(
		fileName,			// filename
		nullptr,			// optional macros
		nullptr,			// optional include files
		"PS",				// entry point
		"ps_5_0",			// shader model (target)
		0,					// shader compile options
		0,					// effect compile options
		&pPS,				// double pointer to ID3DBlob		
		nullptr				// pointer for Error Blob messages.
							// how to use the Error blob, see here
							// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
		);

	// Create Pixel shader
	hr = gDevice->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &gPixelShader);
	if (FAILED(hr))
	{
		MessageBox(0, "Pixel Shader - Failed", "Error", MB_OK);
		return false;
	}

	pPS->Release();

	return true;
}

bool Shader::CreateInputLayout(ID3D11Device* gDevice, ID3DBlob* pVS, const D3D11_INPUT_ELEMENT_DESC* inputDesc, int inputDescSize)
{
	// Create the Input Layout
	hr = gDevice->CreateInputLayout(inputDesc, inputDescSize, pVS->GetBufferPointer(), pVS->GetBufferSize(), &gVertexLayout);
	if (FAILED(hr))
	{
		MessageBox(0, "Input Layout - Failed", "Error", MB_OK);
		return false;
	}

	return true;
}

void Shader::SetVertexShader(ID3D11DeviceContext * gDevCon) const
{
	gDevCon->VSSetShader(gVertexShader, nullptr, 0);
}

void Shader::SetPixelShader(ID3D11DeviceContext* gDevCon) const
{
	gDevCon->PSSetShader(gPixelShader, nullptr, 0);
}

void Shader::SetInputlayout(ID3D11DeviceContext* gDevCon) const
{
	gDevCon->IASetInputLayout(gVertexLayout);
}
