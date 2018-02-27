#pragma once
#ifndef ENEMYSPELL_H
#define ENEMYSPELL_H

#include "Spell.h"

class ActorObject;

class EnemySpell : public Spell
{
protected:
	float damage = -1;
	int range = -1;
	ActorObject * pPlayer = nullptr;

public:
	EnemySpell(EnemyObject* pShooter, NAME name) : Spell(pShooter, name) { }
	
	float getDamage() {
		return this->damage;
	}
	float getRange() {
		return this->range;
	}
	ActorObject * getPlayer() {
		return this->pPlayer;
	}
	void setDamage(float damage) {
		this->damage = damage;
	}
	void setRange(float range) {
		this->range = range;
	}
	void setpPlayer(ActorObject* pPlayer) {
		this->pPlayer = pPlayer;
	}
	
	// Returns false if spell in unavalible to cast
	virtual bool castSpell() = 0;
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	virtual void upgrade(float modif) = 0;
	// Function called by the projectile, spells collision should be handled here
	virtual void collision(GameObject* target, Projectile* proj) = 0;
	virtual void update() = 0;

};


#endif

