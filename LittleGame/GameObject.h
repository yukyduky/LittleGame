#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <DirectXMath.h>
#include <SimpleMath.h>


enum class OBJECTSTATE { IDLE, MOVING, DEAD, FROZEN, STOP };
enum class OBJECTTYPE { PLAYER, ENEMY, DOODAD, INDESTRUCTIBLE, PROJECTILE };

class Component;

using namespace DirectX;

struct Message
{
	OBJECTSTATE state;
	Message(OBJECTSTATE state) : state(state) {}
};



class GameObject
{
private:
	XMMATRIX world;
	XMMATRIX translationMatrix;
	XMMATRIX scaleMatrix;
	XMMATRIX rotationMatrix;

protected:
	std::list<Component*> components;
	const size_t ID;
	XMFLOAT3 pos;
	XMFLOAT3 velocity;
	OBJECTSTATE state;
	OBJECTTYPE type;

public:
	GameObject(const size_t ID) : ID(ID), pos(XMFLOAT3(0.0f, 0.0f, 0.0f)), state(OBJECTSTATE::IDLE) {}
	GameObject(const size_t ID, XMFLOAT3 pos) : ID(ID), pos(pos), state(OBJECTSTATE::IDLE) {}


	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Send the parameter 'msg'(obj) to all components that have been added to the object.
	*/
	void send(Message msg);
	void update();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleans up the GameObject and all the attached components.
	*/
	virtual void cleanUp() = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Adds a component using the 'components.push_back()' function.
	*/
	void addComponent(Component* component);
	const size_t getID() const { return this->ID; }

	void setPosition(XMFLOAT3 pos) { this->pos = pos; }
	XMFLOAT3 getPosition() const { return this->pos; }
	void setVelocity(XMFLOAT3 velocity) { this->velocity = velocity; }
	XMFLOAT3 getVelocity() const { return this->velocity; }
	void setState(OBJECTSTATE state) { this->state = state; }
	OBJECTSTATE getState() const { return this->state; }
	XMMATRIX& getWorld() { return this->world; }
	void SETworldMatrix(XMMATRIX wMatrix) { this->world = wMatrix; }
	void SETtranslationMatrix(XMMATRIX translationM) { this->translationMatrix = translationM; }
	void SETscaleMatrix(XMMATRIX scaleM) { this->scaleMatrix = scaleM; }
	void SETrotationMatrix(XMMATRIX rotationM) { this->rotationMatrix = rotationM; }
	void updateWorldMatrix(XMFLOAT3 newPos);

	OBJECTTYPE getType() const { return this->type; }

};

#endif // !GAMEOBJECT_H
