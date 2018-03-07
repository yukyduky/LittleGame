#include "Projectile.h"
#include "Component.h"
#include "RenderInputOrganizer.h"

Projectile::Projectile() : GameObject(-1)
{
	this->setState(OBJECTSTATE::TYPE::DEAD);
}

Projectile::Projectile(const size_t ID, float speed, bool spinn, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType, std::pair<size_t, Light*> light, IDHandler* lightIDs) : GameObject(ID, pos)
{
	this->setState(OBJECTSTATE::TYPE::ACTIVATED);
	this->setType(OBJECTTYPE::PROJECTILE);
	this->spell = nullptr;

	this->type = objectType;
	this->direction = dir;
	this->speed = speed;
	this->spinn = spinn;
	this->velocity = XMFLOAT3(dir.x * this->speed, dir.y * this->speed, dir.z * this->speed);
	this->rangeCounter = 0;

	this->light = light;
	this->lightIDs = lightIDs;
}

Projectile::Projectile(const size_t ID, float speed, PROJBEHAVIOR behavior, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType, std::pair<size_t, Light*> light, IDHandler * lightIDs) : GameObject(ID, pos)
{
	this->setState(OBJECTSTATE::TYPE::ACTIVATED);
	this->setType(OBJECTTYPE::PROJECTILE);
	this->spell = nullptr;

	this->type = objectType;
	this->direction = dir;
	this->speed = speed;
	this->behavior = behavior;
	this->velocity = XMFLOAT3(dir.x * this->speed, dir.y * this->speed, dir.z * this->speed);
	this->rangeCounter = 0;

	this->light = light;
	this->lightIDs = lightIDs;
}

Projectile::~Projectile()
{
}

void Projectile::cleanUp()
{
	this->lightIDs->remove(this->light.first);
	this->light.second->diffuse = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->light.second->ambient = XMFLOAT3(0.0f, 0.0f, 0.0f);

	for (auto &c : this->components) {
		c->cleanUp();
		delete c;
	}
}

void Projectile::setDirection(XMVECTOR dir) {
	DirectX::XMStoreFloat3(&this->direction, dir);
}

DirectX::XMFLOAT3 Projectile::getDirection()
{	
	return this->direction;
}

Spell * Projectile::getSpell()
{
	return this->spell;
}



void Projectile::update()
{
	//GameObject::update();

	for (auto &i : this->components) {
		i->update();
	}

	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->pos.x += this->direction.x * this->speed * dt;
	// Projectiles dosnt move in Y
	this->pos.z += this->direction.z * this->speed * dt;
	this->setPosition(pos);
	this->light.second->pos = pos;
	if (this->spinn)
	{
		XMVECTOR dir = XMLoadFloat3(&this->direction);
		XMMATRIX rotM = XMLoadFloat4x4(&this->getRotationMatrix());
		this->SETrotationMatrix(rotM * XMMatrixRotationAxis(dir, static_cast<float>(this->rangeCounter)));
	}
	else if (this->behavior == PROJBEHAVIOR::ENLARGE)
	{
		float size = this->rangeCounter * 4.0f;
		XMMATRIX scaleM = XMMatrixScaling(size, size, size);
		this->GETphysicsComponent()->updateBoundingArea(size);
		this->SETscaleMatrix(scaleM);
	}

	this->rangeCounter++;
	if (this->rangeCounter >= this->range && this->range != -1.0f)
	{
		this->setState(OBJECTSTATE::TYPE::DEAD);
	}
	
}

