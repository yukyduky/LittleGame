#include "Crosshair.h"

Crosshair::Crosshair(ActorObject* player, const size_t ID) : GameObject(ID)
{
	this->player = player;
	this->type = OBJECTTYPE::DOODAD;

	this->radius = 60;
}

Crosshair::~Crosshair()
{
}

void Crosshair::receive(GameObject & obj, Message msg)
{

}

void Crosshair::cleanUp()
{
	// Cleanup all the components
	for (auto &c : this->components) {
		c->cleanUp();
		delete c;
	}

}

void Crosshair::update()
{
	XMFLOAT3 newPos{ this->player->GETPosition() };
	XMFLOAT3 dir(this->player->getDirection(this->radius));
	this->setPosition(XMFLOAT3 (newPos.x + dir.x, newPos.y, newPos.z + dir.z));
	this->SETrotationMatrix(XMLoadFloat4x4(&this->player->getRotationMatrix()));
	for (auto &i : this->components) {
		i->update();
	}
}
