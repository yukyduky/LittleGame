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

		// E   N   E   M   Y
		// 6	=	ENEMY				+			ENEMY
		// 7	=	ENEMY				+			GENERATOR
		// 8	=	ENEMY				+			INDESCTRUCTIBLE
		// 9	=	ENEMY				+			PROJECTILE

		// G  E  N  E  R  A  T  O  R
		// 10	=	GENERATOR			+			GENERATOR
		// 11	=	GENERATOR			+			INDESTRUCTIBLE
		// 12	=	GENERATOR			+			PROJECTILE

		// I  N  D  E  S  T  R  U  C  T  I  B  L  E
		// 13	=	INDESTRUCTIBLE		+			INDESTRUCTIBLE
		// 14	=	INDESTRUCTIBLE		+			PROJECTILE

		// P   R   O   J   E   C   T   I   L   E
		// 15	=	PROJECTILE			+			PROJECTILE
		*/

		// Collidable #1 = PLAYER
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
		}
		break;
	}
		// Collidable #1 = ENEMY
	case OBJECTTYPE::ENEMY: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // ENEMY <--> PLAYER
			this->collisionID = 2;
			break;
		}
		case OBJECTTYPE::ENEMY: { // ENEMY <--> ENEMY
			this->collisionID = 6;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // ENEMY <--> GENERATOR
			this->collisionID = 7;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // ENEMY <--> INDESTRUCTIBLE
			this->collisionID = 8;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // ENEMY <--> PROJECTILE
			this->collisionID = 9;
			break;
		}
		}
		break;
	}
		// Collidable #1 = GENERATOR
	case OBJECTTYPE::GENERATOR: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // GENERATOR <--> PLAYER
			this->collisionID = 3;
			break;
		}
		case OBJECTTYPE::ENEMY: { // GENERATOR <--> ENEMY
			this->collisionID = 7;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // GENERATOR <--> GENERATOR
			this->collisionID = 10;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // GENERATOR <--> INDESTRUCTIBLE
			this->collisionID = 11;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // GENERATOR <--> PROJECTILE
			this->collisionID = 12;
			break;
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
			this->collisionID = 8;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // INDESTRUCTIBLE <--> GENERATOR
			this->collisionID = 11;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // INDESTRUCTIBLE <--> INDESTRUCTIBLE
			this->collisionID = 13;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // INDESTRUCTIBLE <--> PROJECTILE
			this->collisionID = 14;
			break;
		}
		}
		break;
	}
		// Collidable #1 = PROJECTILE
	case OBJECTTYPE::PROJECTILE: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // PROJECTILE <--> PLAYER
			this->collisionID = 5;
			break;
		}
		case OBJECTTYPE::ENEMY: { // PROJECTILE <--> ENEMY
			this->collisionID = 9;
			break;
		}
		case OBJECTTYPE::GENERATOR: { // PROJECTILE <--> DOODAD
			this->collisionID = 12;
			break;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // PROJECTILE <--> INDESTRUCTIBLE
			this->collisionID = 14;
			break;
		}
		case OBJECTTYPE::PROJECTILE: { // PROJECTILE <--> PROJECTILE
			this->collisionID = 15;
			break;
		}
		}
		break;
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

void CollisionHandler::collisionProjectileProjectile() {
	// Somewhat skillfull if you manage to pull this off.
	// At least assuming that the game is still single player.
	/// Does nothing for now.
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
		// ENEMY
	case 6: this->collisionEnemyEnemy();
		break;
	case 7: this->collisionEnemyGenerator();
		break;
	case 8: this->collisionEnemyIndestruct();
		break;
	case 9: this->collisionEnemyProjectile();
		break;
		// DOODAD
	case 10: this->collisionGeneratorGenerator();
		break;
	case 11: this->collisionGeneratorIndestruct();
		break;
	case 12: this->collisionGeneratorProjectile();
		break;
		// INDESTRUCTIBLE
	case 13: this->collisionIndestructIndestruct();
		break;
	case 14: this->collisionIndestrucProjectile();
		break;
		// PROJECTILE
	case 15: this->collisionProjectileProjectile();
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
