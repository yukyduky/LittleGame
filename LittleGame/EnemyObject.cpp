#include "EnemyObject.h"
#include "Locator.h"

EnemyObject::EnemyObject(const size_t ID, float speed, XMFLOAT3 pos, XMFLOAT3 velocity, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType)
	: ActorObject(ID, speed, pos, velocity, pGPS, objectType)
{

}

void EnemyObject::update()
{
	switch (this->state) {
		case OBJECTSTATE::TYPE::ATTACKING: {

			Locator::getGameTime()->getDeltaTime();

			


			break;
		}
		case OBJECTSTATE::TYPE::MOVING: {

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