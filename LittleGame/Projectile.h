#pragma once
#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject
{
private:
	DirectX::XMFLOAT3 startPos;
	DirectX::XMFLOAT3 direction;

public:
	Projectile(const size_t ID, XMFLOAT3 direction, XMFLOAT3 startPos);
	~Projectile();


};


#endif