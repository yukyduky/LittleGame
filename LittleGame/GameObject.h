#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <DirectXMath.h>

namespace OBJECTSTATE {
	enum class TYPE { ACTIVATED, DEAD, FROZEN, ATTACKING, STOP, FALLING, TFALLING, 
		INVISIBLE, RECOVER, RESETCOLOR, GENERATORRISING, GENERATORACTIVE, STUNNED, 
		TELEPORTED, BOSSSUBMERGE, BOSSEMERGE };
}
namespace OBJECTTYPE {
	enum TYPE {
		PLAYER, ENEMY, GENERATOR, INDESTRUCTIBLE,
		PROJECTILE, BOSS, NOT_SET,
		SIZE
	};
}

class Component;
class PhysicsComponent;
class GraphicsComponent;
class BlockComponent;
class GUIComponent;

using namespace DirectX;

struct Message
{
	OBJECTSTATE::TYPE state;
	Message(OBJECTSTATE::TYPE state) : state(state) {}
};  



class GameObject
{
private:
	XMFLOAT4X4 world;
	XMFLOAT4X4 translationMatrix;
	XMFLOAT4X4 scaleMatrix;
	XMFLOAT4X4 rotationMatrix;

protected:
	std::list<Component*> components;
	PhysicsComponent* physicsComponent = nullptr;
	GraphicsComponent* graphicsComponent = nullptr;
	GUIComponent* graphicsComponentUI = nullptr;

	const size_t ID;
	XMFLOAT3 previousPos;
	XMFLOAT3 pos;
	XMFLOAT3 direction;
	XMFLOAT3 newPos;
	XMFLOAT3 kineticVector;
	OBJECTTYPE::TYPE type;
	OBJECTSTATE::TYPE state;
	double counter = 0;
	double transitionTime = 0;

	// Movement related values
	XMFLOAT3 moveDirection;
	float velocityMagnitude = 0.0f;
	float topSpeedMagnitude = 1.0f;
	float topSpeed = 0.0f;
	float frictionFactor = 15.0f;
	bool slowed = false;


public:
	GameObject(const size_t ID) : ID(ID), pos(XMFLOAT3(0.0f, 0.0f, 0.0f)), state(OBJECTSTATE::TYPE::ACTIVATED), type(OBJECTTYPE::NOT_SET), physicsComponent(nullptr) {}
	GameObject(const size_t ID, XMFLOAT3 pos) : ID(ID), pos(pos), state(OBJECTSTATE::TYPE::ACTIVATED), type(OBJECTTYPE::NOT_SET), physicsComponent(nullptr) {}
	virtual ~GameObject() {}

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
	void nudgePos();
	const size_t getID() const { return this->ID; }

	void setPosition(XMFLOAT3 pos) { this->pos = pos; }
	void setPositionY(float value) { this->pos.y = value; }
	void SETpreviousPos(XMFLOAT3 pos) { this->previousPos = pos; }
	XMFLOAT3 GETPosition() const { return this->pos; }
	XMFLOAT3 GETpreviousPos() const { return this->previousPos; }
	void setkineticVector(XMFLOAT3 kineticVector) { this->kineticVector = kineticVector; }
	XMFLOAT3 getkineticVector() const { return this->kineticVector; }
	void SETvelocityMagnitude(float input) { this->velocityMagnitude = input; }
	virtual XMFLOAT3 getDirection() { return this->pos; }
	void setState(OBJECTSTATE::TYPE state) { this->state = state; }
	OBJECTSTATE::TYPE getState() const { return this->state; }
	XMFLOAT4X4& getWorld();
	void SETworldMatrix(XMMATRIX& wMatrix);
	void SETtranslationMatrix(XMMATRIX& translationM);
	void SETscaleMatrix(XMMATRIX& scaleM);
	void SETrotationMatrix(XMMATRIX& rotationM);
	void updateWorldMatrix();
	XMFLOAT4X4& getRotationMatrix();

	OBJECTTYPE::TYPE getType() const { return this->type; }
	void setType(OBJECTTYPE::TYPE type) { this->type = type; }

	void SETphysicsComponent(PhysicsComponent* physicsComponent_in) { this->physicsComponent = physicsComponent_in; }
	PhysicsComponent* GETphysicsComponent() { return this->physicsComponent; }

	// Graphics: BLOCK_COMPONENT
	void SETgraphicsComponent(GraphicsComponent* graphicsComponent_in) { this->graphicsComponent = graphicsComponent_in; }
	GraphicsComponent* GETgraphicsComponent() { return this->graphicsComponent; }
};

#endif // !GAMEOBJECT_H
