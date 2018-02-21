
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
		this->timeSinceCast += Locator::getGameTime()->getDeltaTime();
		if (this->timeSinceCast >= this->coolDown)
		{
			this->state = SPELLSTATE::READY;
			this->timeSinceCast = 0.0;
		}
	}
}

Projectile* Spell::spawnProj(ProjProp props)
{
	Projectile* proj;
	XMFLOAT3 distance = { this->getPlayer()->getDirection() * 40 };
	XMFLOAT3 newPos = { this->getPlayer()->GETPosition() + distance };

	proj = this->getPlayer()->getPGPS()->initProjectile(newPos, this->getPlayer()->getDirection(), props);
	proj->setSpell(this);
	proj->SETrotationMatrix(this->getPlayer()->getRotationMatrix());
	proj->setRange(props.range);

	return proj;
}