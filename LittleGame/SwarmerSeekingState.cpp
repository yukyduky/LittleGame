#include "SwarmerSeekingState.h"
#include "AIComponent.h"
#include "EnemyObject.h"
#include "ActorObject.h"
#include "SwarmerState.h"
#include "IncludeSpells.h"

SwarmerSeekingState::SwarmerSeekingState(
	EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID
) : SwarmerState(pHead, pBrain, pGrid_, swarmerID)
{
	// Activate this state
	this->pBrain->pushState(*this);
}

void SwarmerSeekingState::executeBehavior()
{
	XMFLOAT3 playerPos = (*this->pHead->getPlayers())[0]->GETPosition();
	XMFLOAT3 myPosition = this->pHead->GETPosition();
	XMFLOAT3 directionToPlayer;
	XMVECTOR tempMath;

	/// Always initially aim towards the player
	directionToPlayer.x = playerPos.x - myPosition.x;
	directionToPlayer.y = playerPos.y - myPosition.y;
	directionToPlayer.z = playerPos.z - myPosition.z;

	// Normalize the lookingDirection now since it's not affected by anything else.
	tempMath = DirectX::XMLoadFloat3(&directionToPlayer);
	tempMath = DirectX::XMVector3Normalize(tempMath);
	DirectX::XMStoreFloat3(&directionToPlayer, tempMath);

	// CosSin-ify the lookingDirection for an adjusted firing angle.

	// ---- NEW ----
	// seekPosition += getNeighboursAvgPos();
	// newDirection += wander();
	// newDirection += avoidPlayer();
	// newDirection += this->grid->avoidWalls();
	// newDirection = seekPosition.normalize();

	/// DIFFERENT MOTIVATORS FOR MOVEMENT
	std::vector<EnemyObject*> neighbours = this->getNeighbours();
	int neighbourCount = neighbours.size();
	XMFLOAT3 averageDirection =		{ 0, 0, 0 };
	XMFLOAT3 avoidDirection =		{ 0, 0, 0 };
	XMFLOAT3 wanderDirection =		{ 0, 0, 0 };
	XMFLOAT3 newDirection =			{ 0, 0, 0 };
	XMFLOAT3 antiWallDirection =	{ 0, 0, 0 };

	//// Neighbours (If we have any)
	if (neighbourCount > 1) {
		// Affect spellCooldown
		this->pHead->getFirstSpell()->setCoolDown(this->getOriginalSpellCooldown() / neighbourCount);

		// Affect velocity
		this->pHead->setVelocity(this->getOriginalVelocity() * neighbourCount);

		// Affect how fast we pulse
	//	this->setPulseInterval(this->getOriginalPulseInterval() * neighbourCount);
	}
	else {
		// Reset if we have to
		this->pHead->getFirstSpell()->setCoolDown(this->getOriginalSpellCooldown());
		this->pHead->setVelocity(this->getOriginalVelocity());
		//this->setPulseInterval(this->getOriginalPulseInterval());
	}

	// Look for the average of all swarmers
	averageDirection = this->getDirectionToSeek();
	newDirection.x += averageDirection.x * 2;
	newDirection.y += averageDirection.y * 2;
	newDirection.z += averageDirection.z * 2;
	
	// Wander
	wanderDirection = this->wander();
	newDirection.x += wanderDirection.x * 150;
	newDirection.y += wanderDirection.y * 150;
	newDirection.z += wanderDirection.z * 150;

	// Fear of the player
	avoidDirection = this->avoidPlayer();
	newDirection.x += avoidDirection.x * 5;
	newDirection.y += avoidDirection.y * 5;
	newDirection.z += avoidDirection.z * 5;

	// Avoidance of walls
	antiWallDirection = this->avoidWalls();
	if (antiWallDirection.x != 0 ||
		antiWallDirection.y != 0 ||
		antiWallDirection.z != 0
		) {
		int test = 3;
	}
	newDirection.x += antiWallDirection.x * 300;
	newDirection.y += antiWallDirection.y * 300;
	newDirection.z += antiWallDirection.z * 300;

	// Normalize all of the added vectors
	XMVECTOR vecDirection = DirectX::XMLoadFloat3(&newDirection);
	vecDirection = DirectX::XMVector3Normalize(vecDirection);
	DirectX::XMStoreFloat3(&newDirection, vecDirection);

	/// Cossinify the direction we fire.
	float angle = Locator::getRandomGenerator()->GenerateInt(0, 90) - 45;
	angle = angle * XM_PI / 180;
	XMFLOAT3 upVec = { 0, 1, 0 };
	XMVECTOR rotation = DirectX::XMLoadFloat3(&upVec);
	tempMath = DirectX::XMLoadFloat3(&directionToPlayer);
	rotation = DirectX::XMQuaternionRotationAxis(rotation, angle);
	tempMath = DirectX::XMVector3Rotate(tempMath, rotation);
	DirectX::XMStoreFloat3(&directionToPlayer, tempMath);

	/// Set SimulatedMovement & Direction
	if (this->timeToPulse) {
		this->timeToPulse = false;
		this->pBrain->SETsimulatedMovement(XMFLOAT2(newDirection.x, newDirection.z));	
	}
	this->pHead->setDirection(directionToPlayer);
	
	// Adjust velocity based on pulsing
	this->pulse();

	// Move!
	this->pBrain->pushCommand(AICOMMANDS::MOVE);
	// Cooldown is checked internally | This unit has unlimited attackrange

	this->pBrain->pushCommand(AICOMMANDS::ATTACK);
}