#include "PhysicsComponent.h"
#include "GameObject.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                             PHYSICS COMPONENT           /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

int PhysicsComponent::createCollisionID(
	GameObject* collidable1,
	GameObject* collidable2) {

	switch (collidable1->getType()) {
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
		switch (collidable2->getType()) {
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
		switch (collidable2->getType()) {
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
		switch (collidable2->getType()) {
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
		switch (collidable2->getType()) {
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
		switch (collidable2->getType()) {
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

void PhysicsComponent::collisionPlayerPlayer(
	GameObject* collidable1,
	GameObject* collidable2) {
	// SEPARATE BOUNDING AREAS
	collidable1->setPosition(DirectX::XMFLOAT3(

	)

	collidable1->setPosition(DirectX::XMFLOAT3(
		collidable1->getPosition().x - (collidable1->getVelocity().x * this->stepper),
		collidable1->getPosition().y - (collidable1->getVelocity().y * this->stepper),
		collidable1->getPosition().z - (collidable1->getVelocity().z * this->stepper))
	);
	collidable2->setPosition(DirectX::XMFLOAT3(
		collidable2->getPosition().x - (collidable2->getVelocity().x * this->stepper),
		collidable2->getPosition().y - (collidable2->getVelocity().y * this->stepper),
		collidable2->getPosition().z - (collidable2->getVelocity().z * this->stepper))
	);

	// Run function as per usual

	return;
}

void PhysicsComponent::collisionPlayerEnemy(
	GameObject* collidable1,
	GameObject* collidable2) {

	// Swapping places of collidables with eachother if necessary
	if (collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = collidable1;
		collidable1 = collidable2;
		collidable2 = this->tempCollidableHolder;
	}
	// Enemies are moved out of the way of players
	collidable2->setPosition(DirectX::XMFLOAT3(
		collidable2->getPosition().x - (collidable2->getVelocity().x * this->stepper),
		collidable2->getPosition().y - (collidable2->getVelocity().y * this->stepper),
		collidable2->getPosition().z - (collidable2->getVelocity().z * this->stepper))
	);

	return;
}

void PhysicsComponent::collisionPlayerDoodad(
	GameObject* collidable1,
	GameObject* collidable2) {

	// Swapping places of collidables with eachother if necessary
	// collidable1 = PLAYER
	if (collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = collidable1;
		collidable1 = collidable2;
		collidable2 = this->tempCollidableHolder;
	}

	return;
}

void PhysicsComponent::collisionPlayerIndestruct(
	GameObject* collidable1,
	GameObject* collidable2) {

	// Swapping places of collidables with eachother if necessary
	// collidable1 = PLAYER
	if (collidable1->getType() != OBJECTTYPE::PLAYER) {
		this->tempCollidableHolder = collidable1;
		collidable1 = collidable2;
		collidable2 = this->tempCollidableHolder;
	}

	collidable1->setPosition

	return;
}

void PhysicsComponent::collisionPlayerProjectile(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionEnemyEnemy(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionEnemyDoodad(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionEnemyIndestruct(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionEnemyProjectile(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionDoodadDoodad(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionDoodadIndestruct(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionDoodadProjectile(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionIndestructIndestruct(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionIndestrucProjectile(
	GameObject* collidable1,
	GameObject* collidable2) {

}

void PhysicsComponent::collisionProjectileProjectile(
	GameObject* collidable1,
	GameObject* collidable2) {

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

PhysicsComponent::PhysicsComponent(GameObject& obj) : ID(obj.getID()) {
	this->selfBoundingSphere.Center = DirectX::XMFLOAT3{ 0, 0, 0 };
	this->selfBoundingSphere.Radius = 1.0f;
}

PhysicsComponent::PhysicsComponent(
	DirectX::XMFLOAT3 boundingSphereCenter,
	float radius,
	GameObject& obj) : ID(obj.getID()) {
	this->selfBoundingSphere.Center = boundingSphereCenter;
	this->selfBoundingSphere.Radius = radius;
}

PhysicsComponent::~PhysicsComponent() {

}

DirectX::BoundingSphere PhysicsComponent::getBoundingSphere() {
	return this->selfBoundingSphere;
}

bool PhysicsComponent::checkCollision(DirectX::BoundingSphere boundingSphere_in) {
	return this->selfBoundingSphere.Intersects(boundingSphere_in);
}

bool PhysicsComponent::checkCollision(DirectX::BoundingBox boundingBox_in) {
	return this->selfBoundingSphere.Intersects(boundingBox_in);
}

void PhysicsComponent::updateBoundingArea(DirectX::XMFLOAT3 centerPos) {
	this->selfBoundingSphere.Center = centerPos;
}

void PhysicsComponent::updateBoundingArea(float radius) {
	this->selfBoundingSphere.Radius = radius;
}

void PhysicsComponent::updateBoundingArea(DirectX::XMFLOAT3 centerPos, float radius) {
	this->selfBoundingSphere.Center = centerPos;
	this->selfBoundingSphere.Radius = radius;
}

void PhysicsComponent::executeCollision(GameObject* collidable1, GameObject* collidable2) {
	this->collisionID = this->createCollisionID(collidable1, collidable2);

	switch (collisionID) {
		// PLAYER <--> PLAYER
	case 1: {

	}
	}
}

const size_t PhysicsComponent::getID() {
	return this->ID;
}

void PhysicsComponent::receive(GameObject & obj, Message msg) {
	// Switch case that depends on the message being received
}

//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                             PHYSICS COMPONENT           \
////////////////////////////////////////////////////////////