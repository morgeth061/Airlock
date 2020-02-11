/**
Collision Manager class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Definitions for Collision Manager
	- Adapted from GBC GAME3001 Template v3
	- Checks collision box around game object --> using squaredRadiusCheck
		- if object is colliding with .... (switch statement) CASE: ______
		- e.g.) if target/player (object) is colliding with.... (switch statement) CASE: ENEMY,
					then cout << "ENEMY COLLISION" 
Author: Sojung (Serena) Lee
Date: Jan/31/2020
Description:
	- Added squareRadiansCheckObjects (for minerals or other game items only) --> has different (Smaller) radius than enemies
Author: Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	- Added ENEMY GameObjectType to squareRadiansCheckObjects (when enemy hits player through smaller radius)
		- smaller radius = enemy decreases player's health
		- larger radius = enemy seeks player
**/

#include "CollisionManager.h"
#include "Game.h"

#include "GameObject.h"


int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheck(GameObject * object1, GameObject * object2)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (object1->getHeight() + object2->getHeight()) * 1;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case BULLET:
				break;
			case ENEMY:
				//std::cout << "ENEMY COLLISION" << std::endl;
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
bool CollisionManager::squaredRadiusCheckObjects(GameObject* object1, GameObject* object2)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	float halfHeights = (object1->getHeight() + object2->getHeight()) * 0.2;
	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		if (!object2->getIsHit()) {

			object2->setIsHit(true);

			switch (object2->getType()) {

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

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
