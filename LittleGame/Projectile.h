#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include "Locator.h"

class Spell;
class GameObject;
class ActorObject;

class Projectile : public GameObject
{
public:
	Projectile(const size_t ID, float speed, bool spinn, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType);
	~Projectile();

	/*Moves the projectile in this->direction with this->velocity * this->dt
	if it is dead it will cleanup and send the state to the components*/
	void update();
	virtual void cleanUp();


	float getAngleTowardsPlayer();
	void turnLeft(float speed);
	void turnRight(float speed);

	void setSpeed(float spd) { this->speed = spd; }
	float getSpeed() { return this->speed; }
	void setDirection(XMVECTOR dir);
	XMVECTOR getDirection();
	void setRange(int range) { this->range = range; }
	void setSeeking(float seekSpeed, ActorObject* playerPos);	// Only relevant to stalking projectiles
	void setSpell(Spell* spell);
	Spell* getSpell();	// Gets allocated by player.spell->castSpell()

private:

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Affects position based on current direction and velocity.
	*/
	void move();

	// The speed of the projectile
	float speed = 0.0f;
	// If the pojectile should spinn around its X-axis
	bool spinn;
	ActorObject* pPlayer = nullptr;		// Only relevant to seek projectiles
	bool isFollowing = false;			// Only relevant to seek projectiles
	float seekSpeed = -1;				// Only relevant to seek projectiles
	// Pointer to the spell to able to call the correct collision in CollsionHandler
	Spell* spell = nullptr;
	// Range of travel
	int range = 0;
	int rangeCoutner = 0;
};



#endif // !PROJECTILE_H
