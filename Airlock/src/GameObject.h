#pragma once
#ifndef __GameObject__
#define __GameObject__

#include <glm\vec2.hpp>
#include <string>
#include <SDL.h>

#include "GameObjectType.h"
#include "SteeringState.h"

class GameObject {
public:
	GameObject();
	~GameObject();

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	glm::vec2 getPosition();
	glm::vec2 getRotation();
	glm::vec2 getScale();
	glm::vec2 getVelocity();
	glm::vec2 getAcceleration();
	int getWidth();
	int getHeight();
	bool getIsColliding();
	bool getIsHit();
	GameObjectType getType();
	SteeringState getSteeringState();
	SDL_RendererFlip getFlip();

	// setters for common variables
	void setPosition(glm::vec2 newPosition);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setVelocity(glm::vec2 newVelocity);
	void setIsColliding(bool collision);
	void setIsHit(bool hit);
	void setType(GameObjectType newType);
	void setSteeringState(SteeringState newState);
	void setAcceleration(glm::vec2 newAcceleration);
	void setFlip(SDL_RendererFlip flipType);


private:
	// transform variables
	glm::vec2 m_position;
	glm::vec2 m_rotation;
	glm::vec2 m_scale;


	// movement variables
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	// size variables
	int m_width;
	int m_height;

	// animation variables
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	std::string m_textureID;
	SDL_RendererFlip m_flipType;

	// collision variables
	bool m_isColliding;
	bool m_isHit;
	GameObjectType m_type;
	SteeringState m_state;
};

#endif