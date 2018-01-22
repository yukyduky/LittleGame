#pragma once
#ifndef DEFERRED_H
#define DEFERRED_H
#include "d3d11.h"
#include "DeferredTexture2Ds.h"
#include "DeferredShader.h"
#include "LightShader.h"

class Deferred {
private:
	DeferredTexture2Ds* Gbuffers;
	DeferredShader* deferredShader;
	LightShader* lightShader;

	ID3D11Device** pgDevice;
	ID3D11DeviceContext** pgDevCon;
	ID3D11RenderTargetView** pgBackBufferRTV;

	void unbindAllRTVs();
	void unbindAllSRVs();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. 
	2. 
	3. 
	*/
	void activateFirstPassPipeline();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Unbinds Gbuffer-Texture2Ds as SRVs so that they can be bound as RTVs
	2. Activates FirstPassPipeline (RenderTargets, Shaders, Samplers)
	3. Renders Objects.
	*/
	void activateSecondPassPipeline();
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Unbinds Gbuffer-Texture2Ds as SRVs so that they can be bound as RTVs
	2. Activates FirstPassPipeline (RenderTargets, Shaders, Samplers)
	3. Renders Objects.
	*/
	void renderSceneToTextures();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Unbinds Gbuffer-Texture2Ds as RTVs so that they can be bound as SRVs.
	2. Activates SecondPassPipeline (RenderTargets, ShaderResourceViews, Shaders, Samplers).
	3. Renders a quad to the BackBufferRTV.
	*/
	void secondPass();

	

public:
	Deferred();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Attaches the Device/DeviceContext/BackBufferRTV to internal pointers for easier management.
	2. Initializes internal GBuffers class.
	3. Initializes internal DeferredShader class. 
	4. Initializes internal LightShader class.
	*/
	void initialize(ID3D11Device** pgDevice, ID3D11DeviceContext** pgDevCon, ID3D11RenderTargetView** BackBufferRTV, int screenWidth, int ScreenHeight);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Renders the scene to textures in the "First Pass" of deferred shading.
	2. Renders the scene to the BackBufferRTV in the "Second Pass" of deferred shading.
	*/
	void render(int tempInput);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calls the respective cleanUp() functions for Gbuffers/deferredShader/lightShader.
	2. Deletes Gbuffers/deferredShader/lightShader.
	*/
	void cleanUp();


};






#endif