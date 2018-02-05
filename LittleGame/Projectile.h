#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include "Locator.h"

class DamageSpell;

class Projectile : public GameObject
{
public:
	Projectile(const size_t ID, XMFLOAT3 pos);
	~Projectile();

	void update();
	virtual void cleanUp();

	void setSpeed(float spd) { this->speed = spd; }
	float getSpeed() { return this->speed; }
	void setDirection(XMFLOAT3 dir) { this->direction = dir; }
	XMFLOAT3 getDirection() { return this->direction; }
	void setSpell(DamageSpell* spell) { this->spell = spell; }

	DamageSpell* getSpell() ;
private:
	XMFLOAT3 direction;
	float speed;
	DamageSpell* spell;
};



#endif // !PROJECTILE_H
