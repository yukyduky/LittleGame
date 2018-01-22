#pragma once
#ifndef DEFERREDTEXTURE2DS_H
#define DEFERREDTEXTURE2DS_H

#include <d3d11.h>
#define GBUFFERCOUNT 3 // Color, Normal, Diffuse
#define SRVCOUNT (GBUFFERCOUNT + 1) // Color, Normal, Diffuse, Depth

class DeferredTexture2Ds {
private:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	- Gbuffers will be used as rendertargets to which data will be outputted
	from the 1st pass and read from in the 2nd pass.
	- GbufferRenderTargetViews are lenses used to render to the Texture2Ds.
	- GbufferShaderResourceViews are lenses used to read from the Texture2Ds.
	*/
	ID3D11Texture2D* Gbuffers[GBUFFERCOUNT];
	ID3D11RenderTargetView*	GbufferRTVs[GBUFFERCOUNT];
	ID3D11ShaderResourceView* GbufferSRVs[GBUFFERCOUNT];
	void initializeGbuffers(ID3D11Device** pgDevice, int screenWidth, int screenHeight);


	ID3D11Texture2D* DepthStencilBuffer;
	ID3D11DepthStencilView* DepthStencilView;
	ID3D11ShaderResourceView* DepthStencilSRV;
	void initializeDepth(ID3D11Device** pgDevice, int screenWidth, int screenHeight);



public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Prepares for initialization by setting all internal pointers to nullptr.
	*/
	DeferredTexture2Ds();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes the Gbuffer Texture2D/RTV/SRV-context.
	2. Initializes the Depthstencil Texture2D/StencilView/SRV-context.
	*/
	void initialize(ID3D11Device** pgDevice, int screenWidth, int screenHeight);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. 
	*/
	void setAllSRVs(ID3D11DeviceContext** pgDevCon);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Sets the internal GBuffer Texture2D RTVs to the pipeline.
	2. Sets the internal DepthStencilView to the pipeline.
	*/
	void setAllRTVs(ID3D11DeviceContext** pgDevCon);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Clears ALL of the internal Texture2D RTVs, including DepthStencilView.
	*/
	void clearAllRTVs(ID3D11DeviceContext** pgDevCon, float ClearColor_Red, float ClearColor_Blue, float ClearColor_Green, float ClearColor_Alpha);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Releases Gbuffer Texture2Ds/RTVs/SRVs.
	2. Releases Depth Texture2D/StencilView/SRV.
	*/
	void CleanUp();
};






#endif