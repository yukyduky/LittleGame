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
	this->selfBoundingSphere.Center = obj.getPosition();
	this->selfBoundingSphere.Radius = 1.0f;
}

PhysicsComponent::PhysicsComponent(GameObject& obj, float boundingSphereRadius) : ID(obj.getID()) {
	this->selfBoundingSphere.Center = obj.getPosition();
	this->selfBoundingSphere.Radius = boundingSphereRadius;
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

const size_t PhysicsComponent::getID() {
	return this->ID;
}

void PhysicsComponent::receive(GameObject & obj, Message msg) {
	// Switch case that depends on the message being received
}

void PhysicsComponent::update()
{

}

void PhysicsComponent::cleanUp() {

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