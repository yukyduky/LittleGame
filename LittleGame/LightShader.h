#pragma once
#ifndef LIGHTSHADER_H
#define LIGHTSHADER_H
#include "d3d11.h"
#include "d3dcompiler.h"

class LightShader {
private:
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader*	PixelShader;
	ID3D11SamplerState*	SamplerState;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes the internal VertexShader & PixelSHader
	2. Initializes the internal SamplerState.
	*/
	void initializePipeline(ID3D11Device** pgDevice);


public:
	LightShader();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes the internal VertexShader & PixelShader
	2. Initializes the internal SamplerState.
	*/
	void initialize(ID3D11Device** pgDevice);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Sets the BackBufferRTV as the only RenderTarget in the OM.
	2. Sets the entire shader pipeline after the LightShader
	3. Sets a sampler to the pixel shader.
	*/
	void setPipeline(ID3D11DeviceContext** pgDevCon, ID3D11RenderTargetView* *BackBufferRTV);

	void render(ID3D11DeviceContext** pDevCon);

	void cleanUp();


};

#endif