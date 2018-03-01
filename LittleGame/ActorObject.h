#pragma once
#ifndef ACTOROBJECT_H
#define ACTOROBJECT_H

#include "GameObject.h"
#include "AbilityComponent.h"
#include "InputComponent.h"
#include "Locator.h"
//#include "GraphicsComponent.h"
//#include "KeyboardComponent.h"
//*#include "ControllerComponent.h"
//#include "GamePlayState.h"
//#include "Crosshair.h"

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
	float hp = 0;
	float energy = 0;

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
	ActorObject(const size_t ID, XMFLOAT3 pos, float velocity, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType);
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

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Sets pInputComponent as both a directlink and components.push_back()
	*/
	void SETinputComponent(InputComponent* pInputComponent);
	InputComponent* GETinputComponent();

	//Lowers the cooldown of each ability
	void decCD();	//To be implemented into actors update from another branch
	// Deals dmg to the Actors Hp
	void dealDmg(float dmg);
	
	// Adds a spell to the vector with avalible spells
	void addSpell(Spell* spell);
	// Goes over each spell and switches to new spells, depending on what glyph is on it
	void switchSpell();

	//Crosshair
	void addCrosshair(Crosshair* cross) { this->crossHair = cross; }

	// For enemies
	Spell* getFirstSpell();
};



#endif
