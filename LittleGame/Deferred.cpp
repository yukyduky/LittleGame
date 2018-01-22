#include "Deferred.h"


Deferred::Deferred() {
	this->Gbuffers = new DeferredTexture2Ds;
	this->deferredShader = new DeferredShader;
	this->lightShader = new LightShader;
}

void Deferred::unbindAllRTVs() {
	ID3D11RenderTargetView* UnBinder[GBUFFERCOUNT] = { nullptr };
	ID3D11DepthStencilView* UnBinderDepth = nullptr;
	(*this->pgDevCon)->OMSetRenderTargets(
		GBUFFERCOUNT,
		UnBinder,
		UnBinderDepth
	);
}

void Deferred::unbindAllSRVs() {
	ID3D11ShaderResourceView* UnBinder[SRVCOUNT] = { nullptr };
	(*this->pgDevCon)->PSSetShaderResources(
		0,
		SRVCOUNT,
		UnBinder
	);
}

void Deferred::activateFirstPassPipeline() {
	// Set RTVs
	this->Gbuffers->setAllRTVs(this->pgDevCon);
	this->Gbuffers->clearAllRTVs(
		this->pgDevCon,
		0.0,
		0.0,
		0.0,
		1.0
	);

	// Set Shaders+Samplers
	this->deferredShader->activatePipeline(this->pgDevCon);
}

void Deferred::activateSecondPassPipeline() {
	// Sets Texture2Ds as ShaderResourceViews
	this->Gbuffers->setAllSRVs(this->pgDevCon);

	// Sets lightshaders internal Vertex+Pixel-Shaders + Samplerstate, Sets BackBufferRTV as the final rendertarget.
	this->lightShader->setPipeline(this->pgDevCon, this->pgBackBufferRTV);
}

void Deferred::renderSceneToTextures() {
	// Unbind Gbuffers as SRVs so they can be set as RTVs
	this->unbindAllSRVs();

	// Activate deferredShader pipeline. (Set RenderTargets and set Shaders+Sampler)
	this->activateFirstPassPipeline();

	// Render the objects.
}

void Deferred::secondPass() {
	// Unbind GBuffers as RTVs so they can be set as SRVs
	this->unbindAllRTVs();

	// Activate lightShader pipeline. (Set rendertargets, set shaderresources, set shaders+sampler)
	this->activateSecondPassPipeline();

	// Render
}

void Deferred::initialize(ID3D11Device** pgDevice, ID3D11DeviceContext** pgDevCon, ID3D11RenderTargetView** pgBackBufferRTV, int screenWidth, int screenHeight) {
	this->pgDevice = pgDevice;
	this->pgDevCon = pgDevCon;
	this->pgBackBufferRTV = pgBackBufferRTV;

	this->Gbuffers->initialize(pgDevice, screenWidth, screenHeight);
	this->deferredShader->initialize(pgDevice);
	this->lightShader->initialize(pgDevice);
}

void Deferred::render(int tempInput) {
	this->renderSceneToTextures();
	this->secondPass();
}

void Deferred::cleanUp() {
	this->Gbuffers->CleanUp();
	delete this->Gbuffers;

	this->deferredShader->cleanUp();
	delete this->deferredShader;

	this->lightShader->cleanUp();
	delete this->lightShader;
}