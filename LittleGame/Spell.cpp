
#include "Spell.h"

Spell::Spell(ActorObject* player, NAME name)
{
	this->glyph = GLYPHTYPE::NONE;
	this->player = player;
	this->name = name;
	this->timeSinceCast = 0.0;
	this->cost = 0;
}

Spell::~Spell()
{
}

void Spell::updateCD()
{
	if (this->getState() == SPELLSTATE::COOLDOWN || this->getState() == SPELLSTATE::ACTIVE)
	{
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
		this->timeSinceCast += dt;
		if (this->timeSinceCast >= this->coolDown)
		{
			this->state = SPELLSTATE::READY;
			this->timeSinceCast = 0.0;
		}
	}
}

Projectile* Spell::spawnProj(ProjProp props)
{
	Projectile* proj = nullptr;
	XMFLOAT3 distance = { this->getPlayer()->getDirection() * 40 };
	XMFLOAT3 newPos = { this->getPlayer()->GETPosition() + distance };

	proj = this->getPlayer()->getPGPS()->initProjectile(newPos, this->getPlayer()->getDirection(), props);
	proj->setSpell(this);
	proj->SETrotationMatrix(this->getPlayer()->getRotationMatrix());
	proj->setRange(props.range);

	return proj;
}

float Spell::GETremainingCoolDownFloat() {
	float returnValue;

	// NOTE: If-statement results in the ability being ready (visually) when OFF CD
	if (this->timeSinceCast <= 0)
		returnValue = 1.0f;
	else
		returnValue = (this->timeSinceCast / this->coolDown);

	return returnValue;
}