#pragma once
#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <vector>
#include "GameObject.h"
//#include "AbilityComponent.h"
#include "Locator.h"

class Projectile : public GameObject
{
private:
	float travelDist = 0;
	DirectX::XMFLOAT3 direction;
	float speed;

	//PhysicsComponent* phyComp;
	//GraphicsComponent* graphComp;
	//AbilityComponent* abilComp;

public:
	Projectile(const size_t ID, XMFLOAT3 start, XMFLOAT3 direction);
	~Projectile();
	
	float getTravelDist() { return this->travelDist; };

	void update();
};


#endif