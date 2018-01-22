#include "DeferredTexture2Ds.h"
#include "D3D.h"

DeferredTexture2Ds::DeferredTexture2Ds() {
	for (int i = 0; i < GBUFFERCOUNT; i++) {
		this->Gbuffers[i] = nullptr;
		this->GbufferRTVs[i] = nullptr;
		this->GbufferSRVs[i] = nullptr;
	}
	this->DepthStencilBuffer = nullptr;
	this->DepthStencilView = nullptr;
	this->DepthStencilSRV = nullptr;
}

void DeferredTexture2Ds::initializeGbuffers(ID3D11Device** pgDevice, int screenWidth, int screenHeight) {
	HRESULT hr;
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//			Gbuffers,	 GbufferRenderTargetViews,	GbufferShaderResourceViews		//
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/*
	- Create Description for all Gbuffers
	- Create Description for all GbufferRenderTargetViews
	- Create Description for all GbufferShaderResourceViews
	- Loop the creation of a set (a Gbuffer, and a renderTargetView + ShaderResourceView for it)
	  until all sets are done.
	*/

	D3D11_TEXTURE2D_DESC Texture2DDescription;
	ZeroMemory(&Texture2DDescription, sizeof(Texture2DDescription));
	Texture2DDescription.Width = screenWidth;
	Texture2DDescription.Height = screenHeight;
	Texture2DDescription.MipLevels = 0;		// '0' generates a full set of subtextures.
	Texture2DDescription.ArraySize = 1;		// We're only using '1' texture.
	Texture2DDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // The datatype per pixel, here with four components.
	Texture2DDescription.SampleDesc.Count = 1;	// Multisamples per pixel.
	Texture2DDescription.SampleDesc.Quality = 0;	// Image quality level.
	Texture2DDescription.Usage = D3D11_USAGE_DEFAULT;	// Will only be read/written to by GPU.
	Texture2DDescription.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // Texture will both be rendered to and read from by shaders.
	Texture2DDescription.CPUAccessFlags = 0;
	Texture2DDescription.MiscFlags = 0;

	// 
	D3D11_RENDER_TARGET_VIEW_DESC RenderTargetViewDescription;
	ZeroMemory(&RenderTargetViewDescription, sizeof(RenderTargetViewDescription));
	RenderTargetViewDescription.Format = Texture2DDescription.Format;
	RenderTargetViewDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RenderTargetViewDescription.Texture2D.MipSlice = 0;

	//
	D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDescription;
	ShaderResourceViewDescription.Format = Texture2DDescription.Format;
	ShaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	ShaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
	ShaderResourceViewDescription.Texture2D.MipLevels = 1;

	// For each GBuffer (Color, Normals, etc)
	for (int i = 0; i < GBUFFERCOUNT; i++) {

		// Create the Texture2D
		hr = (*pgDevice)->CreateTexture2D(
			&Texture2DDescription,
			NULL,
			&this->Gbuffers[i]
		);
		if (FAILED(hr)) {
			MessageBox(NULL, "Failed to create a Texture2D", "ERROR: DeferredTexture2Ds::InitiateGbuffers()", MB_OK);
		}


		// Create the RenderTargetView for that Texture2D
		hr = (*pgDevice)->CreateRenderTargetView(
			this->Gbuffers[i],
			&RenderTargetViewDescription,
			&this->GbufferRTVs[i]
		);
		if (FAILED(hr)) {
			MessageBox(NULL, "Failed to create a RenderTargetView", "ERROR: DeferredTexture2Ds::InitiateGbuffers()", MB_OK);
		}


		// Create the ShaderResourceView for that Texture2D
		hr = (*pgDevice)->CreateShaderResourceView(
			this->Gbuffers[i],
			&ShaderResourceViewDescription,
			&this->GbufferSRVs[i]
		);
		if (FAILED(hr)) {
			MessageBox(NULL, "Failed to create a ShaderResourceView", "ERROR: DeferredTexture2Ds::InitiateGbuffers()", MB_OK);
		}
	}
}


void DeferredTexture2Ds::initializeDepth(ID3D11Device** pgDevice, int screenWidth, int screenHeight) {
	HRESULT hr;
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//																					//
	//							DepthBuffer,	DepthStencilView						//			
	//																					//
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/*
	- Create Description for DepthStencilBuffer and then create it.
	- Create Description for DepthStencilView and connect it to the DepthStencilBuffer.
	- Create Description for DepthShaderResourceView and connect it to the DepthStencilBuffer.
	*/
	// Description for the DepthBuffer
	D3D11_TEXTURE2D_DESC DepthBufferDescription;
	ZeroMemory(&DepthBufferDescription, sizeof(DepthBufferDescription));
	DepthBufferDescription.Width = screenWidth;
	DepthBufferDescription.Height = screenHeight;
	DepthBufferDescription.MipLevels = 1;
	DepthBufferDescription.ArraySize = 1;
	DepthBufferDescription.Format = DXGI_FORMAT_R24G8_TYPELESS; // This specific format needed so that it can later be used as a shader resource.
	DepthBufferDescription.SampleDesc.Count = 1;
	DepthBufferDescription.SampleDesc.Quality = 0;
	DepthBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	DepthBufferDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	DepthBufferDescription.CPUAccessFlags = 0;
	DepthBufferDescription.MiscFlags = 0;
	// Creation of the DepthBuffer
	hr = (*pgDevice)->CreateTexture2D(
		&DepthBufferDescription,
		NULL,
		&this->DepthStencilBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create Texture2D for DepthStencilBuffer", "ERROR: DeferredTexture2Ds::initializeDepth", MB_OK);
	}


	// Description for the DepthStencilView
	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDescription;
	ZeroMemory(&DepthStencilViewDescription, sizeof(DepthStencilViewDescription));
	DepthStencilViewDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // Needed so that it can work with the format specified above, and for the same reasons.
	DepthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDescription.Texture2D.MipSlice = 0;
	// Creation of the DepthStencilView
	hr = (*pgDevice)->CreateDepthStencilView(
		this->DepthStencilBuffer,
		&DepthStencilViewDescription,
		&this->DepthStencilView
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create DepthStencilView for DepthStencilBuffer", "ERROR: DeferredTexture2Ds::initializeDepth", MB_OK);
	}

	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ Everything related to the last ShaderResourceView-Index, The Depth Buffer. +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/* Necessary formats so that Depth can be used as a GBuffer:

	"The texture resource for the depth buffer is created using the
	R24G8_TYPELESS texture format and the depth/stencil view is created
	with the D24_UNORM_S8_UINT texture format. When accessing the
	depth buffer in the pixel shader, the shader resource view is created
	using the R24_UNORM_X8_TYPELESS texture format since the stencil value is unused."

	*/
	// Description for the DepthStencilSRV
	D3D11_SHADER_RESOURCE_VIEW_DESC DepthStencilSRVDescription;
	ZeroMemory(&DepthStencilSRVDescription, sizeof(DepthStencilSRVDescription));
	DepthStencilSRVDescription.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS; // This specific format is needesd so that.. same reason as format in depthBuffer & DepthView.
	DepthStencilSRVDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	DepthStencilSRVDescription.Texture2D.MostDetailedMip = 0;
	DepthStencilSRVDescription.Texture2D.MipLevels = 1;
	// Creation of the DepthStencilSRV
	hr = (*pgDevice)->CreateShaderResourceView(
		this->DepthStencilBuffer,
		&DepthStencilSRVDescription,
		&this->DepthStencilSRV
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to create ShaderResourceView for DepthStencilBuffer", "ERROR: DeferredTexture2Ds::initializeDepth", MB_OK);
	}
}


void DeferredTexture2Ds::initialize(ID3D11Device** pgDevice, int screenWidth, int screenHeight) {
//	this->initializeGbuffers(pgDevice, screenWidth, screenHeight);
//	this->initializeDepth(pgDevice, screenWidth, screenHeight);
}

void DeferredTexture2Ds::setAllSRVs(ID3D11DeviceContext** pgDevCon) {
	// Merge Gbuffer/Depth SRVs
	ID3D11ShaderResourceView* MergedSRVs[SRVCOUNT];
	for (int i = 0; i < GBUFFERCOUNT; i++) {
		MergedSRVs[i] = this->GbufferSRVs[i];
	}
	MergedSRVs[GBUFFERCOUNT] = this->DepthStencilSRV;

	// Set SRVs to the PixelShader
	(*pgDevCon)->PSGetShaderResources(
		1,	// Why is the starterslot '1'?
		SRVCOUNT,
		MergedSRVs
	);

	// Cut the pointer connection to prevent destruction of pointers
	for (int i = 0; i < SRVCOUNT; i++) {
		MergedSRVs[i] = nullptr;
	}
}

void DeferredTexture2Ds::setAllRTVs(ID3D11DeviceContext** pgDevCon) {
	(*pgDevCon)->OMSetRenderTargets(
		GBUFFERCOUNT,
		this->GbufferRTVs,
		this->DepthStencilView
	);
}

void DeferredTexture2Ds::clearAllRTVs(
	ID3D11DeviceContext** pgDevCon,
	float					ClearColor_Red,
	float					ClearColor_Blue,
	float					ClearColor_Green,
	float					ClearColor_Alpha
) {
	float colour[4];
	colour[0] = ClearColor_Red;
	colour[1] = ClearColor_Blue;
	colour[2] = ClearColor_Green;
	colour[3] = ClearColor_Alpha;

	// Clears all RenderTarget's
	for (int i = 0; i < GBUFFERCOUNT; i++) {
		(*pgDevCon)->ClearRenderTargetView(this->GbufferRTVs[i], colour);
	}

	// Clear the DepthStencilView
	(*pgDevCon)->ClearDepthStencilView(
		this->DepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0,
		0
	);
}

void DeferredTexture2Ds::CleanUp() {
	// Clean up all the GBuffer related data
	for (int i = 0; i < GBUFFERCOUNT; i++) {
		this->Gbuffers[i]->Release();
		this->Gbuffers[i] = nullptr;

		this->GbufferRTVs[i]->Release();
		this->GbufferRTVs[i] = nullptr;

		this->GbufferSRVs[i]->Release();
		this->GbufferSRVs[i] = nullptr;
	}

	// Clean up the Depth related data
	this->DepthStencilBuffer->Release();
	this->DepthStencilBuffer = nullptr;
	this->DepthStencilView->Release();
	this->DepthStencilView = nullptr;
	this->DepthStencilSRV->Release();
	this->DepthStencilSRV = nullptr;
}