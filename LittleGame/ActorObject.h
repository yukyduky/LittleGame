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
	AbilityComponent* abilities[5];
	AbilityComponent* ability0;
	float hp;
	float energy;


public:
	ActorObject(const size_t ID);
	ActorObject(const size_t ID, Vector3 pos);
	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Moves the Actor according to data fetched from the internal InputComponent
	*/
	// 
	void move();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Affects the position of the ActorObject
	*/
	// 
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

	void SETinputComponent(InputComponent* pInputComponent);
	InputComponent* GETinputComponent();



};



#endif
