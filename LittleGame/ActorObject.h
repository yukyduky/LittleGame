#pragma once
#ifndef ACTOROBJECT_H
#define ACTOROBJECT_H

#include "GameObject.h"
#include "InputComponent.h"
#include "Locator.h"
#include "LevelManager.h"

#include "D3D.h"
#include "list"
#include <vector>

class GamePlayState;
class Spell;
class Crosshair;

namespace ABILITIES {
	enum KEYS {
		ABILITY0, ABILITY1, ABILITY2, ABILITY3, ABILITY4, SIZE
	};
}

class ActorObject : public GameObject
{
protected:
	InputComponent * pInput = nullptr;
	//Vector with all Spells that the player can cast
	std::vector<Spell*> spells;
	//Current spell that wil be cast by fireAbilityX
	Spell* selectedSpell = nullptr;
	int selectedSpellIntValue = 0;
	float hp = 0;
	float hpMAX = 0;
	TILESTATE::STATE statusEffect = TILESTATE::STATE::ACTIVE;
	float counter = 0.0f;
	float slowedVelocity;
	float realVelocity;

	float energy = 100;
	float energyMAX = 100;

	//Used to calculate angle to fire
	float rotation = 0;
	XMFLOAT3 direction = { 0, 0, 0 };

	//Pointer to be able to initiate projectiles in GamePlayState
	GamePlayState* pGPS = nullptr;

	Crosshair* crossHair = nullptr;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Only currently sets the pos, doesn't update world with it.
	*/
	ActorObject(const size_t ID, XMFLOAT3 pos, float velocity, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType, float hp_in);
	virtual ~ActorObject() {}
	virtual const size_t getID();
	virtual GamePlayState* getPGPS();
	virtual float getRotation();
	virtual void setDirection();
	virtual void setDirection(XMFLOAT3 direction);
	virtual XMFLOAT3 getDirection();
	virtual XMFLOAT3 getDirection(float length);
	virtual void setSpeed(float speed);
	virtual float GEThp() { return this->hp; }
	virtual float GEThpMAX() { return this->hpMAX; }
	std::vector<Spell*> GETSpells() { return this->spells; };
	virtual float GEThpRemainingFloat() { return (this->hp / this->hpMAX); }

	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
	virtual void update();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Moves the Actor according to data fetched from the internal InputComponent
	2. Only called when the player is using a controller
	*/
	void move();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Affects the position of the ActorObject
	2. Only called when the player is using a keyboard
	*/
	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Moves the Actor according to data fetched from the internal InputComponent
	*/
	void rotate();
	void rotate(XMFLOAT3 aimVec);
	void rotate(XMFLOAT2 aimVec);
	void fireAbility0();
	void selectAbility1();
	void selectAbility2();
	void selectAbility3();
	void selectAbility4();
	void fireAbilityX();
	void pauseMenu();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Sets pInputComponent as both a directlink and components.push_back()
	*/
	void SETinputComponent(InputComponent* pInputComponent);
	InputComponent* GETinputComponent();

	//Lowers the cooldown of each ability
	void decCD();	//To be implemented into actors update from another branch
	// Deals dmg to the Actors Hp
	void dealDmg(float dmg);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Depletes the players energy by a certain amount.
	2. NOTE: Should the function return true, then the energy HAS BEEN DEPLETED.
	*/
	bool useEnergy(float energyUse);
	void addEnergy(float energyGain);
	float GETenergyRemainingFloat() { return (this->energy / this->energyMAX); }
	
	// Adds a spell to the vector with avalible spells
	void addSpell(Spell* spell);
	// Goes over each spell and switches to new spells, depending on what glyph is on it
	void switchSpell();
	// Return vector of spells
	std::vector<Spell*> GETspellsVector() { return this->spells; }
	int GETcurrentSpellInt() { return this->selectedSpellIntValue; }
	void changeSpell(int spell, int glyph);

	//Crosshair
	void addCrosshair(Crosshair* cross) { this->crossHair = cross; }

	// For enemies
	Spell* getFirstSpell();
	void applyStatusEffect(TILESTATE::STATE effect);
};



#endif
