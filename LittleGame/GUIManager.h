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
#include "ActorObject.h"

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

	RectangleComponent* rectHP = nullptr;
	RectangleComponent* rectEnergy = nullptr;
	RectangleComponent* rectAbility1 = nullptr;
	RectangleComponent* rectAbility2 = nullptr;
	RectangleComponent* rectAbility3 = nullptr;
	RectangleComponent* rectAbility4 = nullptr;

	// vColor colorHP = { 255.0f, 0.0f, 0.0f, 255.0f };
	vColor colorHP = { 1.0f, 0.0f, 0.0f, 1.0f };
	// vColor colorEnergy = { 0.95687f, 226.0f, 67.0f, 255.0f };
	vColor colorEnergy = { 0.95687f, 0.88628f, 0.26285f, 1.0f };
	// vColor colorAbility1 = { 255.0f, 25.5f, 127.5f, 255.0f };
	vColor colorAbility1 = { 1.0f, 0.1f, 0.5f, 1.0f };
	//vColor colorAbility2 = { 80.0f, 80.0f, 80.0f, 255.0f };
	vColor colorAbility2 = { 0.31373f, 0.31373f, 0.31373f, 1.0f };
	// vColor colorAbility3 = { 255.0f, 128.0f, 0.0f, 255.0f };
	vColor colorAbility3 = { 1.0f, 0.50196f, 0.0f, 1.0f };
	// vColor colorAbility4 = { 0.0f, 102.0f, 255.0f, 255.0f };
	vColor colorAbility4 = { 0.0f, 0.4f, 1.0f, 1.0f };

	vColor colorBack = { 0.25f, 0.25f, 0.25f, 0.0f };

	void createGUIElement(
		float r, float g, float b, float a,
		float xAdjust, float yAdjust, float zAdjust,
		float xScaling, float zScaling, float yScaling
	);

	void updateGUIElement(RectangleComponent* element, float remainingCooldownFloat);

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

	void updateGUI(ActorObject* player);

	RectangleComponent* GETrectHP() { return this->rectHP; }
	RectangleComponent* GETrectEnergy() { return this->rectEnergy; }
	RectangleComponent* GETrectAbility1() { return this->rectAbility1; }
	RectangleComponent* GETrectAbility2() { return this->rectAbility2; }
	RectangleComponent* GETrectAbility3() { return this->rectAbility3; }
	RectangleComponent* GETrectAbility4() { return this->rectAbility4; }

	vColor GETcolorHP() { return this->colorHP; };
	vColor GETcolorEnergy() { return this->colorEnergy; }
	vColor GETcolorAbility1() { return this->colorAbility1; }
	vColor GETcolorAbility2() { return this->colorAbility2; }
	vColor GETcolorAbility3() { return this->colorAbility3; }
	vColor GETcolorAbility4() { return this->colorAbility4; }
};

#endif
 