#pragma once
#ifndef DAMAGESPELL_H
#define DAMAGESPELL_H

#include "Spell.h"
#include "Projectile.h"

enum class NAME { EXPLOSION };

class DamageSpell : public Spell
{
public:
	DamageSpell(NAME name);
	~DamageSpell();

	bool castSpell();
	void upgrade(float modif);

private:
	float strength;
	NAME name;

};

DamageSpell::DamageSpell(NAME name)
{
	this->strength = 1;
	this->name = name;

}

DamageSpell::~DamageSpell()
{
}

#endif // !DAMAGESPELL_H
