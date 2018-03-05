
#include "Spell.h"
#include "SpAutoAttack.h"
#include "SpBomb.h"
#include "SpDash.h"
#include "SpFire.h"
#include "SpSwarmProjectile.h"


Spell::Spell(ActorObject* owner, NAME name)
{
	this->glyph = GLYPHTYPE::NONE;
	this->owner = owner;
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
	XMFLOAT3 distance = { this->getOwner()->getDirection() * 40 };
	XMFLOAT3 newPos = { this->getOwner()->GETPosition() + distance };

	proj = this->getOwner()->getPGPS()->initProjectile(newPos, this->getOwner(), props);

	// Attach the relevant spell to the projectile
	// (This could be optimized by adding copy constructors and using those instead of what's done below)
	Spell* projectilesSpell = nullptr;

	switch (this->name) {
	case NAME::AUTOATTACK: {
		SpAutoAttack* trueThis = static_cast<SpAutoAttack*>(this);

		projectilesSpell = new SpAutoAttack(this->getOwner());
		proj->setSpell(projectilesSpell);
		break;
	}
	case NAME::BOMB: {
		SpBomb* trueThis = static_cast<SpBomb*>(this);

		projectilesSpell = new SpBomb(this->getOwner());
		proj->setSpell(projectilesSpell);
		break;
	}
	case NAME::DASH: {
		SpDash* trueThis = static_cast<SpDash*>(this);

		projectilesSpell = new SpDash(this->getOwner());
		proj->setSpell(projectilesSpell);
		break;
	}
	case NAME::FIRE: {
		SpFire* trueThis = static_cast<SpFire*>(this);

		projectilesSpell = new SpFire(this->getOwner());
		proj->setSpell(projectilesSpell);
		break;
	}
	case NAME::ENEM_SWARM: {
		SpSwarmProjectile* trueThis = static_cast<SpSwarmProjectile*>(this);
		EnemyObject* trueCaster = static_cast<EnemyObject*>(trueThis->getOwner());

		projectilesSpell = new SpSwarmProjectile(
			trueCaster, trueThis->GETpPlayer(), trueThis->getpActiveEnemiesCount(), trueThis->getprojectilesMaxFlyingRange(), trueThis->getDamage(),
			trueThis->getAttackRange(), trueThis->getCoolDown()
		);
		proj->setSpell(projectilesSpell);
		break;
	}
	}
	

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