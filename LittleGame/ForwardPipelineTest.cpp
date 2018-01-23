#include "ForwardPipelineTest.h"

FPLT::FPLT()
{
	this->vertices.push_back(tVertex(-0.5, -0.5, 0.5));
	this->vertices.push_back(tVertex(-0.5, 0.5, 0.5));
	this->vertices.push_back(tVertex(0.5, 0.5, 0.5));
	this->vertices.push_back(tVertex(0.5, -0.5, 0.5));

	this->colors.push_back(tVertex(1.0, 0.0, 0.0));
	this->colors.push_back(tVertex(0.0, 1.0, 0.0));
	this->colors.push_back(tVertex(0.0, 0.0, 1.0));
	this->colors.push_back(tVertex(1.0, 0.0, 0.0));

	this->indices.push_back(DWORD(0));
	this->indices.push_back(DWORD(1));
	this->indices.push_back(DWORD(2));
	this->indices.push_back(DWORD(0));
	this->indices.push_back(DWORD(2));
	this->indices.push_back(DWORD(3));
}

FPLT::~FPLT()
{
}

void FPLT::init()
{
	

	
	std::vector<D3D11_INPUT_ELEMENT_DESC> test;
	test.push_back(*this->layout);


	D3D::createFixedShaders(&this->vLayout, &this->vShader, &this->pShader, this->fileNameVertex, this->fileNamePixel, this->layout, 2);

	D3D::setFixedShaders(this->vShader, this->pShader);

	int size = 0;
	size = this->indices.size();

	DWORD* index = new DWORD[size];
	int counter = 0;
	for (std::vector<DWORD>::iterator it = this->indices.begin(); it != this->indices.end(); ++it) 
	{
		index[counter] = *it;
		counter++;
	}
	DWORD test2 = 90;
	for (int i = 0; i < 6; i++)
	{
		test2 = index[i];
	}

	D3D::createIndexBuffer(index, &this->iBuffer, sizeof(DWORD) * 2 * 3);


}