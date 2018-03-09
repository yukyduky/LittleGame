#pragma once
#ifndef ENEMYSPELL_H
#define ENEMYSPELL_H

#include "Spell.h"

//class ActorObject;

class EnemySpell : public Spell
{
protected:
	float damage = -1;
	int projectilesMaxFlyingRange = -1;
	int* pActiveEnemiesCount = nullptr;	// Points to an int inside EnemyManager
	ActorObject * pPlayer = nullptr;

public:
	EnemySpell(EnemyObject* pShooter, int* pActiveEnemiesCount, NAME name) : Spell(pShooter, name) { 
		this->pActiveEnemiesCount = pActiveEnemiesCount;
	}
	
	float getDamage() {
		return this->damage;
	}
	int getprojectilesMaxFlyingRange() {
		return this->projectilesMaxFlyingRange;
	}
	ActorObject * GETpPlayer() {
		return this->pPlayer;
	}
	int* getpActiveEnemiesCount() {
		return this->pActiveEnemiesCount;
	}
	void setDamage(float damage) {
		this->damage = damage;
	}
	void setProjectilesMaxFlyingRange(int projectilesMaxFlyingRange) {
		this->projectilesMaxFlyingRange = projectilesMaxFlyingRange;
	}
	void setpActiveEnemiesCount(int* pActiveEnemiesCount) {
		this->pActiveEnemiesCount = pActiveEnemiesCount;
	}
	void setpPlayer(ActorObject* pPlayer) {
		this->pPlayer = pPlayer;
	}

	ActorObject* getOwner() { return static_cast<ActorObject*>(this->owner); };

	
	// Returns false if spell in unavalible to cast
	virtual bool castSpell() = 0;
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	virtual void upgrade(float modif) = 0;
	// Function called by the projectile, spells collision should be handled here
	virtual void collision(GameObject* target, Projectile* proj) = 0;
	virtual void update() = 0;
	virtual void cleanUp() = 0;

};


#endif

