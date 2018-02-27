#pragma once
#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <list>
#include "GameObject.h"
#include "GraphicsComponent.h"

using namespace DirectX::SimpleMath;
class GamePlayState;
class RectangleComponent;

class GUIManager
{
private:
	GamePlayState * pGPS = nullptr;
	int tempID;
	DirectX::XMFLOAT3 cameraPos;
	DirectX::XMFLOAT3 cameraFacingDir;

	GameObject* object = nullptr;
	RectangleComponent* rect = nullptr;

	RectangleComponent* hpRect = nullptr;
	RectangleComponent* energyRect = nullptr;
	RectangleComponent* ability1Rect = nullptr;
	RectangleComponent* ability2Rect = nullptr;
	RectangleComponent* ability3Rect = nullptr;
	RectangleComponent* ability4Rect = nullptr;

	void createGUIElement(
		float r, float g, float b, float a,
		float xAdjust, float yAdjust, float zAdjust,
		float xScaling, float zScaling, float yScaling
	);
	int getID();

public:
	GUIManager();
	~GUIManager();

	int initGUI(
		int ID,
		DirectX::XMFLOAT3 cameraPos,
		DirectX::XMFLOAT3 cameraFacingDir,
		std::list<GameObject*>& GUIObjects,
		std::list<GraphicsComponent*>& graphics
	);

	RectangleComponent* GEThpRect() { return this->hpRect; }
	RectangleComponent* GETenergyRect() { return this->energyRect; }
	RectangleComponent* GETability1Rect() { return this->ability1Rect; }
	RectangleComponent* GETability2Rect() { return this->ability2Rect; }
	RectangleComponent* GETability3Rect() { return this->ability3Rect; }
	RectangleComponent* GETability4Rect() { return this->ability4Rect; }
};

#endif
 