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
**/

/**
Author: Sojung (Serena) Lee
Date: Jan/31/2020
Description:
	- Added squareRadiansCheckObjects (for minerals or other game items only) --> has different (Smaller) radius than enemies
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
	int halfHeights = (object1->getHeight() + object2->getHeight()) * 2;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case BULLET:
				break;
			case ENEMY:
				std::cout << "ENEMY COLLISION" << std::endl;
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
	float halfHeights = (object1->getHeight() + object2->getHeight()) * 0.3;
	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case MINERALS:
				std::cout << "Minerals gone" << std::endl;
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
