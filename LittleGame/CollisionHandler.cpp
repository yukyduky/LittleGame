#include "CollisionHandler.h"
#include "Spell.h"
#include "GameObject.h"

#include <cassert>

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

void CollisionHandler::createCollisionID() {

	switch (this->collidable1->getType()) {
		// COLLIDABLE ID-LIST:
		/*
		// P   L   A   Y   E   R
		// 1	=	PLAYER				+			PLAYER
		// 2	=	PLAYER				+			ENEMY
		// 3	=	PLAYER				+			GENERATOR
		// 4	=	PLAYER				+			INDESTRUCTIBLE
		// 5	=	PLAYER				+			PROJECTILE
		// 6	=	PLAYER				+			BOSS

		// E   N   E   M   Y
		// 7	=	ENEMY				+			ENEMY
		// 8	=	ENEMY				+			GENERATOR
		// 9	=	ENEMY				+			INDESCTRUCTIBLE
		// 10	=	ENEMY				+			PROJECTILE
		// 11	=	ENEMY				+			BOSS

		// D   O   O   D   A   D
		// 12	=	GENERATOR			+			GENERATOR
		// 13	=	GENERATOR			+			INDESTRUCTIBLE
		// 14	=	GENERATOR			+			PROJECTILE
		// 15	=	GENERATOR			+			BOSS

		// I  N  D  E  S  T  R  U  C  T  I  B  L  E
		// 16	=	INDESTRUCTIBLE		+			INDESTRUCTIBLE
		// 17	=	INDESTRUCTIBLE		+			PROJECTILE
		// 18	=	INDESTRUCTIBLE		+			BOSS

		// P   R   O   J   E   C   T   I   L   E
		// 19	=	PROJECTILE			+			PROJECTILE
		// 20	=	PROJECTILE			+			BOSS

		// B   O   S   S
		// 21	=	BOSS				+			BOSS
		*/

		// Collidable1 = PLAYER
	case OBJECTTYPE::PLAYER: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // PLAYER <--> PLAYER
			this->collisionID = 1;
			break;
		}
		case OBJECTTYPE::ENEMY: { // PLAYER <--> ENEMY
			this->collisionID = 2;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // PLAYER <--> GENERATOR
			this->collisionID = 3;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // PLAYER <--> INDESTRUCTIBLE
			this->collisionID = 4;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // PLAYER <--> PROJECTILE
			this->collisionID = 5;
			break;
		}
		case OBJECTTYPE::BOSS: { // PLAYER <--> BOSS
			this->collisionID = 6;
			break;
		}
		}
		break;
	}
		// Collidable1 = ENEMY
	case OBJECTTYPE::ENEMY: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // ENEMY <--> PLAYER
			this->collisionID = 2;
			break;
		}
		case OBJECTTYPE::ENEMY: { // ENEMY <--> ENEMY
			this->collisionID = 7;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // ENEMY <--> GENERATOR
			this->collisionID = 8;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // ENEMY <--> INDESTRUCTIBLE
			this->collisionID = 9;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // ENEMY <--> PROJECTILE
			this->collisionID = 10;
			break;
		}
		case OBJECTTYPE::BOSS: { // ENEMY <--> BOSS
			this->collisionID = 11;
			break;
		}
		}
		break;
	}
		// Collidable1 = GENERATOR
	case OBJECTTYPE::GENERATOR: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // GENERATOR <--> PLAYER
			this->collisionID = 3;
			break;
		}
		case OBJECTTYPE::ENEMY: { // GENERATOR <--> ENEMY
			this->collisionID = 8;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // GENERATOR <--> GENERATOR
			this->collisionID = 12;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // GENERATOR <--> INDESTRUCTIBLE
			this->collisionID = 13;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // GENERATOR <--> PROJECTILE
			this->collisionID = 14;
			break;
		}
		case OBJECTTYPE::BOSS: { // GENERATOR <--> BOSS
			this->collisionID = 15;
		}
		}
		break;
	}
		// Collidable #1 = INDESTRUCTIBLE
	case OBJECTTYPE::INDESTRUCTIBLE: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // INDESTRUCTIBLE <--> PLAYER
			this->collisionID = 4;
			break;
		}
		case OBJECTTYPE::ENEMY: { // INDESTRUCTIBLE <--> ENEMY
			this->collisionID = 9;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // INDESTRUCTIBLE <--> GENERATOR
			this->collisionID = 13;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // INDESTRUCTIBLE <--> INDESTRUCTIBLE
			this->collisionID = 16;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // INDESTRUCTIBLE <--> PROJECTILE
			this->collisionID = 17;
			break;
		}
		case OBJECTTYPE::BOSS: { // INDESTRUCTIBLE <--> BOSS
			this->collisionID = 18;
			break;
		}
		}
		break;
	}
		// Collidable1 = PROJECTILE
	case OBJECTTYPE::PROJECTILE: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // PROJECTILE <--> PLAYER
			this->collisionID = 5;
			break;
		}
		case OBJECTTYPE::ENEMY: { // PROJECTILE <--> ENEMY
			this->collisionID = 10;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // PROJECTILE <--> GENERATOR
			this->collisionID = 14;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // PROJECTILE <--> INDESTRUCTIBLE
			this->collisionID = 17;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // PROJECTILE <--> PROJECTILE
			this->collisionID = 19;
			break;
		}
		case OBJECTTYPE::BOSS: { // PROJECTILE <--> BOSS
			this->collisionID = 20;
		}
		}
		break;
	}
	case OBJECTTYPE::BOSS: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: {
			this->collisionID = 6;
			break;
		}
		case OBJECTTYPE::ENEMY: {
			this->collisionID = 11;
			break;
		}
		case OBJECTTYPE::GENERATOR: {
			this->collisionID = 15;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: {
			this->collisionID = 18;
			break;
		}
		case OBJECTTYPE::PROJECTILE: {
			this->collisionID = 20;
			break;
		}
		case OBJECTTYPE::BOSS: {
			this->collisionID = 21;
			break;
		}
		}
	}
	}
}

void CollisionHandler::calculateDistance(DirectX::XMFLOAT3 collidable1, DirectX::XMFLOAT3 collidable2) {
	// This method calculates the approximate distance between two points.
	// NOTE: It does NOT use the 'sqrt()' function resulting in optimization!
	this->xDiff = std::abs(collidable2.x - collidable1.x);
	this->zDiff = std::abs(collidable2.z - collidable1.z);
	this->minDiff = std::_Min_value(this->xDiff, this->zDiff);

	this->distance = (this->minDiff * DISTANCE_FACTOR);
	this->distance += ((this->xDiff - this->minDiff) + (this->zDiff - this->minDiff));
}

//void CollisionHandler::calculateDistance(float x1, float y1, float x2, float y2) {
//	// This method calculates the approximate distance between two points.
//	// NOTE: It does NOT use the 'sqrt()' function resulting in optimization!
//	this->xDiff = std::abs(x2 - x1);
//	this->yDiff = std::abs(y2 - y1);
//	this->minDiff = std::_Min_value(this->xDiff, this->yDiff);
//
//	this->distance = (this->minDiff * DISTANCE_FACTOR);
//	this->distance += ((this->xDiff - this->minDiff) + (this->yDiff - this->minDiff));
//}

void CollisionHandler::collisionPlayerPlayer() {

	this->calculateDistance(
		this->collidable1->GETPosition(),
		this->collidable2->GETPosition()
	);

	this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
	this->divisionFactor = (1.0f / this->distance);
	this->resultVector = {
		this->stepper * (this->centerToCenterVector.x * this->divisionFactor),
		this->stepper * (this->centerToCenterVector.y * this->divisionFactor),
		this->stepper * (this->centerToCenterVector.z * this->divisionFactor)
	};

	this->collidable1->setPosition(this->collidable1->GETPosition() - (this->resultVector * this->stepper));
	this->collidable2->setPosition(this->collidable2->GETPosition() + (this->resultVector * this->stepper));
}

void CollisionHandler::collisionPlayerEnemy() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = PLAYER
	if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	// Check if we're colliding with something that's charged
	EnemyObject* trueEnemy = static_cast<EnemyObject*>(this->collidable2);
	if (trueEnemy->getIfCharged()) {
		ActorObject* truePlayer = static_cast<ActorObject*>(this->collidable1);
		truePlayer->dealDmg(trueEnemy->getCollisionDamage());
		trueEnemy->setIfCharged(false);
		Locator::getAudioManager()->play(SOUND::TRIANGLESLICE);
	}
	// Collide normally
	else {
		this->calculateDistance(
			this->collidable1->GETPosition(),
			this->collidable2->GETPosition()
		);

		this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
		this->divisionFactor = (1.0f / this->distance);
		this->resultVector = {
			(this->stepper * 3) * (this->centerToCenterVector.x * this->divisionFactor),
			0.0,
			(this->stepper * 3) * (this->centerToCenterVector.z * this->divisionFactor)
		};

		DirectX::XMFLOAT3 newEnemyPos = this->collidable2->GETPosition() - (this->resultVector * this->stepper);

		// Enemies are moved out of the way of players
		this->collidable2->setPosition(newEnemyPos);
		this->collidable2->GETphysicsComponent()->updateBoundingArea(newEnemyPos);
	}
}

void CollisionHandler::collisionPlayerGenerator() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = PLAYER
	if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	this->calculateDistance(
		this->collidable1->GETPosition(),
		this->collidable2->GETPosition()
	);

	this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
	this->divisionFactor = (1.0f / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		0.0,
		this->centerToCenterVector.z * this->divisionFactor
	};

	// Moving the player only, since the indestructibles cannot move.
	collidable1->setPosition(this->collidable1->GETPosition() + (this->resultVector * this->stepper));
}

void CollisionHandler::collisionPlayerIndestruct() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = PLAYER
	//if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
	//	this->tempCollidableHolder = this->collidable1;
	//	this->collidable1 = this->collidable2;
	//	this->collidable2 = this->tempCollidableHolder;
	//}

	this->calculateDistance(
		this->collidable1->GETPosition(),
		this->collidable2->GETPosition()
	);

	this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
	this->divisionFactor = (1.0f / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		0.0,
		this->centerToCenterVector.z * this->divisionFactor
	};

	// Moving the player only, since the indestructibles cannot move.
	collidable1->setPosition(this->collidable1->GETPosition() + (this->resultVector * this->stepper));
	//collidable1->setVelocity(this->resultVector);
}

void CollisionHandler::collisionPlayerProjectile() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = PLAYER
	if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	Projectile* proj = static_cast<Projectile*>(this->collidable2);
	Spell* spell = proj->getSpell();
	spell->collision(this->collidable1, proj);
}

void CollisionHandler::collisionEnemyEnemy() {
	this->calculateDistance(
		this->collidable1->GETPosition(),
		this->collidable2->GETPosition()
	);

	this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
	this->divisionFactor = (1.0f / this->distance);
	this->resultVector = {
		this->stepper * (this->centerToCenterVector.x * this->divisionFactor),
		0.0,
		this->stepper * this->centerToCenterVector.z * this->divisionFactor
	};

	// Enemies are moved, and not doodads
	this->collidable2->setPosition(this->collidable2->GETPosition() - this->resultVector);
}

void CollisionHandler::collisionPlayerBoss() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = PLAYER
	if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	// CODE GOES HERE
	this->calculateDistance(
		this->collidable1->GETPosition(),
		this->collidable2->GETPosition()
	);

	this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
	this->divisionFactor = (1.0f / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		0.0,
		this->centerToCenterVector.z * this->divisionFactor
	};

	// Moving the player only, since the indestructibles cannot move.
	collidable1->setPosition(this->collidable1->GETPosition() + (this->resultVector * this->stepper));
}

void CollisionHandler::collisionEnemyGenerator() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = ENEMY
	if (this->collidable1->getType() != OBJECTTYPE::ENEMY) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	this->calculateDistance(
		this->collidable1->GETPosition(),
		this->collidable2->GETPosition()
	);

	this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
	this->divisionFactor = (1.0f / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		0.0,
		this->centerToCenterVector.z * this->divisionFactor
	};

	// Moving the player only, since the indestructibles cannot move.
	collidable1->setPosition(this->collidable1->GETPosition() + (this->resultVector * this->stepper));
}

void CollisionHandler::collisionEnemyIndestruct() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = ENEMY
	if (this->collidable1->getType() != OBJECTTYPE::ENEMY) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	this->calculateDistance(
		this->collidable1->GETPosition(),
		this->collidable2->GETPosition()
	);

	this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
	this->divisionFactor = (1.0f / this->distance);
	this->resultVector = {
		(this->stepper * 3) * (this->centerToCenterVector.x * this->divisionFactor),
		0.0,
		(this->stepper * 3) * (this->centerToCenterVector.z * this->divisionFactor)
	};

	// Moving the player only, since the indestructibles cannot move.
	collidable1->setPosition(this->collidable1->GETPosition() + (this->resultVector * this->stepper));
}

void CollisionHandler::collisionEnemyProjectile() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = ENEMY
	if (this->collidable1->getType() != OBJECTTYPE::ENEMY) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	Projectile* proj = static_cast<Projectile*>(this->collidable2);
	Spell* spell = proj->getSpell();
	spell->collision(this->collidable1, proj);
}

void CollisionHandler::collisionEnemyBoss() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = ENEMY
	if (this->collidable1->getType() != OBJECTTYPE::ENEMY) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	// CODE GOES HERE
	this->calculateDistance(
		this->collidable1->GETPosition(),
		this->collidable2->GETPosition()
	);

	this->centerToCenterVector = (collidable1->GETPosition() - collidable2->GETPosition());
	this->divisionFactor = (1.0f / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		0.0,
		this->centerToCenterVector.z * this->divisionFactor
	};

	// Moving the player only, since the indestructibles cannot move.
	collidable1->setPosition(this->collidable1->GETPosition() + (this->resultVector * this->stepper));
}

void CollisionHandler::collisionGeneratorGenerator() {
	// A GENERATOR colliding with another GENERATOR?
	// Now that just sounds silly.
	/// Does nothing for the time being.
}

void CollisionHandler::collisionGeneratorIndestruct() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = DOODAD
	//if (this->collidable1->getType() != OBJECTTYPE::DOODAD) {
	//	this->tempCollidableHolder = this->collidable1;
	//	this->collidable1 = this->collidable2;
	//	this->collidable2 = this->tempCollidableHolder;
	//}

	// A GENERATOR colliding with an indestructible?
	// Also seems kinda silly.
	/// Does nothing for the time being.
}

void CollisionHandler::collisionGeneratorProjectile() {
	// Swapping places of collidables with eachother if necessary
	// collidable1 = DOODAD
	if (this->collidable1->getType() != OBJECTTYPE::GENERATOR) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	Projectile* proj = static_cast<Projectile*>(this->collidable2);
	Spell* spell = proj->getSpell();
	spell->collision(this->collidable1, proj);

	// There's potential here I suppose, mostly in terms of graphical effects, perhaps.
	/// Regardless, this too does nothing for now.
}

void CollisionHandler::collisionGeneratorBoss() {
	// Swapping places of collidables with eachother if necessary
	// collidable1 = DOODAD
	if (this->collidable1->getType() != OBJECTTYPE::GENERATOR) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	// CODE GOES HERE
}

void CollisionHandler::collisionIndestructIndestruct() {
	// Seems somewhat unlikely.
	/// Does nothing for now.
}

void CollisionHandler::collisionIndestrucProjectile() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = INDESTRUCTIBLE
	if (this->collidable1->getType() != OBJECTTYPE::INDESTRUCTIBLE) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	//this->collidable2->setState(OBJECTSTATE::TYPE::DEAD);

	Projectile* proj = static_cast<Projectile*>(this->collidable2);
	Spell* spell = proj->getSpell();

	spell->collision(this->collidable1, proj);
	//spell->setActive(false);
}

void CollisionHandler::collisionIndestrucBoss() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = INDESTRUCTIBLE
	if (this->collidable1->getType() != OBJECTTYPE::INDESTRUCTIBLE) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	// CODE GOES HERE
}

void CollisionHandler::collisionProjectileProjectile() {
	// Somewhat skillfull if you manage to pull this off.
	// At least assuming that the game is still single player.

	// DOES NOTHING FOR NOW.
}

void CollisionHandler::collisionProjectileBoss() {
	// Swapping places of collidables with eachother if necessary
	// COLLIDABLE1 = INDESTRUCTIBLE
	if (this->collidable1->getType() != OBJECTTYPE::BOSS) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	// CODE GOES HERE.
	Projectile* proj = static_cast<Projectile*>(this->collidable2);
	Spell* spell = proj->getSpell();
	spell->collision(this->collidable1, proj);
}

void CollisionHandler::collisionBossBoss() {
	// CODE GOES HERE.
}
//_________________________________________//
//                                         //
//             END OF PRIVATE              //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PUBLIC            |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

CollisionHandler::CollisionHandler() {
	this->collidable1 = nullptr;
	this->collidable2 = nullptr;
	this->boundingArea1 = nullptr;
	this->boundingArea2 = nullptr;

}

CollisionHandler::~CollisionHandler() {

}

void CollisionHandler::executeCollision(
	GameObject* collidable1,
	GameObject* collidable2,
	DirectX::BoundingSphere* boundingArea1,
	DirectX::BoundingSphere* boundingArea2) {

	this->collidable1 = collidable1;
	this->collidable2 = collidable2;
	this->boundingArea1 = boundingArea1;
	this->boundingArea2 = boundingArea2;

	this->createCollisionID();

	if (this->collidable1->GETPosition().x == this->collidable2->GETPosition().x &&
		this->collidable1->GETPosition().z == this->collidable2->GETPosition().z)
		this->collidable1->nudgePos();

	switch (collisionID) {
		// PLAYER
	case 1: this->collisionPlayerPlayer();
		break;
	case 2: this->collisionPlayerEnemy();
		break;
	case 3: this->collisionPlayerGenerator();
		break;
	case 4: this->collisionPlayerIndestruct();
		break;
	case 5: this->collisionPlayerProjectile();
		break;
	case 6: this->collisionPlayerBoss();
		break;
		// ENEMY
	case 7: this->collisionEnemyEnemy();
		break;
	case 8: this->collisionEnemyGenerator();
		break;
	case 9: this->collisionEnemyIndestruct();
		break;
	case 10: this->collisionEnemyProjectile();
		break;
	case 11: this->collisionEnemyBoss();
		break;
		// DOODAD
	case 12: this->collisionGeneratorGenerator();
		break;
	case 13: this->collisionGeneratorIndestruct();
		break;
	case 14: this->collisionGeneratorProjectile();
		break;
	case 15: this->collisionGeneratorBoss();
		break;
		// INDESTRUCTIBLE
	case 16: this->collisionIndestructIndestruct();
		break;
	case 17: this->collisionIndestrucProjectile();
		break;
	case 18: this->collisionIndestrucBoss();
		break;
		// PROJECTILE
	case 19: this->collisionProjectileProjectile();
		break;
	case 20: this->collisionProjectileBoss();
		break;
		// BOSS
	case 21: this->collisionBossBoss();
		break;
	}

	// If an object never had it's type set, these assertions will go off, crashing the program
	assert(this->collidable2->getType() != OBJECTTYPE::NOT_SET && "WARNING: 'Collidable1' has not had it's objectType set!!!");
	assert(this->collidable1->getType() != OBJECTTYPE::NOT_SET && "WARNING: 'Collidable1' has not had it's objectType set!!!");
}
//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////
