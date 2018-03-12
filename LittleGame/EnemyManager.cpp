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
#include "SwarmerEnemyAttack.h"
#include "SwarmerSeekingState.h"
#include "SwarmerOutsideState.h"
#include "SpSwarmProjectile.h"
#include "SpEnemyImmolation.h"
#include "Grid.h"
#include "RewardMenuState.h"
//BOSS STATES
#include "BossMoveToArenaState.h"

// BOSS ATTACKS
#include "SpBossBulletHell.h"

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
	bool ramp = false;
	bool pulse = false;
}

void EnemyManager::startStandardLevel(enemySpawnPositions spawnPosVectors, float difficulty)
{
	// Initiate variables
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.20f;
	this->waveInterval = (5.1f - (difficulty * 0.5f));
	if (this->waveInterval < 0.0f)
		this->waveInterval = 0.0f;

	std::vector<EnemyObject*> localSwarmers;

	this->currentWaveCount = 10;

	// Deciding on how individual enemy counts will be calculated
	this->minionCount = (2 + static_cast<int>(difficulty));
	this->swarmerCount = (1 + static_cast<int>(difficulty));

	// Define specific MINION count PER WAVE
	this->currentWaveMinionCount.resize(this->currentWaveCount);
	for (int i = 0; i < this->currentWaveMinionCount.size(); i++)
		this->currentWaveMinionCount.at(i) = (this->minionCount * i);
	// Define specific SWARMER count PER WAVE
	this->currentWaveSwarmerCount.resize(this->currentWaveCount);
	for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
		this->currentWaveSwarmerCount.at(i) = (this->swarmerCount + i);

	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per Minion
		for (int j = 0; j < this->currentWaveMinionCount.at(i); j++) {
			// Create an enemy and attatch it to the wave.
			EnemyObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS, spawnPosVectors);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Per Swarmer
		for (int k = 0; k < this->currentWaveSwarmerCount.at(i); k++) {
			// Create the actual object
			EnemyObject* swarmer = this->createSwarmer(spawnPosVectors);
			// Attach a pointer to waves
			currentWave->enemies.push_back(swarmer);
			// Attach a pointer to swarmspecific (used by grid)
			localSwarmers.push_back(swarmer);

			this->activeEnemiesCount++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);
	}

	// Initialize the swarmers! (if there are any)
	if (this->currentWaveSwarmerCount.at(this->currentWaveCount - 1) > 0) {
		this->pSwarmers->initialize(localSwarmers);
	}
}

void EnemyManager::startRampLevel(enemySpawnPositions spawnPosVectors, float difficulty)
{
	this->ramp = true;

	// Initiate variables
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 1.1f;
	this->waveInterval = 10.1f;

	std::vector<EnemyObject*> localSwarmers;

	this->currentWaveCount = 10;

	// Deciding on how individual enemy counts will be calculated
	this->minionCount = (4 + static_cast<int>(difficulty));
	this->swarmerCount = (1 + static_cast<int>(difficulty));

	// Define specific MINION count PER WAVE
	this->currentWaveMinionCount.resize(this->currentWaveCount);
	for (int i = 0; i < this->currentWaveMinionCount.size(); i++)
		this->currentWaveMinionCount.at(i) = (this->minionCount * i);
	// Define specific SWARMER count PER WAVE
	this->currentWaveSwarmerCount.resize(this->currentWaveCount);
	for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
		this->currentWaveSwarmerCount.at(i) = (this->swarmerCount + i);

	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per Minion
		for (int j = 0; j < this->currentWaveMinionCount.at(i); j++) {
			// Create an enemy and attatch it to the wave.
			EnemyObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS, spawnPosVectors);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Per Swarmer
		for (int k = 0; k < this->currentWaveSwarmerCount.at(i); k++) {
			// Create the actual object
			EnemyObject* swarmer = this->createSwarmer(spawnPosVectors);
			// Attach a pointer to waves
			currentWave->enemies.push_back(swarmer);
			// Attach a pointer to swarmspecific (used by grid)
			localSwarmers.push_back(swarmer);

			this->activeEnemiesCount++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);
	}

	// Initialize the swarmers! (if there are any)
	if (this->currentWaveSwarmerCount.at(this->currentWaveCount - 1) > 0) {
		this->pSwarmers->initialize(localSwarmers);
	}
}

void EnemyManager::startPulseLevel(enemySpawnPositions spawnPosVectors, float difficulty)
{
	this->ramp = true;

	// Initiate variables
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.0f;
	this->waveInterval = 8.0f;

	std::vector<EnemyObject*> localSwarmers;

	this->currentWaveCount = 10;

	// Deciding on how individual enemy counts will be calculated
	this->minionCount = (2 + static_cast<int>(difficulty));
	this->swarmerCount = (1 + static_cast<int>(difficulty));

	// Define specific MINION count PER WAVE
	this->currentWaveMinionCount.resize(this->currentWaveCount);
	for (int i = 0; i < this->currentWaveMinionCount.size(); i++)
		this->currentWaveMinionCount.at(i) = (this->minionCount + i);
	// Define specific SWARMER count PER WAVE
	this->currentWaveSwarmerCount.resize(this->currentWaveCount);
	for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
		this->currentWaveSwarmerCount.at(i) = (this->swarmerCount + i);

	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per Minion
		for (int j = 0; j < this->currentWaveMinionCount.at(i); j++) {
			// Create an enemy and attatch it to the wave.
			EnemyObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS, spawnPosVectors);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Per Swarmer
		for (int k = 0; k < this->currentWaveSwarmerCount.at(i); k++) {
			// Create the actual object
			EnemyObject* swarmer = this->createSwarmer(spawnPosVectors);
			// Attach a pointer to waves
			currentWave->enemies.push_back(swarmer);
			// Attach a pointer to swarmspecific (used by grid)
			localSwarmers.push_back(swarmer);

			this->activeEnemiesCount++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);
	}

	// Initialize the swarmers! (if there are any)
	if (this->currentWaveSwarmerCount.at(this->currentWaveCount - 1) > 0) {
		this->pSwarmers->initialize(localSwarmers);
	}
}

void EnemyManager::startBossLevel()
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 1;
	this->waveInterval = 0.1;
	this->currentWaveCount = 1;
	//this->currentWaveSize = 1;
	Wave* currentWave;

	currentWave = new Wave();
	EnemyObject* boss = this->createBoss(ENEMYTYPE::BOSS, AIBEHAVIOR::STRAIGHTTOWARDS);
	currentWave->enemies.push_back(boss);
	this->activeEnemiesCount++;
	this->waves.push_back(currentWave);
}

void EnemyManager::cleanLevel()
{
	// Per wave
	for (auto &currentWave : this->waves) {

		for (size_t i = 0; i < currentWave->enemies.size(); i++) {
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

EnemyObject* EnemyManager::createEnemy(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior, enemySpawnPositions spawnPosVectors)
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
	EnemyMovingState* moveState = nullptr;

	bool reGenerateRandom = true;
	int spawnLocation = 0;


	/// D E F I N I T I O N
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 pos = { 0, 0, 0.0001f };
	float spawnOffset = 0.0f;

	if (this->pulse) {
		spawnOffset = 700.0f;
	}

	else {
		spawnOffset = Locator::getRandomGenerator()->GenerateFloat(700.0f, 800.0f);
	}

	while (reGenerateRandom)
	{
		spawnLocation = Locator::getRandomGenerator()->GenerateInt(1, 4);

		switch (spawnLocation) {
		case 1:
		{
			if (spawnPosVectors.west.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.west.size() - 1));
				pos = {
					(spawnPosVectors.west.at(spawnLocation).x - spawnOffset),
					scale.y,
					spawnPosVectors.west.at(spawnLocation).y
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 2:
		{
			if (spawnPosVectors.south.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.south.size() - 1));
				pos = {
					spawnPosVectors.south.at(spawnLocation).x,
					scale.y,
					(spawnPosVectors.south.at(spawnLocation).y - spawnOffset)
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 3:
		{
			if (spawnPosVectors.east.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.east.size() - 1));
				pos = {
					(spawnPosVectors.east.at(spawnLocation).x + spawnOffset),
					scale.y,
					spawnPosVectors.east.at(spawnLocation).y
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 4:
		{
			if (spawnPosVectors.north.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.north.size() - 1));
				pos = {
					spawnPosVectors.north.at(spawnLocation).x,
					scale.y,
					(spawnPosVectors.north.at(spawnLocation).y + spawnOffset)
				};
				reGenerateRandom = false;
			}
			break;
		}
		break;
		}
	}

	float velocityMagnitude = 50.0f;
	float topSpeed = 11.0f;
	XMFLOAT4 enemyColor(1.0f, 0.0f, 0.0f, 0.3f);
	XMFLOAT3 rotation(0.0f, 0.0f, 0.0f);
	float immolationDamage = 3.0f;
	float attackCooldown = 0.3f;
	float attackRange = 50.0f;
	
	// OBJECT
	enemyObject = new EnemyObject(
		ID, velocityMagnitude, topSpeed, pos, 
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

EnemyObject* EnemyManager::createSwarmer(enemySpawnPositions spawnPosVectors)
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
	EnemyState* moveState = nullptr;

	/// D E F I N I T I O N
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 pos = { 0, 0, 0.0001f };

	bool reGenerateRandom = true;
	int spawnLocation = 0;
	float spawnOffset = Locator::getRandomGenerator()->GenerateFloat(550, 650);

	while (reGenerateRandom)
	{
		spawnLocation = Locator::getRandomGenerator()->GenerateInt(1, 4);

		switch (spawnLocation) {
		case 1:
		{
			if (spawnPosVectors.west.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.west.size() - 1));
				pos = {
					(spawnPosVectors.west.at(spawnLocation).x - spawnOffset),
					scale.y,
					spawnPosVectors.west.at(spawnLocation).y
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 2:
		{
			if (spawnPosVectors.south.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.south.size() - 1));
				pos = {
					spawnPosVectors.south.at(spawnLocation).x,
					scale.y,
					(spawnPosVectors.south.at(spawnLocation).y - spawnOffset)
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 3:
		{
			if (spawnPosVectors.east.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.east.size() - 1));
				pos = {
					(spawnPosVectors.east.at(spawnLocation).x + spawnOffset),
					scale.y,
					spawnPosVectors.east.at(spawnLocation).y
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 4:
		{
			if (spawnPosVectors.north.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.north.size() - 1));
				pos = {
					spawnPosVectors.north.at(spawnLocation).x,
					scale.y,
					(spawnPosVectors.north.at(spawnLocation).y + spawnOffset)
				};
				reGenerateRandom = false;
			}
			break;
		}
		break;
		}
	}


	XMFLOAT4 color(0.0f, 1.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 8.0f;
	float attackCooldown = 0.5f;
	float projectileRange = 2000.0f;
	float attackRange = 500.0f;

	float velocityMagnitude = 180.0f;
	float topSpeed = 11.0f;

	// OBJECT
	enemyObject = new EnemyObject(
		ID, velocityMagnitude, topSpeed, pos,
		this->pGPS, &this->players,
		OBJECTTYPE::ENEMY
	);
	// SPELL (Needs to be before States)
	Spell* spell = new SpSwarmProjectile(
		enemyObject, this->players[0], &this->activeEnemiesCount, projectileRange, projectileDamage, attackRange, attackCooldown
	);
	enemyObject->addSpell(spell);	// HAS to be out here because of how spells are structured


	// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, color, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, 20);
	aiComponent = new AIComponent(*enemyObject, AIBEHAVIOR::KEY::TEMPLATE0);
	// STATES
	moveState = new SwarmerOutsideState(*enemyObject, *aiComponent, this->pGrid, this->swarmerIDs++);

	// Make the enemy inactive
	enemyObject->setState(OBJECTSTATE::TYPE::DEAD);
	return enemyObject;
}

EnemyObject* EnemyManager::createBoss(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior)
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
	EnemyState* bossMoveToArenaState = nullptr;

	/// D E F I N I T I O N
	size_t ID = this->pGPS->newID();
	float bossScale = 150.0f;
	XMFLOAT3 scale(bossScale, bossScale, bossScale);
	XMFLOAT3 pos = { ARENADATA::GETarenaWidth() + 700.0f, bossScale, ARENADATA::GETarenaHeight() * 0.5f };


	XMFLOAT4 color(0.0f, 1.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 8.0f;
	float attackCooldown = 0.5f;
	float projectileRange = 2000.0f;
	float attackRange = 500.0f;

	float velocityMagnitude = 180.0f;
	float topSpeed = 11.0f;

	// OBJECT
	enemyObject = new EnemyObject(
		ID, velocityMagnitude, topSpeed, pos,
		this->pGPS, &this->players,
		OBJECTTYPE::ENEMY
	);
	// SPELL (Needs to be before States)
	Spell* spell = new SpBossBulletHell(
		enemyObject, this->players[0], &this->activeEnemiesCount, projectileRange, projectileDamage, attackRange, attackCooldown
	);
	enemyObject->addSpell(spell);	// HAS to be out here because of how spells are structured


									// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, color, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, bossScale * 1.25f);
	aiComponent = new AIComponent(*enemyObject, AIBEHAVIOR::KEY::STRAIGHTTOWARDS);
	// STATE
	bossMoveToArenaState = new BossMoveToArenaState(*enemyObject, *aiComponent, *this->pGPS, bossScale);

	return enemyObject;

}

void EnemyManager::initialize(GamePlayState& pGPS, std::vector<ActorObject*> players)
{
	// Reinstansiate values incase we've restarted once
	this->swarmerIDs = 0;

	this->pGPS = &pGPS;
	this->players = players;
	this->activeEnemiesCount = 0;
	this->pSwarmers = new ArrayList();
	this->pGrid = new Grid(this->pSwarmers);

	this->ramp = false;
	this->pulse = false;
}

void EnemyManager::update(GUIManager* GUI)
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

				// Remove his homelink
				this->waves.front()->enemies.pop_front();
				// Send him out into the real world and let him handle himself (gl hf bobby!)
				freshEnemy->setState(OBJECTSTATE::TYPE::ACTIVATED);
				(*this->pGPS->getDynamicObjects()).push_back(freshEnemy);

				GUI->pushEnemyElement(*this->pGPS->GETGUIObjects(), *this->pGPS->getGraphicsComponents(), this->pGPS->newID());

				//char msgbuf[20];
				//sprintf_s(msgbuf, "SPAWNED\n");
				//OutputDebugStringA(msgbuf);
			}
		}
		// No enemies in this wave? Move on to the next wave
		else if (this->timePassed > this->waveInterval) {
			this->timePassed = 0;

			// Ramping the time between waves
			if (this->ramp)
			{
				this->waveInterval -= 1.0f;

				if (this->waveInterval < 0.0f)
					this->waveInterval = 0.0f;

				this->spawnInterval -= 0.1f;

				if (this->spawnInterval < 0.0f)
					this->spawnInterval = 0.0f;
			}

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
			Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::PLAYERWON);
		}
	}

	// Update the swarmer collective!
	this->pSwarmers->update();
	this->pGrid->update();
}

void EnemyManager::cleanUp()
{
	this->cleanLevel();

	// Grid
	this->pGrid->cleanUp();
	delete this->pGrid;
	this->pGrid = nullptr;
	
	// ArrayList
	this->pSwarmers->cleanUp();
	delete this->pSwarmers;
	this->pSwarmers = nullptr;
	

	
}