#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include "Locator.h"
#include "RenderInputOrganizer.h"
#include "idlist.h"

enum class PROJBEHAVIOR {NONE, ENLARGE};

class Spell;
class GameObject;
class ActorObject;

class Projectile : public GameObject
{
public:
	Projectile();
	//Projectile(const size_t ID, float velocity, PROJBEHAVIOR behavior, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType, std::pair<size_t, Light*> light, IDHandler* lightIDs);
	Projectile(const size_t ID, float velocity, float maxFlyingRange, PROJBEHAVIOR behavior, GameObject* shooter, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType, size_t lightID, idlist<Light>* lights);
	virtual ~Projectile();
	
	/*Moves the projectile in this->direction with this->velocity * this->dt
	if it is dead it will cleanup and send the state to the components*/
	void update();
	virtual void cleanUp();


	float getAngleTowardsPlayer();
	void turnLeft();
	void turnRight();

	void setSpeed(float spd) { this->speed = spd; }
	float getSpeed() { return this->speed; }
	void setDirection(XMVECTOR dir);
	XMFLOAT3 getDirection();
	void setRange(int maxFlyingRange) { this->maxFlyingRange = maxFlyingRange; }
	void setSeeking(float rotationSpeed, ActorObject* pPlayer);	// Only relevant to seekling projectiles
	void setSpell(Spell* spell);
	void setSpellByName(int spellName, int glyph);
	Spell* getSpell();	// Gets allocated by player.spell->castSpell()


	// Mainly for FIRE SPELL, but can be used by all projectiles
	std::list<GameObject*>* getPreviouslyHitList() { return &this->previouslyHit; }
private:

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Affects position based on current direction and velocity.
	*/
	void move();
	void steerTowardsPlayer();

	// The speed of the projectile
	float speed = 0.0f;
	// If the pojectile should spinn around its X-axis
	bool spinn;
	bool seekingLeft = false;			// Only relevant to seek projectiles
	ActorObject* pPlayer = nullptr;		// Only relevant to seek projectiles
	bool isFollowing = false;			// Only relevant to seek projectiles
	float rotationSpeed = -1;			// Only relevant to seek projectiles
	PROJBEHAVIOR behavior;
	// Pointer to the spell to able to call the correct collision in CollsionHandler
	Spell* spell = nullptr;
	// Range of travel
	float range = 0.0f;

	size_t lightID;
	idlist<Light>* lights;
	
	int maxFlyingRange = 0;
	float rangeCounter = 0;
	
	std::list<GameObject*> previouslyHit;
};



#endif // !PROJECTILE_H
