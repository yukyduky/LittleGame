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

#include "MouseInput.h"


class Command;
class InputComponent;

//(Size of cube, color in XMFLOAT4, travelSpeed, range(tiem alive), if it sould spinn)
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


class GamePlayState : public State
{
private:
	static GamePlayState sGamePlayState;
	GameManager* pGM;
	
	EnemyManager enemyManager;
	int ID = 0;
	int arenaWidth;
	int arenaDepth;
	QuadTree quadTree;
	CollisionHandler collisionHandler;
	LevelManager lm;
	Camera camera;
	RenderInputOrganizer rio;
	std::vector<std::vector<tileData>> grid;
	//everything that will exist in this level
	std::vector<GameObject*> staticObjects;
	std::vector<GameObject*> dynamicObjects;
	// Count below represents static objects that have collision (see 'checkCollisions()' function)
	std::vector<GameObject*> noCollisionDynamicObjects;
	int staticPhysicsCount = 0;
	
	//Variables for falling floor
	FloorFallData fallData;
	double counter = 0;

	//All objects that wants to be renederd
	std::vector<GraphicsComponent*> graphics;
	std::array<InputComponent*, 1> playerInput;	// '1' for testing purposes, should be '5'

	std::vector<Light> pointLights;

	//Template to be able to update player1, changed to vector when multiplayer is implemented
	ActorObject* player1;
	Command* selectCommand;
	
	void checkCollisions();

	MouseInput* mousePicker;


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
	std::vector<GameObject*>* getDynamicObjects();

	void addGraphics(GraphicsComponent* graphicsComponent);

	void initPlayer();

	/*call to shoot projectile*/
	Projectile* initProjectile(XMFLOAT3 pos, XMFLOAT3 dir, ProjProp props);

	/*RETURNS THE NEW ID*/
	int newID() { return this->ID++; }

	MouseInput* GETMouseInput() { return this->mousePicker; }

	void provide(ActorObject* player);
};

#endif // !GAMEPLAYSTATE_H
