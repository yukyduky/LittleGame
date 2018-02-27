#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <DirectXMath.h>


namespace OBJECTSTATE {
	enum class TYPE { ACTIVATED, DEAD, FROZEN, ATTACKING, STOP, FALLING, TFALLING, INVISIBLE, RECOVER, RESETCOLOR };
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
class BlockComponent;

using namespace DirectX;

struct Message
{
	OBJECTSTATE::TYPE state;
	Message(OBJECTSTATE::TYPE state) : state(state) {}
};  



class GameObject
{
private:
	//XMMATRIX world;
	//XMMATRIX translationMatrix;
	//XMMATRIX scaleMatrix;
	//XMMATRIX rotationMatrix;
	XMFLOAT4X4 world;
	XMFLOAT4X4 translationMatrix;
	XMFLOAT4X4 scaleMatrix;
	XMFLOAT4X4 rotationMatrix;

protected:
	std::list<Component*> components;
	PhysicsComponent* physicsComponent = nullptr;
	BlockComponent* graphicsComponent = nullptr;

	const size_t ID;
	XMFLOAT3 pos;
	XMFLOAT3 velocity;
	OBJECTTYPE::TYPE type;
	OBJECTSTATE::TYPE state;
	double counter = 0;
	double transitionTime = 0;

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
	XMFLOAT3 GETPosition() const { return this->pos; }
	void setVelocity(XMFLOAT3 velocity) { this->velocity = velocity; }
	XMFLOAT3 getVelocity() const { return this->velocity; }
	void setState(OBJECTSTATE::TYPE state) { this->state = state; }
	OBJECTSTATE::TYPE getState() const { return this->state; }
	XMFLOAT4X4& getWorld();
	void SETworldMatrix(XMMATRIX& wMatrix);
	void SETtranslationMatrix(XMMATRIX& translationM);
	void SETscaleMatrix(XMMATRIX& scaleM);
	void SETrotationMatrix(XMMATRIX& rotationM);
	void updateWorldMatrix();
	XMMATRIX getRotationMatrix();

	OBJECTTYPE::TYPE getType() const { return this->type; }
	void setType(OBJECTTYPE::TYPE type) { this->type = type; }

	void SETphysicsComponent(PhysicsComponent* physicsComponent_in) { this->physicsComponent = physicsComponent_in; }
	PhysicsComponent* GETphysicsComponent() { return this->physicsComponent; }

	void SETgraphicsComponent(BlockComponent* graphicsComponent_in) { this->graphicsComponent = graphicsComponent_in; }
	BlockComponent* GETgraphicsComponent() { return this->graphicsComponent; }
};

#endif // !GAMEOBJECT_H
