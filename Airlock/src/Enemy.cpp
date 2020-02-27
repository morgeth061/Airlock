#include "Enemy.h"
#include "Game.h"
#include "Util.h"
#include "GLM/gtx/rotate_vector.hpp"
#include "Engine.h"


Enemy::Enemy()
{
	Texture::Instance()->load("../Assets/textures/enemy1.png",
		"Enemy", TheGame::Instance()->getRenderer());

	levelPtr = Level::Instance()->getLevel();
	levelArray = *levelPtr;

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
	m_steerForce = 0.1f;

	// set up health, name, and attack damage (PLEASE CHANGE ONCE DETAILS ARE FINALIZED)
	setEnemyHealth(100);
	setEnemyName("Fairies");
	setEnemyAtkDmg(20);
	setEnemyDeath(false);
}


Enemy::~Enemy()
{
}

void Enemy::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	Texture::Instance()->draw("Enemy", xComponent, yComponent, TheGame::Instance()->getRenderer(), m_currentDirection, 255, true);
}

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
	}
}

void Enemy::update()
{
	m_checkState();
}

void Enemy::clean()
{
}

void Enemy::turnRight()
{

}

void Enemy::turnLeft()
{
}

void Enemy::m_move()
{
	glm::vec2 newPosition = getPosition() + getVelocity() * m_maxSpeed;
	int newX = (getPosition().x + getVelocity().x) / 64;
	int newY = (getPosition().y + getVelocity().y) / 64;

	//cout << endl << "got here" << endl;
	if (levelArray[(newPosition.y + 12) / 64][newX] == 1 || levelArray[newY][(newPosition.x + 4) / 64] == 1 || levelArray[newY][(newPosition.x - 4) / 64] == 1)
	{
		//cout << endl << "a" << endl;
		newPosition = getPosition();
	}
	setPosition(newPosition);
}

glm::vec2 Enemy::getTarget()
{
	return m_target;
}

float Enemy::getMaxSpeed()
{
	return m_maxSpeed;
}



void Enemy::setMaxSpeed(float newMaxSpeed)
{
	m_maxSpeed = newMaxSpeed;
}

void Enemy::setTarget(glm::vec2 newTarget)
{
	m_target = newTarget;
}

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

void Enemy::m_reset()
{
	setEnemyHealth(100);
	setPosition(getEnemySpawn());
	setSteeringState(IDLE);
	setIsColliding(false);
}


void Enemy::m_seek()
{

	glm::vec2 steeringVelocity = m_target - getPosition();
	steeringVelocity = Util::normalize(steeringVelocity);

	setVelocity(steeringVelocity);
}


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
int Enemy::getEnemyHealth()
{
	return m_enemyHealth;
}

string Enemy::getEnemyName()
{
	return m_enemyName;
}

int Enemy::getEnemyAtkDmg()
{
	return m_enemyAtkDmg;
}
bool Enemy::getEnemyDeath()
{
	return m_enemyDeath;
}

glm::vec2 Enemy::getEnemySpawn()
{
	return m_enemySpawnPoint;
}

void Enemy::setEnemyHealth(int health)
{
	m_enemyHealth = health;
}
void Enemy::setEnemyName(string name)
{
	m_enemyName = name;
}
void Enemy::setEnemyAtkDmg(int damage)
{
	m_enemyAtkDmg = damage;
}

void Enemy::setEnemyDeath(bool death)
{
	m_enemyDeath = death;
}

void Enemy::setEnemySpawn(glm::vec2 spawn)
{
	m_enemySpawnPoint = spawn;
}

