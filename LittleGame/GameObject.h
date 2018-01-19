#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <SimpleMath.h>

enum class OBJECTSTATE { IDLE, MOVING, DEAD, FROZEN, STOP };

class Component;

using namespace DirectX;
using namespace DirectX::SimpleMath;

struct Message
{
	OBJECTSTATE state;
	Message(OBJECTSTATE state) : state(state) {}
};

class GameObject
{
public:
	GameObject(const size_t ID) : ID(ID), pos(Vector2(0.0f, 0.0f)), state(OBJECTSTATE::IDLE) {}
	GameObject(const size_t ID, Vector2 pos) : ID(ID), pos(pos), state(OBJECTSTATE::IDLE) {}
	virtual ~GameObject();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Send the parameter 'msg'(obj) to all components that have been added to the object.
	*/
	void send(Message msg);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Adds a component using the 'components.push_back()' function.
	*/
	void addComponent(Component* component);
	const size_t getID() const { return this->ID; }
	void setPosition(Vector2 pos) { this->pos = pos; }
	Vector2 getPosition() const { return this->pos; }
	void setVelocity(Vector2 velocity) { this->velocity = velocity; }
	Vector2 getVelocity() const { return this->velocity; }
	void setState(OBJECTSTATE state) { this->state = state; }
	OBJECTSTATE getState() const { return this->state; }
private:
	std::list<Component*> components;
	const size_t ID;
	Vector2 pos;
	Vector2 velocity;
	OBJECTSTATE state;
};

#endif // !GAMEOBJECT_H
