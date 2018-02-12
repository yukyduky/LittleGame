#include "EnemyObject.h"
#include "Locator.h"
#include "CollisionHandler.h"

#define DISTANCE_FACTOR 1.4142135623730950488016887242097	// Fetched from CollisionHandler.h

void EnemyObject::updateRelationsToPlayer(XMFLOAT2 myPos, XMFLOAT2 playerPos)
{
	// This method calculates the approximate distance between two points.
	// NOTE: It does NOT use the 'sqrt()' function resulting in optimization!
	float xDiff = std::abs(playerPos.x - myPos.x);
	float yDiff = std::abs(playerPos.y - myPos.y);
	float minDiff = std::_Min_value(xDiff, yDiff);

	this->distanceToPlayer = (minDiff * DISTANCE_FACTOR);
	this->distanceToPlayer += ((xDiff - minDiff) + (yDiff - minDiff));

	this->normalizedVectorToPlayer = playerPos - myPos;
	float optimization = 1 / this->distanceToPlayer;
	this->normalizedVectorToPlayer.x *= optimization;
	this->normalizedVectorToPlayer.y *= optimization;
}



EnemyObject::EnemyObject(const size_t ID, float speed, XMFLOAT3 pos, XMFLOAT3 velocity, GamePlayState* pGPS, std::vector<ActorObject*>* players, OBJECTTYPE::TYPE objectType)
	: ActorObject(ID, speed, pos, velocity, pGPS, objectType)
{
	this->players = players;
	this->attackComponent = attackComponent;
}

void EnemyObject::SETattackComponent(EnemyAttackComponent* attackComponent)
{
	this->attackComponent = attackComponent;
}

XMFLOAT2 EnemyObject::getVectorToPlayer()
{
	return this->normalizedVectorToPlayer;
}

float EnemyObject::getDistanceToPlayer()
{
	return this->distanceToPlayer;
}

void EnemyObject::update()
{
	switch (this->state) {
		case OBJECTSTATE::TYPE::ATTACKING: {

			this->attackComponent->decreaseAttackTime();

			break;
		}
		case OBJECTSTATE::TYPE::ACTIVATED: {

			// Find out where you are in relevance to the player.
			XMFLOAT3 playerPos = (*players)[0]->GETPosition();
			this->updateRelationsToPlayer(XMFLOAT2(this->pos.x, this->pos.z), XMFLOAT2(playerPos.x, playerPos.z));


			for (auto &component : this->components) {
				component->update();
			}

			break;
		}
		default: {

			break;
		}
	}
}

void EnemyObject::attack()
{

}