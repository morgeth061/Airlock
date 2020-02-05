#pragma once
#ifndef __Enemy__
#define __Enemy__

#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"

#include <string>

using namespace std;

class Enemy : public GameObject
{
private:
	int m_enemyHealth();
	string m_enemyName();
	double enemyAtkDmg();

	void m_checkState();
	void m_checkBounds();

	void m_reset();
	void m_checkArrival();

	// steering behaviours
	void m_seek();
	float m_maxSpeed;
	double m_currentDirection;
	float m_turnSpeed;
	float m_steerForce;
	glm::vec2 m_target;
public:
	Enemy();
	~Enemy();

	Level levelSelect;
	array_type levelArray;

	// Inherited via GameObject
	void draw() override;

	void update() override;

	void clean() override;

	void turnRight();
	void turnLeft();
	void m_move();

	//getters
	glm::vec2 getTarget();
	float getMaxSpeed();

	//setters
	void setTarget(glm::vec2 newTarget);
	void setMaxSpeed(float newMaxSpeed);

};
#endif // defined (__Enemy__)
