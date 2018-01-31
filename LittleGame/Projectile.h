#pragma once
#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <vector>
#include "GameObject.h"
#include "AbilityComponent.h"
#include "Locator.h"

class Projectile : public GameObject
{
private:
	float travelDist = 0;
	DirectX::XMFLOAT3 direction;

	//std::vector<PhysicsComponent*> projPhy;
	//std::vector<GraphicsComponent*> projGraph;

public:
	Projectile(const size_t ID, XMFLOAT3 direction, float travelDist);
	~Projectile();
	
	float getTravelDist() { return this->travelDist; };

	void update();
};


#endif