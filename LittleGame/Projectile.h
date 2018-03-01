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
	void setRange(float range) { this->range = range; }

	Spell* getSpell() ;

	// Mainly for FIRE SPELL, but can be used by all projectiles
	std::list<GameObject*>* getPreviouslyHitList() { return &this->previouslyHit; }
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
	float range = 0.0f;
	int rangeCounter = 0;
	
	std::list<GameObject*> previouslyHit;
};



#endif // !PROJECTILE_H
