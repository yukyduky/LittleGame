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
#include "MinionOutsideState.h"
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
}

void EnemyManager::startLevel1(enemySpawnPositions spawnPosVectors)
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 1;
	this->waveInterval = 0.1;
	this->currentWaveCount = 4;
	this->currentWaveSize = 20;
	Wave* currentWave;
	this->swarmerCount = 5;
	std::vector<EnemyObject*> localSwarmers;

	// TESTING -----------
	this->currentWaveCount = 2;
	this->currentWaveSize = 5;
	this->swarmerCount = 5;
	// TESTING -----------

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per minion
		for (int j = 0; j < this->currentWaveSize; j++) {
			// Create an enemy and attatch it to the wave.
			EnemyObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS, spawnPosVectors);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Per Swarmer
		for (int k = 0; k < swarmerCount; k++) {
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

		// Up the difficulty a bit maybe?
	//	this->currentWaveSize += 1;				REMOVED WHILE IMMOLATION IS NOT DONE
	}

	// Initialize the swarmers! (if there are any)
	if (this->swarmerCount > 0) {
		this->pSwarmers->initialize(localSwarmers);
	}

	// I couldn't figure out why, but the above loop creates 1 less enemy than it claims to.
//	this->activeEnemiesCount--;
}

void EnemyManager::startBossLevel()
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 1;
	this->waveInterval = 0.1;
	this->currentWaveCount = 1;
	this->currentWaveSize = 1;
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
	GraphicsComponent* graphicsComponent = nullptr;
	AIComponent* aiComponent = nullptr;
	InputComponent* input = nullptr;
	PhysicsComponent* physicsComponent = nullptr;
	EnemyAttackComponent* attackComponent = nullptr;
	// STATES
	EnemyState* moveState = nullptr;

	bool reGenerateRandom = true;
	int spawnLocation = 0;


	/// D E F I N I T I O N
	std::vector<XMFLOAT3> generatedPositions;
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 spawnPos = { 0.0f, 0.0f, 0.0001f };
	XMFLOAT3 openingPos = { 0.0f, 0.0f, 0.01f };

	generatedPositions = this->generateEnemySpawnPositions(spawnPosVectors, scale);
	spawnPos = generatedPositions[0];
	openingPos = generatedPositions[1];

	float velocity = 180;
	XMFLOAT4 enemyColor(1.0f, 0.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);
	float immolationDamage = 3;
	float attackCooldown = 0.5;
	float attackRange = 70;

	// OBJECT
	enemyObject = new EnemyObject(
		ENEMYTYPE::IMMOLATION, ID, spawnPos, velocity,
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
	moveState = new MinionOutsideState(*enemyObject, *aiComponent, this->pGrid, this->swarmerIDs++, openingPos);

	
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
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 spawnPos = { 0.0f, 0.0f, 0.0001f };
	XMFLOAT3 openingPos = { 0.0f, 0.0f, 0.01f };

	generatedPositions = this->generateEnemySpawnPositions(spawnPosVectors, scale);
	spawnPos = generatedPositions[0];
	openingPos = generatedPositions[1];


	float velocity = 180;
	XMFLOAT4 color(0.0f, 1.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 8;
	float attackCooldown = 0.5;
	float projectileRange = 200;
	float attackRange = 500;

	/// A T T A C H M E N T
	// OBJECT
	enemyObject = new EnemyObject(
		ENEMYTYPE::SWARMER, ID, spawnPos, velocity,
		pGPS, &this->players,
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
	moveState = new SwarmerOutsideState(*enemyObject, *aiComponent, this->pGrid, this->swarmerIDs++, openingPos);

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

	float velocity = 180;
	XMFLOAT4 color(0.0f, 1.0, 0.0f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 8;
	float attackCooldown = 0.5;
	float projectileRange = 200;
	float attackRange = 500;

	/// A T T A C H M E N T
	// OBJECT
	enemyObject = new EnemyObject(
		ENEMYTYPE::SWARMER, ID, spawnPos, velocity,
		pGPS, &this->players, 
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
	moveState = new SwarmerOutsideState(*enemyObject, *aiComponent, this->pGrid, this->swarmerIDs++, openingPos);

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


	float velocity = 180;
	XMFLOAT4 color(0.1f, 0.01f, 0.75f, 1.0f);
	XMFLOAT3 rotation(0, 0, 0);

	float projectileDamage = 8;
	float attackCooldown = 0.5;
	float projectileRange = ARENADATA::GETarenaWidth() - 200.0f;
	float attackRange = ARENADATA::GETarenaWidth();

	/// A T T A C H M E N T
	// OBJECT
	enemyObject = new EnemyObject(
		ENEMYTYPE::BOSS, ID, pos, velocity,
		pGPS, &this->players,
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

std::vector<XMFLOAT3> EnemyManager::generateEnemySpawnPositions(enemySpawnPositions spawnPosVectors, XMFLOAT3 scale)
{
	std::vector<XMFLOAT3> generatedPositions;
	XMFLOAT3 spawnPosition;
	XMFLOAT3 openingPosition;

	bool reGenerateRandom = true;
	int spawnLocation = 0;
	int indexToOpening = -1;
	int relevantOpeningsCount = -1;
	float spawnOffset = Locator::getRandomGenerator()->GenerateFloat(550, 650);

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