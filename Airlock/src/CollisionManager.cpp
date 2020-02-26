#include "CollisionManager.h"
#include "Game.h"

int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheck(GameObject * object1, GameObject * object2, float distance)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (object1->getHeight() + object2->getHeight()) * distance;

	if (distance > 0.25)
	{
		if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
			if (!object2->getIsColliding()) {

				object2->setIsColliding(true);

				switch (object2->getType()) {
				case BULLET:
					break;
				case ENEMY:
					break;
				default:
					std::cout << "Collision with unknown type!" << std::endl;
					break;
				}

				return true;
			}
			return false;
		}
	}
	else if (distance <= 0.25)
	{
		if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
			if (!object2->getIsHit()) {

				object2->setIsHit(true);

				switch (object2->getType()) {

				case BULLET:
					std::cout << "Bullets" << std::endl;
				case MINERALS:
					std::cout << "Minerals gone" << std::endl;
					TheGame::Instance()->objectPickUp();
					break;
				case ENEMY:
					std::cout << "ENEMY gone" << std::endl;
					TheGame::Instance()->enemyAttack();
					break;
				default:
					std::cout << "Collision with unknown type!" << std::endl;
					break;
				}

				return true;
			}
			return false;
		}
	}
	
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
