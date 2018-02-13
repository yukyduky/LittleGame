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
	//State used to make a object fall and after a set time the object "dies"
	case OBJECTSTATE::TYPE::FALLING:
		this->velocity.y += gravity * dt * 4;
		this->pos.y += this->velocity.y * dt;
		if (this->pos.y < -500.0f) {
			this->pos.y = -500.0f;
			this->velocity.y = 0.0f;
			this->state = OBJECTSTATE::TYPE::INVISIBLE;
		}
		this->updateWorldMatrix();
		break;
	//State used to restore the arena floor at the end of the stage.
	case OBJECTSTATE::TYPE::RECOVER:
		this->velocity.y += gravity * dt * 4;
		this->pos.y -= this->velocity.y * dt;
		if (this->pos.y > -0.5) {
			this->pos.y = -0.5;
			this->state = OBJECTSTATE::TYPE::RESETCOLOR;
		}
		this->updateWorldMatrix();
		break;
	default:
		break;
	}

}