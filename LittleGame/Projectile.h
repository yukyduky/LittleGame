#pragma once
#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"
#include "AbilityComponent.h"
#include "GraphicsComponent.h"

class Projectile : public GameObject
{
private:
	DirectX::XMFLOAT3 startPos;
	DirectX::XMFLOAT3 direction;

public:
	Projectile(const size_t ID, XMFLOAT3 direction, XMFLOAT3 startPos);
	~Projectile();

	GraphicsComponent* graphComp;
	AbilityComponent* abiliComp;
};


#endif