#pragma once
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"
#include <vector>
#include <array>
#include "Commands.h"
#include "RenderInputOrganizer.h"
//#include "GraphicsComponent.h"
//#include "GameObject.h"
#include "ActorObject.h"
#include "Projectile.h"
#include "Camera.h"
//#include "PhysicsComponent.h"
#include "CollisionHandler.h"
#include <list>
#include "ArenaGlobals.h"
#include "EnemyManager.h"
#include "LevelManager.h"
#include "QuadTree.h"
#include "GUIManager.h"
#include "IDHandler.h"
#include "MouseInput.h"


class Command;
class InputComponent;

//(Size of cube, color in XMFLOAT4, travelSpeed, range(time alive), if it should spin)
struct ProjProp {
	float size;
	XMFLOAT4 color;
	float speed;
	float range;
	bool spinn;

	ProjProp(float s, XMFLOAT4 c, float spd, float r, bool spn) 
		: size(s)
		, color(c)
		, speed(spd)
		, range(r)
		, spinn(spn)
	{}
	ProjProp() {}
};

namespace FLOORSTATE {
	enum STATE {
		ACTIVE, TFALLING, FALLING, RECOVERING, DEACTIVATED,
		FLASH, SIZE
	};
}

class GamePlayState : public State
{
private:
	static GamePlayState sGamePlayState;
	GameManager* pGM = nullptr;
	
	EnemyManager enemyManager;
	int ID = 0;
	int arenaWidth = 0;
	int arenaDepth = 0;
	QuadTree quadTree;
	CollisionHandler collisionHandler;
	LevelManager lm;
	Camera camera;
	GUIManager GUI;
	RenderInputOrganizer rio;
	std::vector<std::vector<tileData>> grid;
	//everything that will exist in this level
	std::list<GameObject*> GUIObjects;
	std::list<GameObject*> staticObjects;
	std::list<GameObject*> dynamicObjects;
	// Count below represents static objects that have collision (see 'checkCollisions()' function)
	std::list<GameObject*> noCollisionDynamicObjects;
	int staticPhysicsCount = 0;
	
	//Variables for falling floor
	FloorFallData fallData; //OLD
	FloorFallData currData;
	FLOORSTATE::STATE floorState;
	std::vector<FloorFallData> easyPatterns;
	std::vector<FloorFallData> mediumPatterns;
	std::vector<FloorFallData> hardPatterns;
	std::vector<Index> genIndex;
	double mediumTime;
	double hardTime;
	double totalLevelTime;
	double gTimeLastFrame;
	double stateTime;
	double timeBetweenPatterns;
	double tFallingTime;
	double fallAndRecoveryTime;
	double counter;
	double genTimer;
	double genCounter;
	double genEffectTime;
	bool recoveryMode;
	int currentPatternNr;
	double fallPatternCoolDown;
	double dt;
	bool playerSteppedOnBossTile;

	//All spawnPositions that will be used in the EnemyHandler
	enemySpawnPositions enemySpawnPos;


	//All objects that wants to be renederd
	std::list<GraphicsComponent*> graphics;
	std::array<InputComponent*, 1> playerInput;	// '1' for testing purposes, should be '5'

	IDHandler lightIDs;
	std::vector<Light> pointLights;

	//Template to be able to update player1, changed to vector when multiplayer is implemented
	ActorObject* player1 = nullptr;
	Command* selectCommand = nullptr;
	
	void checkCollisions();
	void updateFloorPattern();
	void updateFloor();
	void checkPlayerTileStatus();

	// Template version of picked up loot, is provided to RMS
	int nrOfPickedUpLoot = 0;
	void generatorDischarge(Index index);

	MouseInput* mousePicker = nullptr;
	float tempFloater = 1.0f;
public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the 'GamePlayState'.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleanup the 'GamePlayState'; freeing memory, default settings, etc.
	*/
	virtual void cleanUp();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Pause the 'GamePlayState'.
	*/
	virtual void pause();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Resume the 'GamePlayState'.
	*/
	virtual void resume();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Handle the events generated in the GamePlayState.
	*/
	virtual void handleEvents(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Update the GamePlayState.
	*/
	virtual void update(GameManager* gm);
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Render the 'GamePlayState'
	*/
	virtual void render(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Get the static instance of the 'GamePlayState'.
	*/
	static GamePlayState* getInstance();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns a reference to the internal dynamicObjects vector.
	- Currently only used by EnemyHandler for creation of enemies.
	*/
	std::list<GameObject*>* GETGUIObjects();
	std::list<GameObject*>* getDynamicObjects();
	std::list<GraphicsComponent*>* getGraphicsComponents();

	void addGraphics(GraphicsComponent* graphicsComponent);

	void initPlayer();

	/*call to shoot projectile*/
	Projectile* initProjectile(XMFLOAT3 pos, ActorObject* shooter, ProjProp props, Light light);

	std::vector<std::vector<tileData>>& GETgrid();

	bool GETplayerSteppedOnBossTile();
	void SETplayerSteppedOnBossTile(bool input);

	/*RETURNS THE NEW ID*/
	int newID() { return this->ID++; }

	MouseInput* GETMouseInput() { return this->mousePicker; }

};

#endif // !GAMEPLAYSTATE_H
