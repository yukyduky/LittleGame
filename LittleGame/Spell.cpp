
#include "Spell.h"
#include "SpAutoAttack.h"
#include "SpBomb.h"
#include "SpDash.h"
#include "SpFire.h"
#include "SpSwarmProjectile.h"


Spell::Spell(ActorObject* actor, NAME name)
{
	this->glyph = GLYPHTYPE::NONE;
	this->actor = actor;
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
	Projectile* proj = nullptr;
	XMFLOAT3 distance = { this->getActor()->getDirection() * 40 };
	XMFLOAT3 newPos = { this->getActor()->GETPosition() + distance };

	proj = this->getActor()->getPGPS()->initProjectile(newPos, this->getActor(), props);
//	proj->SETrotationMatrix(this->getActor()->getRotationMatrix());
//	proj->setRange(props.range); 

	// Attach the relevant spell to the projectile
	// (This could be optimized by adding copy constructors and using those instead of what's done below)
	Spell* projectilesSpell = nullptr;

	switch (this->name) {
	case NAME::AUTOATTACK: {
		SpAutoAttack* trueThis = static_cast<SpAutoAttack*>(this);

		projectilesSpell = new SpAutoAttack(this->getActor());
		proj->setSpell(projectilesSpell);
		break;
	}
	case NAME::BOMB: {
		SpBomb* trueThis = static_cast<SpBomb*>(this);

		projectilesSpell = new SpBomb(this->getActor());
		proj->setSpell(projectilesSpell);
		break;
	}
	case NAME::DASH: {
		SpDash* trueThis = static_cast<SpDash*>(this);

		projectilesSpell = new SpDash(this->getActor());
		proj->setSpell(projectilesSpell);
		break;
	}
	case NAME::FIRE: {
		SpFire* trueThis = static_cast<SpFire*>(this);

		projectilesSpell = new SpFire(this->getActor());
		proj->setSpell(projectilesSpell);
		break;
	}
	case NAME::ENEM_SWARM: {
		SpSwarmProjectile* trueThis = static_cast<SpSwarmProjectile*>(this);
		EnemyObject* trueCaster = static_cast<EnemyObject*>(trueThis->getActor());

		projectilesSpell = new SpSwarmProjectile(
			nullptr, trueThis->getRange(), trueThis->getDamage(),
			trueThis->getAggroRange(), trueThis->getCoolDown()
		);
		proj->setSpell(projectilesSpell);
		break;
	}
	}
	

	return proj;
}