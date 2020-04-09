/*
Enemy Class
- deals with all enemy functionality
*/


#include "Enemy.h"
#include "Game.h"
#include "Util.h"
#include "GLM/gtx/rotate_vector.hpp"
#include "Engine.h"

//Enemy Ctor
Enemy::Enemy()
{
	Texture::Instance()->load("../Assets/textures/enemy1.png",
		"Enemy", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/enemyHealthBack.png",
		"HealthBack", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/enemyHealthFore.png",
		"HealthFore", TheGame::Instance()->getRenderer());

//Generates level and level collision
	levelPtr = Level::Instance()->getLevel();
	levelArray = *levelPtr;

// Enemy Init
	glm::vec2 size = Texture::Instance()->getTextureSize("Enemy");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	//m_reset();
	setIsColliding(false);
	setIsHit(false);
	setType(GameObjectType::ENEMY);
	setSteeringState(SteeringState::IDLE);
	m_maxSpeed = 1.0f;
	m_currentDirection = 0.0;
	m_turnSpeed = 2.0f;
	m_steerForce = 0.5f;

	// set up health, name, and attack damage (PLEASE CHANGE ONCE DETAILS ARE FINALIZED)
	setEnemyHealth(100);
	setEnemyName("Fairies");
	setEnemyAtkDmg(20);
	setEnemyDeath(false);
}

//Enemy De-Ctor
Enemy::~Enemy()
{
}

// Enemy draw to buffer
void Enemy::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	Texture::Instance()->draw("Enemy", xComponent, yComponent, TheGame::Instance()->getRenderer(), m_currentDirection, 255, true);
	Texture::Instance()->draw("HealthBack", xComponent - 25, yComponent - 45, 50, 5, TheGame::Instance()->getRenderer(), getFlip());
	Texture::Instance()->draw("HealthFore", xComponent - 25, yComponent - 45, getEnemyHealth() / 2, 5, TheGame::Instance()->getRenderer(), getFlip());
}

//Checks steering state of the enemy(Either seek or idle)
void Enemy::m_checkState()
{
	switch (getSteeringState())
	{
	case SteeringState::IDLE:
		break;
	case SteeringState::SEEK:
		m_seek();
		m_checkBounds();
		m_checkArrival();
		m_move();
		break;
	case SteeringState::FLEE:
		m_flee();
		m_checkBounds();
		m_checkArrival();
		m_move();
		break;
	}
}

// Enemy Update
void Enemy::update()
{
	m_checkState();
}

//Clean on Exit
void Enemy::clean()
{
}

//Enemy Right-Turn
void Enemy::turnRight()
{

}
// Enemy Left-Turn
void Enemy::turnLeft()
{
}

// Enemy Movement
void Enemy::m_move()
{
	//up or down : levelArray[(newPosition.y + 12) / 64][newX] == 1
	//side to side : levelArray[newY][(newPosition.x + 4) / 64] == 1 || levelArray[newY][(newPosition.x - 4) / 64] == 1

	glm::vec2 newPosition = getPosition() + getVelocity() * m_maxSpeed;
	int newX = (getPosition().x + getVelocity().x) / 64;
	int newY = (getPosition().y + getVelocity().y) / 64;
	float y = getPosition().y;
	float x = getPosition().x;

	if ((levelArray[(newPosition.y + 12) / 64][newX] == 0 || levelArray[newY][(newPosition.x + 4) / 64] == 0 || levelArray[newY][(newPosition.x - 4) / 64] == 0) &&
		(levelArray[((newPosition.y + 12) / 64) + 0.5][newX] == 1 || levelArray[((newPosition.y + 12) / 64) - 0.5][newX] == 1 ||
			levelArray[newY][((newPosition.x + 4) / 64) - 0.5] == 1 || levelArray[newY][((newPosition.x + 4) / 64) + 0.5] == 1 ||
			levelArray[newY][((newPosition.x - 4) / 64) - 0.5] == 1 || levelArray[newY][((newPosition.x - 4) / 64) + 0.5] == 1))
	{
		if ((levelArray[newY][(newPosition.x + 4) / 64] == 0 || levelArray[newY][(newPosition.x - 4) / 64] == 0) &&
			(levelArray[newY][((newPosition.x + 4) / 64) + 1] == 1 || levelArray[newY][((newPosition.x - 4) / 64) + 1] == 1))
		{
			if (Game::Instance()->m_pTarget->getPosition().y < getPosition().y)
			{
				y -= 0.5;
				newPosition = glm::vec2(getPosition().x, y);
			}
			else if (Game::Instance()->m_pTarget->getPosition().y > getPosition().y)
			{
				y += 0.5;
				newPosition = glm::vec2(getPosition().x, y);
			}
		}
		else if ((levelArray[newY][(newPosition.x + 4) / 64] == 0 || levelArray[newY][(newPosition.x - 4) / 64] == 0) &&
			(levelArray[newY][((newPosition.x + 4) / 64) - 1] == 1 || levelArray[newY][((newPosition.x - 4) / 64) - 1] == 1))
		{
			if (Game::Instance()->m_pTarget->getPosition().y < getPosition().y)
			{
				y -= 0.5;
				newPosition = glm::vec2(getPosition().x, y);
			}
			else if (Game::Instance()->m_pTarget->getPosition().y > getPosition().y)
			{
				y += 0.5;
				newPosition = glm::vec2(getPosition().x, y);
			}
		}

		if ((levelArray[((newPosition.y - 12) / 64)][newX] == 0 || levelArray[((newPosition.y - 12) / 64)][newX] == 0) &&
			(levelArray[((newPosition.y + 12) / 64) - 0.5][newX] == 1 || levelArray[((newPosition.y + 12) / 64) + 0.5][newX] == 1))
		{
			if (Game::Instance()->m_pTarget->getPosition().x > getPosition().x)
			{
				x += 0.5;
				newPosition = glm::vec2(x, getPosition().y);
			}
			else if (Game::Instance()->m_pTarget->getPosition().x < getPosition().x)
			{
				x -= 0.5;
				newPosition = glm::vec2(x, getPosition().y);
			}
		}
		if ((levelArray[((newPosition.y - 12) / 64)][newX] == 0 || levelArray[((newPosition.y - 12) / 64)][newX] == 0) &&
			(levelArray[((newPosition.y + 12) / 64) + 0.5][newX] == 1 || levelArray[((newPosition.y + 12) / 64) - 0.5][newX] == 1))
		{
			if (Game::Instance()->m_pTarget->getPosition().x > getPosition().x)
			{
				x += 0.5;
				newPosition = glm::vec2(x, getPosition().y);
			}
			else if (Game::Instance()->m_pTarget->getPosition().x < getPosition().x)
			{
				x -= 0.5;
				newPosition = glm::vec2(x, getPosition().y);
			}
		}
	}
	else if ((levelArray[(newPosition.y + 12) / 64][newX] == 1 || levelArray[newY][(newPosition.x + 4) / 64] == 1 || levelArray[newY][(newPosition.x - 4) / 64] == 1))
	{
		setSteeringState(FLEE);
	}
	setPosition(newPosition);
}

// Enemy Target Getter
glm::vec2 Enemy::getTarget()
{
	return m_target;
}
//Enemy Max Speed Getter
float Enemy::getMaxSpeed()
{
	return m_maxSpeed;
}
// Enemy Max Speed Setter
void Enemy::setMaxSpeed(float newMaxSpeed)
{
	m_maxSpeed = newMaxSpeed;
}
// Enemy Target Setter
void Enemy::setTarget(glm::vec2 newTarget)
{
	m_target = newTarget;
}
// Checks if Enemy is out of the window boarders
void Enemy::m_checkBounds()
{

	if (getPosition().x > 1856)
	{
		setPosition(glm::vec2(1856.0f, getPosition().y));
	}

	if (getPosition().x < 0)
	{
		setPosition(glm::vec2(5.0f, getPosition().y));
	}

	if (getPosition().y > 960)
	{
		setPosition(glm::vec2(getPosition().x, 960.0f));
	}

	if (getPosition().y < 0)
	{
		setPosition(glm::vec2(getPosition().x, 5.0f));
	}
}

// Enemy Reset
void Enemy::m_reset()
{
	setEnemyHealth(100);
	setPosition(getEnemySpawn());
	setSteeringState(IDLE);
	setIsColliding(false);
}

// Seek State for enemy
void Enemy::m_seek()
{

	glm::vec2 steeringVelocity = m_target - getPosition();
	steeringVelocity = Util::normalize(steeringVelocity);

	setVelocity(steeringVelocity);
}

// Seek State for enemy
void Enemy::m_flee()
{

	glm::vec2 steeringVelocity = getPosition() - m_target;
	steeringVelocity = Util::normalize(steeringVelocity);

	setVelocity(steeringVelocity);
}

// Checking if the Enemy is at the enemy
void Enemy::m_checkArrival()
{
	if (getSteeringState() != IDLE)
	{
		if (Util::distance(getPosition(), m_target) <= 0.0005)
		{
			setSteeringState(IDLE);
		}
	}
}
// Enemy Health Getter
int Enemy::getEnemyHealth()
{
	return m_enemyHealth;
}
// Enemy Name Getter
string Enemy::getEnemyName()
{
	return m_enemyName;
}

// Enemy Attack Damage Getter
int Enemy::getEnemyAtkDmg()
{
	return m_enemyAtkDmg;
}
// Enemy Death Getter
bool Enemy::getEnemyDeath()
{
	return m_enemyDeath;
}
// Enemy Spawnpoint Getter
glm::vec2 Enemy::getEnemySpawn()
{
	return m_enemySpawnPoint;
}
// Enemy Health Setter
void Enemy::setEnemyHealth(int health)
{
	m_enemyHealth = health;
}
// Enemy Name Setter
void Enemy::setEnemyName(string name)
{
	m_enemyName = name;
}
// Enemy Attack Damage Setter
void Enemy::setEnemyAtkDmg(int damage)
{
	m_enemyAtkDmg = damage;
}
// Enemy Death Setter
void Enemy::setEnemyDeath(bool death)
{
	m_enemyDeath = death;
}
// Enemy Spawnpoint Setter
void Enemy::setEnemySpawn(glm::vec2 spawn)
{
	m_enemySpawnPoint = spawn;
}

