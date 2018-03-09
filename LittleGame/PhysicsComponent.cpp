#include "PhysicsComponent.h"
#include "GameObject.h"
#include <SimpleMath.h>
#include <DirectXMath.h>
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
	this->pHead = &obj;
	obj.SETphysicsComponent(this);
	obj.addComponent(this);
	XMFLOAT3 testPos = obj.GETPosition();
	testPos.y = 40.0f;
	this->selfBoundingSphere.Center = testPos;
	this->selfBoundingSphere.Radius = 1.0f;
}

PhysicsComponent::PhysicsComponent(GameObject& obj, float boundingSphereRadius) : ID(obj.getID()) {
	this->pHead = &obj;
	obj.SETphysicsComponent(this);
	obj.addComponent(this);
	XMFLOAT3 testPos = obj.GETPosition();
	testPos.y = 40.0f;

	this->selfBoundingSphere.Center = testPos;
	this->selfBoundingSphere.Radius = boundingSphereRadius;
}

PhysicsComponent::~PhysicsComponent() {

}

bool PhysicsComponent::checkCollision(DirectX::BoundingSphere boundingSphere_in) {
	bool returnValue = false;

	float totalRadius = boundingSphere_in.Radius + this->selfBoundingSphere.Radius;
	XMFLOAT3 dist = boundingSphere_in.Center;
	XMFLOAT3 dist2 = this->selfBoundingSphere.Center;
	dist.x = dist.x - dist2.x;
	dist.y = dist.y - dist2.y;
	dist.z = dist.z - dist2.z;
	
	XMVECTOR dist3 = XMLoadFloat3(&dist);
	dist3 = XMVector3Length(dist3);
	XMStoreFloat3(&dist, dist3);

	if (dist.x < totalRadius) {
		returnValue = true;
	}
	//return this->selfBoundingSphere.Intersects(boundingSphere_in);
	/*
	
	returnValue = this->selfBoundingSphere.Intersects(boundingSphere_in);

	if (returnValue == false)
		returnValue = this->selfBoundingSphere.Contains(boundingSphere_in);
	*/
	return returnValue;
}

bool PhysicsComponent::checkCollision(DirectX::BoundingBox boundingBox_in) {
	return this->selfBoundingSphere.Intersects(boundingBox_in);
}

void PhysicsComponent::updateBoundingArea(DirectX::XMFLOAT3 centerPos) {
	XMFLOAT3 testPos = centerPos;
	testPos.y = 40.0f;

	this->selfBoundingSphere.Center = testPos;
}


void PhysicsComponent::updateBoundingArea(float radius) {
	this->selfBoundingSphere.Radius = radius;
}

void PhysicsComponent::updateBoundingArea(DirectX::XMFLOAT3 centerPos, float radius) {
	XMFLOAT3 testPos = centerPos;
	testPos.y = 40.0f;

	this->selfBoundingSphere.Center = testPos;
	this->selfBoundingSphere.Radius = radius;
}

GameObject* PhysicsComponent::GETpHead() {
	return this->pHead;
}

DirectX::BoundingSphere PhysicsComponent::GETBoundingSphere() 
{
	return this->selfBoundingSphere;
}

const size_t PhysicsComponent::getID()
{
	return this->ID;
}

void PhysicsComponent::receive(GameObject & obj, Message msg)
{
	// Switch case that depends on the message being received
}

void PhysicsComponent::update()
{
	this->updateBoundingArea(this->pHead->GETPosition());
}

void PhysicsComponent::cleanUp() 
{
	this->pHead = nullptr;
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