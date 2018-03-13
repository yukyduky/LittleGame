#include "SpBossBulletHell.h"
#include "Spell.h"

SpBossBulletHell::SpBossBulletHell(EnemyObject* pShooter, ActorObject* pPlayer, int* pActiveEnemiesCount,
	int range, int dmg, int attackRange, double cooldown) : EnemySpell(pShooter, pActiveEnemiesCount, NAME::BULLETHELL)
{
	this->pPlayer = pPlayer;
	this->projectilesMaxFlyingRange = range;
	this->damage = dmg;
	this->attackRange = attackRange;
	this->setCoolDown(cooldown);
	this->counter = 0.0f;
//	this->currentPattern = Locator::getRandomGenerator()->GenerateInt(0, ATTACKPATTERN::SZIE - 1);
	this->currentPattern = ATTACKPATTERN::NORMAL;
}
SpBossBulletHell::~SpBossBulletHell()
{
}

bool SpBossBulletHell::castSpell()
{
	this->counter += Locator::getGameTime()->getDeltaTime();
	if (this->counter > 10.0f) {
		Locator::getRandomGenerator()->GenerateInt(0, ATTACKPATTERN::SZIE - 1);
	}
	this->actOwner = static_cast<ActorObject*>(this->getOwner());
	XMVECTOR dirVec;
	XMMATRIX rotationM = XMMatrixRotationY(this->radians);
	XMFLOAT3 dir = { 0.0f, 0.0f, 0.0f };
	bool returnValue = true;
	//Temporary template for the light
	Light light;
	light.pos = this->getOwner()->GETPosition();
	light.diffuse = XMFLOAT3(0.25f, 0.0f, 0.0f);
	light.ambient = XMFLOAT3(0.0f, 0.0f, 0.0f);
	light.attenuation = XMFLOAT3(0.0f, 0.0001f, 0.0001f);
	light.specPower = 0.0f;

	ProjProp props(10, XMFLOAT4(1.0f, 0.01f, 0.01f, 1.0f), 400.0f, this->projectilesMaxFlyingRange, true);
	Projectile* pProj;
	Projectile* pProj2;

	if (this->getState() == SPELLSTATE::COOLDOWN) {
		returnValue = false;
	}
	else {
		switch (this->currentPattern)
		{
		case ATTACKPATTERN::NORMAL:
			dir = this->getOwner()->getDirection();
			if (dir.z > 0.9f && this->radians > 0.0f) {
				this->radians *= -1.0f;
			}
			else if (dir.z < -0.9f && this->radians < 0.0f) {
				this->radians *= -1.0f;
			}
			dirVec = DirectX::XMLoadFloat3(&dir);
			DirectX::XMVector3Normalize(dirVec);
			dirVec = DirectX::XMVector3Rotate(dirVec, DirectX::XMQuaternionRotationMatrix(rotationM));
			DirectX::XMStoreFloat3(&dir, dirVec);
			this->getOwner()->setDirection(dir);
			pProj = this->spawnProj(props, light);
			dir.z *= -1.0f;
			this->getOwner()->setDirection(dir);
			pProj2 = this->spawnProj(props, light);
			dir.z *= -1.0f;
			this->getOwner()->setDirection(dir);
			/// ADD A SOUND FOR THE ATTACK HERE.
			// Locator::getAudioManager()->play(SOUNDE::NAME::BEEP4);
			/// 

			this->setState(SPELLSTATE::COOLDOWN);
			break;
		case ATTACKPATTERN::RANDOM:
			break;
		case ATTACKPATTERN::WAVE:
			break;
		default:
			break;
		}
		
		
	}
	return returnValue;
}

void SpBossBulletHell::upgrade(float modif)
{

}

void SpBossBulletHell::collision(GameObject* target, Projectile* proj)
{
	OBJECTTYPE::TYPE type = target->getType();
	XMFLOAT3 dir;
	XMVECTOR vecDir;
	XMFLOAT3 pos;
	switch (type) {
	case OBJECTTYPE::PLAYER:
		static_cast<ActorObject*>(target)->dealDmg(this->damage);
		proj->setState(OBJECTSTATE::TYPE::DEAD);
		break;
	case OBJECTTYPE::INDESTRUCTIBLE:
		dir = proj->getDirection();
		dir.z *= -1.0f;
		vecDir = XMLoadFloat3(&dir);
		proj->setDirection(vecDir);
		pos = proj->GETpreviousPos();
		pos.x += dir.x * 30.0f;
		pos.z += dir.z * 30.0f;
		proj->setPosition(pos);
		break;
	}
}

void SpBossBulletHell::update()
{
	this->updateCD();
}

void SpBossBulletHell::cleanUp()
{
	(*this->pActiveEnemiesCount)--;
}