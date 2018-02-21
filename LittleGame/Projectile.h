#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include "Locator.h"

class Spell;

class Projectile : public GameObject
{
public:
	Projectile(const size_t ID, float speed, bool spinn, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType);
	~Projectile();

	/*Moves the projectile in the direction of the velocity with speed of this->speed, 
	if it is dead it will cleanup and send the state to the components*/
	void update();
	virtual void cleanUp();

	void setSpeed(float spd) { this->speed = spd; }
	float getSpeed() { return this->speed; }
	void setDirection(XMVECTOR dir);
	XMVECTOR getDirection();
	void setSpell(Spell* spell) { this->spell = spell; }
	void setRange(int range) { this->range = range; }

	Spell* getSpell() ;
private:
	// traveldirection of the projectile
	XMFLOAT3 direction;
	// The speed of the projectile
	float speed = 0.0f;
	// If the pojectile should spinn around its X-axis
	bool spinn;
	// Pointer to the spell to able to call the correct collision in CollsionHandler
	Spell* spell = nullptr;
	// Range of travel
	int range = 0;
	int rangeCoutner = 0;
};



#endif // !PROJECTILE_H
