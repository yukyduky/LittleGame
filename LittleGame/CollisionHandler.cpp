#include "CollisionHandler.h"



/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

int CollisionHandler::createCollisionID() {

	switch (this->collidable1->getType()) {
		// COLLIDABLE ID-LIST:
		/*
		// P   L   A   Y   E   R
		// 1	=	PLAYER				+			PLAYER
		// 2	=	PLAYER				+			ENEMY
		// 3	=	PLAYER				+			DOODAD
		// 4	=	PLAYER				+			INDESTRUCTIBLE
		// 5	=	PLAYER				+			PROJECTILE

		// E   N   E   M   Y
		// 6	=	ENEMY				+			ENEMY
		// 7	=	ENEMY				+			DOODAD
		// 8	=	ENEMY				+			INDESCTRUCTIBLE
		// 9	=	ENEMY				+			PROJECTILE

		// D   O   O   D   A   D
		// 10	=	DOODAD				+			DOODAD
		// 11	=	DOODAD				+			INDESTRUCTIBLE
		// 12	=	DOODAD				+			PROJECTILE

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
			return 1;
		}
		case OBJECTTYPE::ENEMY: { // PLAYER <--> ENEMY
			return 2;
		}
		case OBJECTTYPE::DOODAD: { // PLAYER <--> DOODAD
			return 3;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // PLAYER <--> INDESTRUCTIBLE
			return 4;
		}
		case OBJECTTYPE::PROJECTILE: { // PLAYER <--> PROJECTILE
			return 5;
		}
		}
	}
		// Collidable #1 = ENEMY
	case OBJECTTYPE::ENEMY: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // ENEMY <--> PLAYER
			return 2;
		}
		case OBJECTTYPE::ENEMY: { // ENEMY <--> ENEMY
			return 6;
		}
		case OBJECTTYPE::DOODAD: { // ENEMY <--> DOODAD
			return 7;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // ENEMY <--> INDESTRUCTIBLE
			return 8;
		}
		case OBJECTTYPE::PROJECTILE: { // ENEMY <--> PROJECTILE
			return 9;
		}
		}
	}
		// Collidable #1 = DOODAD
	case OBJECTTYPE::DOODAD: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // DOODAD <--> PLAYER
			return 3;
		}
		case OBJECTTYPE::ENEMY: { // DOODAD <--> ENEMY
			return 7;
		}
		case OBJECTTYPE::DOODAD: { // DOODAD <--> DOODAD
			return 10;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // DOODAD <--> INDESTRUCTIBLE
			return 11;
		}
		case OBJECTTYPE::PROJECTILE: { // DOODAD <--> PROJECTILE
			return 12;
		}
		}
	}
		// Collidable #1 = INDESTRUCTIBLE
	case OBJECTTYPE::INDESTRUCTIBLE: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // INDESTRUCTIBLE <--> PLAYER
			return 4;
		}
		case OBJECTTYPE::ENEMY: { // INDESTRUCTIBLE <--> ENEMY
			return 8;
		}
		case OBJECTTYPE::DOODAD: { // INDESTRUCTIBLE <--> DOODAD
			return 11;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // INDESTRUCTIBLE <--> INDESTRUCTIBLE
			return 13;
		}
		case OBJECTTYPE::PROJECTILE: { // INDESTRUCTIBLE <--> PROJECTILE
			return 14;
		}
		}
	}
		// Collidable #1 = PROJECTILE
	case OBJECTTYPE::PROJECTILE: {
		switch (this->collidable2->getType()) {
		case OBJECTTYPE::PLAYER: { // PROJECTILE <--> PLAYER
			return 5;
		}
		case OBJECTTYPE::ENEMY: { // PROJECTILE <--> ENEMY
			return 9;
		}
		case OBJECTTYPE::DOODAD: { // PROJECTILE <--> DOODAD
			return 12;
		}
		case OBJECTTYPE::INDESTRUCTIBLE: { // PROJECTILE <--> INDESTRUCTIBLE
			return 14;
		}
		case OBJECTTYPE::PROJECTILE: { // PROJECTILE <--> PROJECTILE
			return 15;
		}
		}
	}
	}
}

void CollisionHandler::calculateDistance(float x1, float y1, float x2, float y2) {
	// This method calculates the approximate distance between two points.
	// NOTE: It does NOT use the 'sqrt()' function due to optimization!
	this->xDiff = std::abs(x2 - x1);
	this->yDiff = std::abs(y2 - y1);
	this->minDiff = std::_Min_value(this->xDiff, this->yDiff);

	this->distance = (this->minDiff * DISTANCE_FACTOR);
	this->distance += ((this->xDiff - this->minDiff) + (this->yDiff - this->minDiff));
}

void CollisionHandler::collisionPlayerPlayer() {

	this->calculateDistance(
		this->collidable1->getPosition().x,
		this->collidable1->getPosition().y,
		this->collidable2->getPosition().x,
		this->collidable2->getPosition().y
	);

	this->centerToCenterVector = (collidable1->getPosition() - collidable2->getPosition());
	this->divisionFactor = (1.0 / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		this->centerToCenterVector.y * this->divisionFactor,
		this->centerToCenterVector.z * this->divisionFactor
	};

	/// Might be needed if we upgrade this code
	//this->radiusDistanceVector = (this->boundingArea1->Radius + this->boundingArea2->Radius);

	this->collidable1->setPosition(this->collidable1->getPosition() - (this->resultVector * this->stepper));
	this->collidable2->setPosition(this->collidable2->getPosition() + (this->resultVector * this->stepper));

	return;
}

void CollisionHandler::collisionPlayerEnemy() {

	// Swapping places of collidables with eachother if necessary
	// collidable1 = PLAYER
	if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	this->calculateDistance(
		this->collidable1->getPosition().x,
		this->collidable1->getPosition().y,
		this->collidable2->getPosition().x,
		this->collidable2->getPosition().y
	);

	this->centerToCenterVector = (collidable1->getPosition() - collidable2->getPosition());
	this->divisionFactor = (1.0 / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		this->centerToCenterVector.y * this->divisionFactor,
		this->centerToCenterVector.z * this->divisionFactor
	};

	// Enemies are moved out of the way of players
	this->collidable2->setPosition(this->collidable2->getPosition() + this->resultVector);

	return;
}

void CollisionHandler::collisionPlayerDoodad() {

	// Swapping places of collidables with eachother if necessary
	// collidable1 = PLAYER
	if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	// Currently interacting with a doodad does nothing,
	// since they are 99% invisible, invincible, etc. etc.

	return;
}

void CollisionHandler::collisionPlayerIndestruct() {

	// Swapping places of collidables with eachother if necessary
	// collidable1 = PLAYER
	if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	this->calculateDistance(
		this->collidable1->getPosition().x,
		this->collidable1->getPosition().y,
		this->collidable2->getPosition().x,
		this->collidable2->getPosition().y
	);

	this->centerToCenterVector = (collidable1->getPosition() - collidable2->getPosition());
	this->divisionFactor = (1.0 / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		this->centerToCenterVector.y * this->divisionFactor,
		this->centerToCenterVector.z * this->divisionFactor
	};

	// Moving the player only, since the indestructibles cannot move.
	collidable1->setPosition(this->collidable1->getPosition() - (this->resultVector * this->stepper));

	return;
}

void CollisionHandler::collisionPlayerProjectile() {
	// Swapping places of collidables with eachother if necessary
	// collidable1 = PLAYER
	if (this->collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}

	return;
}

void CollisionHandler::collisionEnemyEnemy() {

	this->calculateDistance(
		this->collidable1->getPosition().x,
		this->collidable1->getPosition().y,
		this->collidable2->getPosition().x,
		this->collidable2->getPosition().y
	);

	this->centerToCenterVector = (collidable1->getPosition() - collidable2->getPosition());
	this->divisionFactor = (1.0 / this->distance);
	this->resultVector = {
		this->centerToCenterVector.x * this->divisionFactor,
		this->centerToCenterVector.y * this->divisionFactor,
		this->centerToCenterVector.z * this->divisionFactor
	};

	// Moving the player only, since the indestructibles cannot move.
	this->collidable1->setPosition(this->collidable1->getPosition() - (this->resultVector * this->stepper));
	this->collidable2->setPosition(this->collidable2->getPosition() + (this->resultVector * this->stepper));

	return;
}

void CollisionHandler::collisionEnemyDoodad() {

	// Swapping places of collidables with eachother if necessary
	// collidable1 = ENEMY
	if (this->collidable1->getType() != OBJECTTYPE::ENEMY) {
		this->tempCollidableHolder = this->collidable1;
		this->collidable1 = this->collidable2;
		this->collidable2 = this->tempCollidableHolder;
	}
}

void CollisionHandler::collisionEnemyIndestruct() {

}

void CollisionHandler::collisionEnemyProjectile() {

}

void CollisionHandler::collisionDoodadDoodad() {

}

void CollisionHandler::collisionDoodadIndestruct() {

}

void CollisionHandler::collisionDoodadProjectile() {

}

void CollisionHandler::collisionIndestructIndestruct() {

}

void CollisionHandler::collisionIndestrucProjectile() {

}

void CollisionHandler::collisionProjectileProjectile() {

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

	this->collisionID = this->createCollisionID();

	switch (collisionID) {
		// PLAYER <--> PLAYER
	case 1: {

	}
	}
}
//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////
