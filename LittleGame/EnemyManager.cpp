#include "EnemyManager.h"
#include "ActorObject.h"
#include "EnemyObject.h"
#include "GamePlayState.h"
#include "Locator.h"
#include "PhysicsComponent.h"
#include "BlockComponent.h"
#include "TriangleComponent.h"
#include "AIComponent.h"
#include "EnemyAttackComponent.h"
#include "EnemyAttackingState.h"
#include "EnemyMovingState.h"
#include "StateManager.h"
#include "SwarmerEnemyAttack.h"
#include "SwarmerSeekingState.h"
#include "SwarmerOutsideState.h"
#include "ChargerOutsideState.h"
#include "MinionOutsideState.h"
#include "SpSwarmProjectile.h"
#include "SpNo.h"
#include "SpEnemyImmolation.h"
#include "Grid.h"
#include "MenuRewardState.h"
//BOSS STATES
#include "BossMoveToArenaState.h"
#include "ChargerChannelingState.h"

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

void EnemyManager::startStandardLevel(enemySpawnPositions spawnPosVectors, float difficulty, GUIManager* GUI)
{
	// Initiate variables
	this->startTime = Locator::getGameTime()->GetTime();
	int currentLevelNumber = Locator::getStatsHeader()->getStats().level;
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = (0.35f - (0.01f * currentLevelNumber));
	this->waveInterval = (10.1f - (0.3f * currentLevelNumber));
	if (this->waveInterval < 0.0f)
		this->waveInterval = 0.0f;

	std::vector<EnemyObject*> localSwarmers;
	this->currentWaveCount = (1 + currentLevelNumber);

	int amountModifier = Locator::getStatsHeader()->getStats().enemyUpg[2];

	// MINIONS
	this->minionCount = static_cast<int>((2 + currentLevelNumber) + (amountModifier * 2));
	this->currentWaveMinionCount.resize(this->currentWaveCount);

	for (int i = 0; i < this->currentWaveMinionCount.size(); i++)
		this->currentWaveMinionCount.at(i) = (this->minionCount + (i * currentLevelNumber));

	// SWARMERS
	if (currentLevelNumber >= 2)
		this->swarmerCount = static_cast<int>((1 + currentLevelNumber) + amountModifier);
	else
		this->swarmerCount = 0;

	this->currentWaveSwarmerCount.resize(this->currentWaveCount);

	if (currentLevelNumber >= 2)
	{
		for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
			this->currentWaveSwarmerCount.at(i) = static_cast<int>((this->swarmerCount + (i * 0.2)));
	}

	else
	{
		for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
			this->currentWaveSwarmerCount.at(i) = 0;
	}

	// CHARGERS
	if (currentLevelNumber >= 3)
		this->chargerCount = static_cast<int>((2 + currentLevelNumber) + amountModifier);
	else
		this->chargerCount = 0;

	this->currentWaveChargerCount.resize(this->currentWaveCount);

	if (currentLevelNumber >= 3)
	{
		for (int i = 0; i < this->currentWaveChargerCount.size(); i++)
			this->currentWaveChargerCount.at(i) = static_cast<int>((this->chargerCount + (i * 0.2)));
	}

	else
	{
		for (int i = 0; i < this->currentWaveChargerCount.size(); i++)
			this->currentWaveChargerCount.at(i) = 0;
	}
	

	Wave* currentWave = nullptr;


	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		GUI->pushWaveElement(*this->pGPS->GETGUIObjects(), *this->pGPS->getGraphicsComponents(), this->pGPS->newID());
		currentWave = new Wave();

		// Per Minion
		for (int j = 0; j < this->currentWaveMinionCount.at(i); j++) {
			// Create an enemy and attach it to the wave.
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

		// Per Charger
		for (int l = 0; l < this->currentWaveChargerCount.at(i); l++) {
			// Create the actual object
			EnemyObject* charger = this->createCharger(spawnPosVectors);
			// Attach a pointer to waves
			currentWave->enemies.push_back(charger);

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

void EnemyManager::startRampLevel(enemySpawnPositions spawnPosVectors, float difficulty, GUIManager* GUI)
{
	this->ramp = true;

	// Initiate variables
	this->startTime = Locator::getGameTime()->GetTime();
	int currentLevelNumber = Locator::getStatsHeader()->getStats().level;
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.7f;
	this->waveInterval = 7.1f;

	std::vector<EnemyObject*> localSwarmers;
	this->currentWaveCount = 6;

	int amountModifier = Locator::getStatsHeader()->getStats().enemyUpg[2];

	// MINIONS
	this->minionCount = static_cast<int>((1 + currentLevelNumber) + (amountModifier * 2));
	this->currentWaveMinionCount.resize(this->currentWaveCount);

	for (int i = 0; i < this->currentWaveMinionCount.size(); i++)
		this->currentWaveMinionCount.at(i) = (this->minionCount + (i * currentLevelNumber));

	// SWARMERS
	if (currentLevelNumber >= 2)
		this->swarmerCount = static_cast<int>((1 + currentLevelNumber) + amountModifier);
	else
		this->swarmerCount = 0;

	this->currentWaveSwarmerCount.resize(this->currentWaveCount);

	if (currentLevelNumber >= 2)
	{
		for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
			this->currentWaveSwarmerCount.at(i) = static_cast<int>((this->swarmerCount + (i * 0.2)));
	}

	else
	{
		for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
			this->currentWaveSwarmerCount.at(i) = 0;
	}

	// CHARGERS
	if (currentLevelNumber >= 3)
		this->chargerCount = static_cast<int>((1 + currentLevelNumber) + amountModifier);
	else
		this->chargerCount = 0;

	this->currentWaveChargerCount.resize(this->currentWaveCount);

	if (currentLevelNumber >= 3)
	{
		for (int i = 0; i < this->currentWaveChargerCount.size(); i++)
			this->currentWaveChargerCount.at(i) = static_cast<int>((this->chargerCount + (i * 0.2)));
	}

	else
	{
		for (int i = 0; i < this->currentWaveChargerCount.size(); i++)
			this->currentWaveChargerCount.at(i) = 0;
	}


	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		GUI->pushWaveElement(*this->pGPS->GETGUIObjects(), *this->pGPS->getGraphicsComponents(), this->pGPS->newID());
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

		// Per Charger
		for (int l = 0; l < this->currentWaveChargerCount.at(i); l++) {
			// Create the actual object
			EnemyObject* charger = this->createCharger(spawnPosVectors);
			// Attach a pointer to waves
			currentWave->enemies.push_back(charger);

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

void EnemyManager::startPulseLevel(enemySpawnPositions spawnPosVectors, float difficulty, GUIManager* GUI)
{
	this->ramp = true;

	// Initiate variables
	this->startTime = Locator::getGameTime()->GetTime();
	int currentLevelNumber = Locator::getStatsHeader()->getStats().level;
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.0f;
	this->waveInterval = 8.0f;

	std::vector<EnemyObject*> localSwarmers;

	this->currentWaveCount = (1 + currentLevelNumber);

	int amountModifier = Locator::getStatsHeader()->getStats().enemyUpg[2];

	// MINIONS
	this->minionCount = static_cast<int>((1 + currentLevelNumber) + (amountModifier * 2));
	this->currentWaveMinionCount.resize(this->currentWaveCount);

	for (int i = 0; i < this->currentWaveMinionCount.size(); i++)
		this->currentWaveMinionCount.at(i) = (this->minionCount + (i * currentLevelNumber));

	// SWARMERS
	if (currentLevelNumber >= 2)
		this->swarmerCount = static_cast<int>((1 + currentLevelNumber) + amountModifier);
	else
		this->swarmerCount = 0;

	this->currentWaveSwarmerCount.resize(this->currentWaveCount);

	if (currentLevelNumber >= 2)
	{
		for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
			this->currentWaveSwarmerCount.at(i) = static_cast<int>((this->swarmerCount + (i * 0.2)));
	}

	else
	{
		for (int i = 0; i < this->currentWaveSwarmerCount.size(); i++)
			this->currentWaveSwarmerCount.at(i) = 0;
	}

	// CHARGERS
	if (currentLevelNumber >= 3)
		this->chargerCount = static_cast<int>((1 + currentLevelNumber) + amountModifier);
	else
		this->chargerCount = 0;

	this->currentWaveChargerCount.resize(this->currentWaveCount);

	if (currentLevelNumber >= 3)
	{
		for (int i = 0; i < this->currentWaveChargerCount.size(); i++)
			this->currentWaveChargerCount.at(i) = static_cast<int>((this->chargerCount + (i * 0.2)));
	}

	else
	{
		for (int i = 0; i < this->currentWaveChargerCount.size(); i++)
			this->currentWaveChargerCount.at(i) = 0;
	}

	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		GUI->pushWaveElement(*this->pGPS->GETGUIObjects(), *this->pGPS->getGraphicsComponents(), this->pGPS->newID());
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
	this->spawnInterval = 0.5f;
	this->waveInterval = 0.1f;
	this->currentWaveCount = 1;
	Wave* currentWave;

	currentWave = new Wave();
	EnemyObject* boss = this->createBoss(ENEMYTYPE::BOSS, AIBEHAVIOR::STRAIGHTTOWARDS);
	currentWave->enemies.push_back(boss);
	this->activeEnemiesCount++;
	this->waves.push_back(currentWave);
}

void EnemyManager::createBossWave(enemySpawnPositions spawnPosVectors)
{
	Wave* currentWave;
	this->swarmerCount = 5;

	std::vector<EnemyObject*> localSwarmers;
	int currentWaveSize = 20.0f;

	// Adapt for reoccuring waves
	this->swarmerIDs = 0;
	ArrayList* newArrayList = new ArrayList();
	Grid* newGrid = new Grid(newArrayList);
	this->BossSwarmers.push_back(newArrayList);
	this->BossGrids.push_back(newGrid);

	char msgbuf[40];
	sprintf_s(msgbuf, "CREATED NEW BOSS WAVE.\n");
	OutputDebugStringA(msgbuf);

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per minion
		for (int j = 0; j < currentWaveSize; j++) {
			// Create an enemy and attatch it to the wave.
			EnemyObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS, spawnPosVectors);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Per Swarmer
		for (int k = 0; k < swarmerCount; k++) {
			// Create the actual object
			EnemyObject* swarmer = this->createBossSwarmer(spawnPosVectors);

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
		this->BossSwarmers.back()->initialize(localSwarmers);
	}

	// I couldn't figure out why, but the above loop creates 1 less enemy than it claims to.
	//	this->activeEnemiesCount--;
}

void EnemyManager::createBossChargers(std::vector<GameObject*>& bossChargers, std::list<GameObject*>& dynamicObjects, float hp)
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
	EnemyState* bossState = nullptr;

	/// D E F I N I T I O N
	float bossScale = 50.0f;
	XMFLOAT3 scale(bossScale, bossScale, bossScale);
	XMFLOAT3 pos[4];
	pos[0] = { 300.0f, -bossScale, ARENADATA::GETarenaHeight() - 300.0f };
	pos[1] = { 300.0f, -bossScale, 300.0f };
	pos[2] = { ARENADATA::GETarenaWidth() - 300.0f, -bossScale, ARENADATA::GETarenaHeight() - 300.0f };
	pos[3] = { ARENADATA::GETarenaWidth() - 300.0f, -bossScale, 300.0f };

	float velocity = 180;
	XMFLOAT4 color(0.1f, 0.01f, 0.75f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 8;
	float attackCooldown = 5.0;
	float projectileRange = ARENADATA::GETarenaWidth() - 200.0f;
	float attackRange = ARENADATA::GETarenaWidth();
	float health = hp / 3.0f;
	float topSpeed = 12.0f;
	float velocityMagnitude = 60.0f;

	Spell* spell = nullptr;
	

	for (int i = 0; i < 4; i++) {
		/// A T T A C H M E N T
		// OBJECT
		enemyObject = new EnemyObject(
			this->pGPS->newID(), velocityMagnitude, topSpeed, pos[i],
			pGPS, &this->players,
			OBJECTTYPE::BOSS, health
		);
		// SPELL (Needs to be before States)
		spell = new SpBossBulletHell(
			enemyObject, this->players[0], &this->activeEnemiesCount, projectileRange, projectileDamage, attackRange, attackCooldown
		);
		enemyObject->addSpell(spell);	// HAS to be out here because of how spells are structured
		// COMPONENTS
		graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, color, scale, rotation);
		physicsComponent = new PhysicsComponent(*enemyObject, bossScale * 1.25f);
		aiComponent = new AIComponent(*enemyObject);
		// STATE
		// STATES
		bossState = new ChargerChannelingState(*enemyObject, *aiComponent, 3.0f, 40.0f);
	//	bossMoveToArenaState = new BossMoveToArenaState(*enemyObject, *aiComponent, *this->pGPS, bossScale);
		enemyObject->setState(OBJECTSTATE::TYPE::BOSSEMERGE);
		enemyObject->turnOnInvulnerability();
		bossChargers.push_back(enemyObject);
		dynamicObjects.push_back(enemyObject);

		this->activeEnemiesCount++;
	}

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

EnemyObject* EnemyManager::createMinion(enemySpawnPositions spawnPosVectors)
{
	/// D E C L A R A T I O N
	// GRAND OBJECT
	EnemyObject* enemyObject = nullptr;
	// COMPONENTS
	GraphicsComponent* graphicsComponent = nullptr;
	AIComponent* aiComponent = nullptr;
	InputComponent* input = nullptr;
	PhysicsComponent* physicsComponent = nullptr;
	EnemyAttackComponent* attackComponent = nullptr;
	// STATES
	EnemyState* moveState = nullptr;

	/// D E F I N I T I O N
	std::vector<XMFLOAT3> generatedPositions;
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 spawnPos = { 0.0f, 0.0f, 0.0001f };
	XMFLOAT3 openingPos = { 0.0f, 0.0f, 0.0001f };


	generatedPositions = this->generateEnemySpawnPositions(spawnPosVectors, scale);
	spawnPos = generatedPositions[0];
	openingPos = generatedPositions[1];
	float damageModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[0] * 0.25f);
	float healthModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[1] * 0.25f);
	float speedModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[3] * 0.25f);

	XMFLOAT4 enemyColor(1.0f, 0.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float velocityMagnitude = 140.0f * speedModifier;
	float immolationDamage = 1.5f * damageModifier;
	float attackCooldown = 0.5;
	float attackRange = 70;
	float hp = 100.0f * healthModifier;
	float topSpeed = 8.0f * speedModifier;

	// OBJECT
	enemyObject = new EnemyObject(
		ID, velocityMagnitude, topSpeed, spawnPos,
		this->pGPS, &this->players, 
		OBJECTTYPE::ENEMY, hp
	);
	Spell* spell = new SpEnemyImmolation(
		enemyObject, this->players[0], &this->activeEnemiesCount,
		immolationDamage, attackCooldown, attackRange
	);
	enemyObject->addSpell(spell);
	
	// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, enemyColor, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, 20);
	aiComponent = new AIComponent(*enemyObject);
	
	// STATES
	moveState = new MinionOutsideState(*enemyObject, *aiComponent, openingPos);

	
	// Make the enemy inactive
	enemyObject->setState(OBJECTSTATE::TYPE::DEAD);
	return enemyObject;
}

EnemyObject * EnemyManager::createCharger(enemySpawnPositions spawnPosVectors)
{
	/// D E C L A R A T I O N
	// GRAND OBJECT
	EnemyObject* enemyObject = nullptr;
	// COMPONENTS
	GraphicsComponent* graphicsComponent = nullptr;
	AIComponent* aiComponent = nullptr;
	InputComponent* input = nullptr;
	PhysicsComponent* physicsComponent = nullptr;
	EnemyAttackComponent* attackComponent = nullptr;
	// STATES
	EnemyState* moveState = nullptr;

	/// D E F I N I T I O N
	std::vector<XMFLOAT3> generatedPositions;
	size_t ID_ = this->pGPS->newID();
	XMFLOAT3 scale(15.0f, 2.50f, 15.0f);
	XMFLOAT3 spawnPos = { 0.0f, 0.0f, 0.0001f };
	XMFLOAT3 openingPos = { 0.0f, 0.0f, 0.01f };

	generatedPositions = this->generateEnemySpawnPositions(spawnPosVectors, scale);
	spawnPos = generatedPositions[0];
	openingPos = generatedPositions[1];
	float damageModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[0] * 0.25f);
	float healthModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[1] * 0.25f);
	float speedModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[3] * 0.25f);

	XMFLOAT4 color(0.0f, 1.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float velocity = 100.0f * speedModifier;
	float topSpeed = 14.0f * speedModifier;
	float projectileDamage = 4.0f * damageModifier;
	float attackCooldown = 0.5f;
	float projectileRange = 200.0f;
	float attackRange = 500.0f;
	float hp = 200.0f * healthModifier;

	/// A T T A C H M E N T
	// OBJECT
	enemyObject = new EnemyObject(
		ID_, velocity, topSpeed, spawnPos,
		pGPS, &this->players,
		OBJECTTYPE::ENEMY, hp
	);
	Spell* NoSpell = new SpNo(enemyObject, &this->activeEnemiesCount, NAME::NOSPELL);
	enemyObject->addSpell(NoSpell);

	// COMPONENTS
	graphicsComponent = new TriangleComponent(*this->pGPS, *enemyObject, color, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, 20);
	aiComponent = new AIComponent(*enemyObject);
	// STATES
	float chargeUpTime = 5.0f;
	float maxSpinSpeed = 60.0f;
	float collisionDamage = 10.0f;
	moveState = new ChargerOutsideState(*enemyObject, *aiComponent, openingPos, chargeUpTime, maxSpinSpeed, collisionDamage);

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
	GraphicsComponent* graphicsComponent = nullptr;
	AIComponent* aiComponent = nullptr;
	InputComponent* input = nullptr;
	PhysicsComponent* physicsComponent = nullptr;
	EnemyAttackComponent* attackComponent = nullptr;
	// STATES
	EnemyState* moveState = nullptr;

	/// D E F I N I T I O N
	std::vector<XMFLOAT3> generatedPositions;
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 spawnPos = { 0.0f, 0.0f, 0.0001f };
	XMFLOAT3 openingPos = { 0.0f, 0.0f, 0.01f };

	generatedPositions = this->generateEnemySpawnPositions(spawnPosVectors, scale);
	spawnPos = generatedPositions[0];
	openingPos = generatedPositions[1];
	float damageModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[0] * 0.25f);
	float healthModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[1] * 0.25f);
	float speedModifier = 1.0f + (Locator::getStatsHeader()->getStats().enemyUpg[3] * 0.25f);

	XMFLOAT4 color(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 4.0f * damageModifier;
	float attackCooldown = 0.5f;
	float projectileRange = 700.0f;
	float attackRange = -1.0f;
	float hp = 200.0f * healthModifier;

	float velocityMagnitude = 500.0f * speedModifier;
	float topSpeed = 14.0f * speedModifier;

	// OBJECT
	enemyObject = new EnemyObject(
		ID, velocityMagnitude, topSpeed, spawnPos,
		this->pGPS, &this->players,
		OBJECTTYPE::ENEMY, hp
	);
	// SPELL (Needs to be before States)
	Spell* spell = new SpSwarmProjectile(
		enemyObject, this->players[0], &this->activeEnemiesCount, projectileRange, projectileDamage, attackRange, attackCooldown
	);
	enemyObject->addSpell(spell);	// HAS to be out here because of how spells are structured


	// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, color, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, 20);
	aiComponent = new AIComponent(*enemyObject);
	// STATES
	moveState = new SwarmerOutsideState(*enemyObject, *aiComponent, this->pGrid, this->swarmerIDs++, openingPos);


	// Make the enemy inactive
	enemyObject->setState(OBJECTSTATE::TYPE::DEAD);
	return enemyObject;
}

EnemyObject* EnemyManager::createBossSwarmer(enemySpawnPositions spawnPosVectors)
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
	std::vector<XMFLOAT3> generatedPositions;
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 spawnPos = { 0.0f, 0.0f, 0.0001f };
	XMFLOAT3 openingPos = { 0.0f, 0.0f, 0.01f };

	generatedPositions = this->generateEnemySpawnPositions(spawnPosVectors, scale);
	spawnPos = generatedPositions[0];
	openingPos = generatedPositions[1];

	XMFLOAT4 color(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 8.0f;
	float attackCooldown = 0.5f;
	float projectileRange = 200.0f;
	float attackRange = 500.0f;
	float hp = 200.0f;

	float velocityMagnitude = 180.0f;
	float topSpeed = 11.0f;

	// OBJECT
	enemyObject = new EnemyObject(
		ID, velocityMagnitude, topSpeed, spawnPos,
		this->pGPS, &this->players,
		OBJECTTYPE::ENEMY, hp
	);
	// SPELL (Needs to be before States)
	Spell* spell = new SpSwarmProjectile(
		enemyObject, this->players[0], &this->activeEnemiesCount, projectileRange, projectileDamage, attackRange, attackCooldown
	);
	enemyObject->addSpell(spell);	// HAS to be out here because of how spells are structured


	// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, color, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, 20);
	aiComponent = new AIComponent(*enemyObject);

	// STATES
	moveState = new SwarmerOutsideState(*enemyObject, *aiComponent, this->BossGrids.back(), this->swarmerIDs++, openingPos);


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
	GraphicsComponent* graphicsComponent = nullptr;
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


	XMFLOAT4 color(0.1f, 0.01f, 0.75f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 8.0f;
	float attackCooldown = 0.1f;
	float projectileRange = ARENADATA::GETarenaWidth() - 200.0f;
	float attackRange = ARENADATA::GETarenaWidth();
	float hp = 10000.0f;

	float velocityMagnitude = 180.0f;
	float topSpeed = 11.0f;

	// OBJECT
	enemyObject = new EnemyObject(
		ID, velocityMagnitude, topSpeed, pos,
		this->pGPS, &this->players,
		OBJECTTYPE::BOSS, hp
	);
	// SPELL (Needs to be before States)
	Spell* spell = new SpBossBulletHell(
		enemyObject, this->players[0], &this->activeEnemiesCount, projectileRange, projectileDamage, attackRange, attackCooldown
	);
	enemyObject->addSpell(spell);	// HAS to be out here because of how spells are structured


									// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, color, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, bossScale * 1.25f);
	aiComponent = new AIComponent(*enemyObject);
	// STATE
	bossMoveToArenaState = new BossMoveToArenaState(*enemyObject, *aiComponent, *this->pGPS, bossScale);

	return enemyObject;
}

std::vector<XMFLOAT3> EnemyManager::generateEnemySpawnPositions(enemySpawnPositions spawnPosVectors, XMFLOAT3 scale)
{
	std::vector<XMFLOAT3> generatedPositions;
	XMFLOAT3 spawnPosition;
	XMFLOAT3 openingPosition;

	bool reGenerateRandom = true;
	int spawnLocation = 0;
	int indexToOpening = -1;
	int relevantOpeningsCount = -1;
	float spawnOffset = Locator::getRandomGenerator()->GenerateFloat(900, 1000);
	if (this->pulse) {
		spawnOffset = 700.0f;
	}

	// Random a position
	while (reGenerateRandom)
	{
		// Random a cardinal direction, repeat if there are no openings for that side.
		spawnLocation = Locator::getRandomGenerator()->GenerateInt(1, 4);
		
		switch (spawnLocation) {
		case 1:
		{	// W E S T
			if (spawnPosVectors.west.size() > 0) {

				// Firstly generate the spawn position
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.west.size() - 1));
				spawnPosition = {
					(spawnPosVectors.west.at(spawnLocation).x - spawnOffset),
					scale.y,
					spawnPosVectors.west.at(spawnLocation).y
				};

				// Then fetch an opening in the wall
				relevantOpeningsCount = spawnPosVectors.west.size();
				indexToOpening = Locator::getRandomGenerator()->GenerateInt(0, relevantOpeningsCount - 1);
				openingPosition.x = spawnPosVectors.west[indexToOpening].x;
				openingPosition.y = 0;
				openingPosition.z = spawnPosVectors.west[indexToOpening].y;

				reGenerateRandom = false;
			}
			break;
		}
		case 2:
		{	// S O U T H
			if (spawnPosVectors.south.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.south.size() - 1));
				spawnPosition = {
					spawnPosVectors.south.at(spawnLocation).x,
					scale.y,
					(spawnPosVectors.south.at(spawnLocation).y - spawnOffset)
				};

				// Then fetch an opening in the wall
				relevantOpeningsCount = spawnPosVectors.south.size();
				indexToOpening = Locator::getRandomGenerator()->GenerateInt(0, relevantOpeningsCount - 1);
				openingPosition.x = spawnPosVectors.south[indexToOpening].x;
				openingPosition.y = 0;
				openingPosition.z = spawnPosVectors.south[indexToOpening].y;

				reGenerateRandom = false;
			}
			break;
		}
		case 3:
		{	// E A S T
			if (spawnPosVectors.east.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.east.size() - 1));
				spawnPosition = {
					(spawnPosVectors.east.at(spawnLocation).x + spawnOffset),
					scale.y,
					spawnPosVectors.east.at(spawnLocation).y
				};

				// Then fetch an opening in the wall
				relevantOpeningsCount = spawnPosVectors.east.size();
				indexToOpening = Locator::getRandomGenerator()->GenerateInt(0, relevantOpeningsCount - 1);
				openingPosition.x = spawnPosVectors.east[indexToOpening].x;
				openingPosition.y = 0;
				openingPosition.z = spawnPosVectors.east[indexToOpening].y;

				reGenerateRandom = false;
			}
			break;
		}
		case 4:
		{	// N O R T H
			if (spawnPosVectors.north.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.north.size() - 1));
				spawnPosition = {
					spawnPosVectors.north.at(spawnLocation).x,
					scale.y,
					(spawnPosVectors.north.at(spawnLocation).y + spawnOffset)
				};

				// Then fetch an opening in the wall
				relevantOpeningsCount = spawnPosVectors.north.size();
				indexToOpening = Locator::getRandomGenerator()->GenerateInt(0, relevantOpeningsCount - 1);
				openingPosition.x = spawnPosVectors.north[indexToOpening].x;
				openingPosition.y = 0;
				openingPosition.z = spawnPosVectors.north[indexToOpening].y;

				reGenerateRandom = false;
			}
			break;
		}
		break;
		}
	}

	generatedPositions.push_back(spawnPosition);
	generatedPositions.push_back(openingPosition);

	return generatedPositions;
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
	//if (this->waveElementRemoval && this->waves.size() > 0) {
	//	GUI->popWaveElement(*this->pGPS->GETGUIObjects(), *this->pGPS->getGraphicsComponents());
	//	Locator::getAudioManager()->play(SOUND::NAME::EIGHTBIT_NEXTWAVE);
	//	this->waveElementRemoval = false;
	//}

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
		// Enough time has passed to start the next wave
		else if (this->timePassed > this->waveInterval) {
			this->waveElementRemoval = true;
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
			Locator::getAudioManager()->play(SOUND::NAME::EIGHTBIT_LEVELEND);
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
	
	// Boss specific
	for (auto &currentGrid : this->BossGrids) {
		currentGrid->cleanUp();
		delete currentGrid;
		currentGrid = nullptr;
	}
	for (auto &currentArrayList : this->BossSwarmers) {
		currentArrayList->cleanUp();
		delete currentArrayList;
		currentArrayList = nullptr;
	}
	while (this->BossGrids.size() > 0)
		this->BossGrids.pop_back();
	while (this->BossSwarmers.size() > 0)
		this->BossSwarmers.pop_back();
}