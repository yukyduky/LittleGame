#include "EnemyManager.h"
#include "ActorObject.h"
#include "EnemyObject.h"
#include "GamePlayState.h"
#include "Locator.h"
#include "PhysicsComponent.h"
#include "BlockComponent.h"
#include "AIComponent.h"
#include "EnemyAttackComponent.h"
#include "ImmolationEnemyAttack.h"
#include "EnemyAttackingState.h"
#include "EnemyMovingState.h"
#include "StateManager.h"
#include "EndState.h"
#include "SwarmerEnemyAttack.h"
#include "SpSwarmProjectile.h"
#include "SpEnemyImmolation.h"

EnemyManager::EnemyManager()
{
	this->pGPS = nullptr;
	this->activeEnemiesCount = 0;
}

EnemyManager::EnemyManager(GamePlayState& pGPS, std::vector<ActorObject*> players)
{
	// Set up pointers
	this->pGPS = &pGPS;
	this->players = players; 
	this->activeEnemiesCount = 0;
}

void EnemyManager::startLevel1()
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.2;
	this->waveInterval = 5;
	this->currentWaveCount = 4;
	this->currentWaveSize = 20;
	Wave* currentWave;
	this->swarmerCount = 5;
	std::vector<EnemyObject*> localSwarmers;

	// TESTING -----------
	this->currentWaveCount = 1;
	this->currentWaveSize = 0;
	this->swarmerCount = 5;
	// TESTING -----------

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per minion
		for (int j = 0; j < this->currentWaveSize; j++) {
			// Create an enemy and attatch it to the wave.
			EnemyObject* enemy = this->createMinion(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Per Swarmer
		for (int k = 0; k < swarmerCount; k++) {
			// Create the actual object
			EnemyObject* swarmer = this->createSwarmer();

			// Attach a pointer to waves
			currentWave->enemies.push_back(swarmer);

			// Attach a pointer to swarmspecific (used by grid)
			localSwarmers.push_back(swarmer);

			this->activeEnemiesCount++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);

		// Up the difficulty a bit maybe?
	//	this->currentWaveSize += 1;				REMOVED WHILE IMMOLATION IS NOT DONE
	}

	// Initialize the swarmers! (if there are any)
	if (this->swarmerCount > 0) {
		this->pSwarmers->initialize(localSwarmers);
	}

	// I couldn't figure out why, but the above loop creates 1 less enemy than it claims to.
	this->activeEnemiesCount--;
}

void EnemyManager::cleanLevel()
{
	// Per wave
	for (auto &currentWave : this->waves) {

		for (int i = 0; i < currentWave->enemies.size(); i++) {
			currentWave->enemies[i]->cleanUp();
			delete currentWave->enemies[i];
		}
		// Since enemies are actors which SHOULD HAVE been added to the dynamicObjectsArray,
		// they'll be cleaned and deleted from there, so we only need to delete the 'Waves' here
		delete currentWave;
	}

	int popWavesQueue = waves.size();

	for (int i = 0; i < popWavesQueue; i++) {
		this->waves.pop_back();
	}
}

EnemyObject* EnemyManager::createMinion(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior)
{
	/// D E C L A R A T I O N
	// GRAND OBJECT
	EnemyObject* enemyObject = nullptr;
	// COMPONENTS
	BlockComponent* graphicsComponent = nullptr;
	AIComponent* aiComponent = nullptr;
	InputComponent* input = nullptr;
	PhysicsComponent* physicsComponent = nullptr;
	EnemyAttackComponent* attackComponent = nullptr;
	// STATES
	EnemyAttackingState* attackState = nullptr;
	EnemyMovingState* moveState = nullptr;


	/// D E F I N I T I O N
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 pos = { 0, 0, 0 };

	int spawnLocation = Locator::getRandomGenerator()->GenerateInt(1, 4);
	float spawnOffset = Locator::getRandomGenerator()->GenerateFloat(400, 500);

	if (spawnLocation == 1)
		pos = { -spawnOffset, scale.y, static_cast<float>(ARENAHEIGHT * 0.5) };

	else if (spawnLocation == 2)
		pos = { static_cast<float>(ARENAWIDTH * 0.5), scale.y, -spawnOffset };

	else if (spawnLocation == 3)
		pos = { (static_cast<float>(ARENAWIDTH) + spawnOffset), scale.y, static_cast<float>(ARENAHEIGHT * 0.5) };

	else if (spawnLocation == 4)
		pos = { static_cast<float>(ARENAWIDTH * 0.5), scale.y, (static_cast<float>(ARENAHEIGHT) + spawnOffset) };


	float velocity = 180;
	XMFLOAT4 enemyColor(1.0f, 0.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);
	float immolationDamage = 3;
	float attackCooldown = 0.5;
	float attackRange = 70;

	// OBJECT
	enemyObject = new EnemyObject(
		ENEMYTYPE::IMMOLATION, ID, velocity, pos, velocity,
		this->pGPS, &this->players, 
		OBJECTTYPE::ENEMY
	);
	Spell* spell = new SpEnemyImmolation(
		enemyObject, this->players[0], &this->activeEnemiesCount,
		immolationDamage, attackCooldown, attackRange
	);
	enemyObject->addSpell(spell);
	
	// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, enemyColor, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, 20);
	aiComponent = new AIComponent(*enemyObject, aiBehavior);
	
	// STATES
	moveState = new EnemyMovingState(*enemyObject, *aiComponent);

	
	// Make the enemy inactive
	enemyObject->setState(OBJECTSTATE::TYPE::DEAD);
	return enemyObject;
}

EnemyObject* EnemyManager::createSwarmer()
{
	/// D E C L A R A T I O N
	// GRAND OBJECT
	EnemyObject* enemyObject;
	// COMPONENTS
	BlockComponent* graphicsComponent;
	AIComponent* aiComponent;
	InputComponent* input;
	PhysicsComponent* physicsComponent;
	EnemyAttackComponent* attackComponent;
	// STATES
	EnemyAttackingState* attackState;
	EnemyMovingState* moveState;

	/// D E F I N I T I O N
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 pos = { 0, 0, 0 };

	int spawnLocation = Locator::getRandomGenerator()->GenerateInt(1, 4);
	float spawnOffset = Locator::getRandomGenerator()->GenerateFloat(400, 500);

	if (spawnLocation == 1)
		pos = { -spawnOffset, scale.y, static_cast<float>(ARENAHEIGHT * 0.5) };

	else if (spawnLocation == 2)
		pos = { static_cast<float>(ARENAWIDTH * 0.5), scale.y, -spawnOffset };

	else if (spawnLocation == 3)
		pos = { (static_cast<float>(ARENAWIDTH) + spawnOffset), scale.y, static_cast<float>(ARENAHEIGHT * 0.5) };

	else if (spawnLocation == 4)
		pos = { static_cast<float>(ARENAWIDTH * 0.5), scale.y, (static_cast<float>(ARENAHEIGHT) + spawnOffset) };


	float velocity = 180;
	XMFLOAT4 color(0.0f, 1.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 3;
	float attackCooldown = 0.5;
	float projectileRange = 600;
	float attackRange = 500;

	/// A T T A C H M E N T
	// OBJECT
	enemyObject = new EnemyObject(
		ENEMYTYPE::SWARMER, ID, velocity, pos, velocity,
		pGPS, &this->players, 
		OBJECTTYPE::ENEMY
	);
	// SPELL (Needs to be before States)
	Spell* spell = new SpSwarmProjectile(
		enemyObject, this->players[0], &this->activeEnemiesCount, projectileRange, projectileDamage, attackRange, attackCooldown
	);
	enemyObject->addSpell(spell);	// NECESSARY


	// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, color, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, 20);
	aiComponent = new AIComponent(*enemyObject, AIBEHAVIOR::KEY::TEMPLATE0);
//	attackComponent = new SwarmerEnemyAttack(*enemyObject, this->activeEnemiesCount, projectileDamage, attackCooldown, projectileRange);
	// STATES
//	attackState = new EnemyAttackingState(*enemyObject, *aiComponent, *attackComponent);
	moveState = new EnemyMovingState(*enemyObject, *aiComponent);

	// Make the enemy inactive
	enemyObject->setState(OBJECTSTATE::TYPE::DEAD);
	return enemyObject;
}

void EnemyManager::initialize(GamePlayState& pGPS, std::vector<ActorObject*> players)
{
	this->pGPS = &pGPS;
	this->players = players;
	this->activeEnemiesCount = 0;
	this->pSwarmers = new ArrayList();
	
	// --------- NEW TEST ---------
	//std::vector<EnemyObject*> tempVec;
	//tempVec.push_back(this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS));
	//tempVec.push_back(this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS));
	//tempVec.push_back(this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS));
	//tempVec.push_back(this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS));
	//tempVec.push_back(this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS));
	//this->pSwarmers->initialize(tempVec);

	//this->pSwarmers->find(3);
	//this->pSwarmers->remove(3);
	//this->pSwarmers->find(3);
}

void EnemyManager::update()
{
	// If there are any waves left on the current level
	if (this->waves.size() > 0) {

		// If the currentwave has any enemies left
		if (this->waves.front()->enemies.size() > 0) {

			// Update timePassed
			this->timePassed += Locator::getGameTime()->getDeltaTime();

			// If the spawnInterval is met
			if (this->timePassed > spawnInterval) {

				// Reset the timer
				this->timePassed = 0;

				// Grab the next enemy in line
				EnemyObject* freshEnemy = this->waves.front()->enemies.front();

				// Was bobby a swarmer?
				if (freshEnemy->getEnemyType() == ENEMYTYPE::SWARMER) {
					this->pSwarmers->activateNext(); // If so then activate him!
				}

				// Remove his homelink
				this->waves.front()->enemies.pop_front();
				// Send him out into the real world and let him handle himself (gl hf bobby!)
				freshEnemy->setState(OBJECTSTATE::TYPE::ACTIVATED);
				(*this->pGPS->getDynamicObjects()).push_back(freshEnemy);

				char msgbuf[20];
				sprintf_s(msgbuf, "SPAWNED\n");
				OutputDebugStringA(msgbuf);
			}
		}
		// No enemies in this wave? Move on to the next wave
		else if (this->timePassed > this->waveInterval) {
			this->timePassed = 0;

			// Goodbye wave!
			delete this->waves.front();
			this->waves.pop_front();
		}

		else {
			this->timePassed += Locator::getGameTime()->getDeltaTime();
		}
	}
	else { // All waves have been spawned!
		
		// Has the player won? :O
		if (this->activeEnemiesCount < 1) {
			//StateManager::pushState(this->endState);
			int asdf1 = 3;
		}
	}

	// Update the swarmer collective!
	this->pSwarmers->update();
}

void EnemyManager::cleanUp()
{
	this->cleanLevel();
	this->pSwarmers->cleanUp();
	delete this->pSwarmers;
}