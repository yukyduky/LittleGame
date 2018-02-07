#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <DirectXMath.h>


namespace OBJECTSTATE {
	enum class TYPE { IDLE, MOVING, DEAD, FROZEN, STOP };
}
namespace OBJECTTYPE {
	enum TYPE {
		PLAYER, ENEMY, DOODAD, INDESTRUCTIBLE,
		PROJECTILE, NOT_SET,
		SIZE
	};
}

class Component;
class PhysicsComponent;

using namespace DirectX;

struct Message
{
	OBJECTSTATE::TYPE state;
	Message(OBJECTSTATE::TYPE state) : state(state) {}
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
	PhysicsComponent* physicsComponent;

	const size_t ID;
	XMFLOAT3 pos;
	XMFLOAT3 velocity;
	OBJECTTYPE::TYPE type;
	OBJECTSTATE::TYPE state;

public:
	GameObject(const size_t ID) : ID(ID), pos(XMFLOAT3(0.0f, 0.0f, 0.0f)), state(OBJECTSTATE::TYPE::IDLE), type(OBJECTTYPE::NOT_SET) {}
	GameObject(const size_t ID, XMFLOAT3 pos) : ID(ID), pos(pos), state(OBJECTSTATE::TYPE::IDLE), type(OBJECTTYPE::NOT_SET) {}


	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Send the parameter ' msg '(obj) to all components that have been added to the object.
	*/
	void send(Message msg);
	virtual void update() = 0;
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
	XMFLOAT3 GETPosition() const { return this->pos; }
	void setVelocity(XMFLOAT3 velocity) { this->velocity = velocity; }
	XMFLOAT3 getVelocity() const { return this->velocity; }
	void setState(OBJECTSTATE::TYPE state) { this->state = state; }
	OBJECTSTATE::TYPE getState() const { return this->state; }
	XMMATRIX& getWorld() { return this->world; }
	void SETworldMatrix(XMMATRIX wMatrix) { this->world = wMatrix; }
	void SETtranslationMatrix(XMMATRIX translationM) { this->translationMatrix = translationM; }
	void SETscaleMatrix(XMMATRIX scaleM) { this->scaleMatrix = scaleM; }
	void SETrotationMatrix(XMMATRIX rotationM) { this->rotationMatrix = rotationM; }
	void updateWorldMatrix();
	XMMATRIX getRotationMatrix() { return this->rotationMatrix; }

	OBJECTTYPE::TYPE getType() const { return this->type; }
	void setType(OBJECTTYPE::TYPE type) { this->type = type; }

	void SETphysicsComponent(PhysicsComponent* physicsComponent_in) { this->physicsComponent = physicsComponent_in; }
	PhysicsComponent* GETphysicsComponent() { return this->physicsComponent; }
};

#endif // !GAMEOBJECT_H
