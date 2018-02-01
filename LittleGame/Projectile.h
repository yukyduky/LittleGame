#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include "Locator.h"



class Projectile : public GameObject
{
public:
	Projectile(const size_t ID, XMFLOAT3 pos, float spd);
	~Projectile();

	void update();
	virtual void cleanUp();
private:
	XMFLOAT3 direction;
	float speed;
};



#endif // !PROJECTILE_H
