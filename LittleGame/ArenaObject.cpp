#include "ArenaObject.h"
#include "Component.h"
#include "Locator.h"

ArenaObject::ArenaObject(const size_t ID)
	: GameObject(ID)
{
	this->counter = 0.0f;
	this->transitionTime = 5.0f;
}

ArenaObject::ArenaObject(const size_t ID, XMFLOAT3 pos)
	: GameObject(ID, pos)
{
	this->counter = 0.0f;
	this->transitionTime = 5.0f;
}

ArenaObject::~ArenaObject()
{

}

const size_t ArenaObject::getID()
{
	return this->ID;
}

void ArenaObject::cleanUp()
{
	for (auto &c : this->components) {
		c->getID();
		c->cleanUp();
		delete c;
	}
}

void ArenaObject::update()
{
	for (auto &i : this->components) {
		i->update();
	}	

	float gravity = -9.82;
	double dt = Locator::getGameTime()->getDeltaTime();
	
	switch (this->state)
	{
	case OBJECTSTATE::TYPE::FALLING:
		this->counter += dt;
		if (this->counter < this->transitionTime) {
			this->velocity.y += gravity * dt * 4;
			this->pos.y += this->velocity.y * dt;
			this->updateWorldMatrix();
		}
		else {
			this->velocity.y = 0.0;
			this->counter = 0.0;
		//	this->state = OBJECTSTATE::TYPE::INVISIBLE;
			this->state = OBJECTSTATE::TYPE::RECOVER;
		}
		break;
	case OBJECTSTATE::TYPE::RECOVER:
		this->counter += dt;
		this->velocity.y += gravity * dt * 4;
		this->pos.y -= this->velocity.y * dt;
		if (this->pos.y > -0.5) {
			this->pos.y = -0.5;
			this->state = OBJECTSTATE::TYPE::IDLE;
		}
		this->updateWorldMatrix();
		break;
	default:
		break;
	}

}