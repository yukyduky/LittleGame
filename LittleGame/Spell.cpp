
#include "Spell.h"
#include "SpAutoAttack.h"
#include "SpBomb.h"
#include "SpDash.h"
#include "SpFire.h"
#include "SpSwarmProjectile.h"
#include "SpBossBulletHell.h"

//#include "GamePlayState.h"


Spell::Spell(GameObject* owner, NAME name)
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

Projectile* Spell::spawnProj(ProjProp props, Light light)
{
	Projectile* proj = nullptr;
	XMFLOAT3 dir = this->owner->getDirection();
	XMFLOAT3 distance = { dir * 40 };
	XMFLOAT3 newPos = { this->owner->GETPosition() + distance };
	light.pos = newPos;
	proj = GamePlayState::getInstance()->initProjectile(newPos, this->owner, props, light);
	//proj = this->getOwner()->getPGPS()

	// Attach the relevant spell to the projectile
	// (This could be optimized by adding copy constructors and using those instead of what's done below)
	Spell* projectilesSpell = nullptr;

	switch (this->name) {
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
		case NAME::BULLETHELL: {
			SpBossBulletHell* trueThis = static_cast<SpBossBulletHell*>(this);
			EnemyObject* trueCaster = static_cast<EnemyObject*>(trueThis->getOwner());

			projectilesSpell = new SpBossBulletHell(
				trueCaster, trueThis->GETpPlayer(), trueThis->getpActiveEnemiesCount(), trueThis->getprojectilesMaxFlyingRange(), trueThis->getDamage(),
				trueThis->getAttackRange(), trueThis->getCoolDown()
			);
			proj->setSpell(projectilesSpell);
			break;
		}
		default:
			proj->setSpellByName((int)this->name, (int)this->glyph);
			proj->SETrotationMatrix(XMLoadFloat4x4(&this->owner->getRotationMatrix())); // Enemies dont turn, can be added later
			break;
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