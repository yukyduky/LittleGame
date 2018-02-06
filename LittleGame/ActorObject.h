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

#include "D3D.h"
#include "list"
#include <vector>

class GamePlayState;
class Spell;


namespace ABILITIES {
	enum KEYS {
		ABILITY0, ABILITY1, ABILITY2, ABILITY3, ABILITY4, SIZE
	};
}

class ActorObject : public GameObject
{
private:
	InputComponent * pInput;
	std::vector<Spell*> spells;
	Spell* selectedSpell;
	float hp;
	float energy;
	float speed;

	//Used to calculate angle to fire
	float rotation = 0;

	//Cooldown counters, {time of cast, cooldown}
	size_t autoAttCD[2] = {0, 20 };

	GamePlayState* pGPS = nullptr;

public:
	ActorObject(const size_t ID);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Only currently sets the pos, doesn't update world with it.
	*/
	ActorObject(const size_t ID, XMFLOAT3 pos, GamePlayState* pGPS);
	virtual const size_t getID();
	virtual GamePlayState* getPGPS();
	virtual float getRotation();
	virtual XMFLOAT3 getDirection();
	virtual void setSpeed(float speed);

	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();

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
					//Is in fireability0() in this version
	
	// SPELLS
	void addSpell(Spell* spell);
};



#endif
