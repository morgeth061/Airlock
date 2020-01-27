/**
Enemy class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Definitions for Enemy methods
	- Adapted from GBC GAME3001 Template v4 (using "ship.cpp")
	- Creates enemy constructor
	- Defines enemy draw, render, checkState, update, clean, move, max speed, check bounds, seek, check arrival functions
	- Draws enemies (using Assets)
	- MAkes enemy stay within boundaries --> using checkBounds function
		- e.g.) If enemy reaches negative Y axis, then set y axis = 0
**/

#include "Enemy.h"
#include "Game.h"
#include "Util.h"
#include "GLM/gtx/rotate_vector.hpp"


Enemy::Enemy()
{
	Texture::Instance()->load("../Assets/textures/enemy1.png",
		"Enemy", TheGame::Instance()->getRenderer());

	glm::vec2 size = Texture::Instance()->getTextureSize("Enemy");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	//m_reset();
	setIsColliding(false);
	setType(GameObjectType::ENEMY);
	setSteeringState(SteeringState::IDLE);
	m_maxSpeed = 1.0f;
	m_currentDirection = 0.0;
	m_turnSpeed = 2.0f;
	m_steerForce = 0.1f;

	//Texture::Instance()->setColour("Enemy", 255, 255, 0);
}


Enemy::~Enemy()
{
}

void Enemy::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	Texture::Instance()->draw("Enemy", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), m_currentDirection, 255, true);
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
	if (getPosition().x > 1920)
	{
		setPosition(glm::vec2(1920.0f, getPosition().y));
	}

	if (getPosition().x < 0)
	{
		setPosition(glm::vec2(5.0f, getPosition().y));
	}

	if (getPosition().y > 1080)
	{
		setPosition(glm::vec2(getPosition().x, 1080.0f));
	}

	if (getPosition().y < 0)
	{
		setPosition(glm::vec2(getPosition().x, 5.0f));
	}

}

void Enemy::m_reset()
{
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
		if (Util::distance(getPosition(), m_target) <= 2.0f)
		{
			setSteeringState(IDLE);
		}
	}
}