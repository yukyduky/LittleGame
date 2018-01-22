#pragma once
#ifndef DEFERREDSHADER_H
#define DEFERREDSHADER_H
#include "d3d11.h"
#include "d3dcompiler.h"


class DeferredShader {
private:
	ID3D11InputLayout*		VertexLayout;
	ID3D11VertexShader*		VertexShader;
	ID3D11GeometryShader*	GeometryShader;
	ID3D11PixelShader*		PixelShader;
	ID3D11SamplerState*		SamplerState;

	void initializePipeline(ID3D11Device** pgDevice);

public:
	DeferredShader();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Anub'ArakOBAMA'BOBI.
	2. Dobidoby.
	*/
	void initialize(ID3D11Device** pgDevice);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Anub'ArakOBAMA'BOBI.
	2. Dobidoby.
	*/
	void activatePipeline(ID3D11DeviceContext** pgDevCon);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Anub'ArakOBAMA'BOBI.
	2. Dobidoby.
	*/
	void render();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Anub'ArakOBAMA'BOBI.
	2. Dobidoby.
	*/
	void cleanUp();



};






#endif