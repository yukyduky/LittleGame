#pragma once
#ifndef ACTOROBJECT_H
#define ACTOROBJECT_H

#include "GameObject.h"
#include "AbilityComponent.h"
#include "InputComponent.h"
//#include "GraphicsComponent.h"
//#include "KeyboardComponent.h"
//*#include "ControllerComponent.h"

#include "D3D.h"
#include "list"
#include <vector>


namespace ABILITIES {
	enum KEYS {
		ABILITY0, ABILITY1, ABILITY2, ABILITY3, ABILITY4, SIZE
	};
}

class ActorObject : public GameObject
{
private:
	InputComponent * pInput;
	// -------------TEMPLATE
	AbilityComponent* abilities[5];
	AbilityComponent* ability0;
	// -------------TEMPLATE
	float hp;
	float energy;


public:
	ActorObject(const size_t ID);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Only currently sets the pos, doesn't update world with it.
	*/
	ActorObject(const size_t ID, XMFLOAT3 pos);
	virtual const size_t getID();
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
	void selectAbilityX();
	void fireAbilityX();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Sets pInputComponent as both a directlink and components.push_back()
	*/
	void SETinputComponent(InputComponent* pInputComponent);
	InputComponent* GETinputComponent();



};



#endif
