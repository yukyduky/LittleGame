#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"



class Projectile : public GameObject
{
public:
	Projectile(const size_t ID, XMFLOAT3 pos, float spd);
	~Projectile();

	virtual void cleanUp();
private:
	XMFLOAT3 direction;
	float speed;
};



#endif // !PROJECTILE_H
