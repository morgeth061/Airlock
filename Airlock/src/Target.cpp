/**
Target class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Target means Player (same thing, but different title)
	- Definitions for Target methods
	- Adapted from GBC GAME3001 Template v4 (using "target.cpp")
	- Creates Target constructor
	- Defines Target draw, render, checkState, update, clean, move, check bounds functions
	- Able to change speed --> using m_move
	- Able to change their boundaries (move within certain area) --> using checkBounds
**/

#include "Target.h"
#include "Game.h"

Target::Target()
{
	Texture::Instance()->load("../Assets/textures/Circle.png",
		"circle", TheGame::Instance()->getRenderer());

	glm::vec2 size = Texture::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(600.0f, 1000.0f)); //changes original position
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::TARGET);
}

Target::~Target()
{
}

void Target::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	Texture::Instance()->draw("circle", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), true);
}

void Target::update()
{
	m_move();
	m_checkBounds();

}

void Target::clean()
{
}

void Target::m_move()
{
	glm::vec2 newPosition = getPosition() + getVelocity() * 1.0f;
	setPosition(newPosition);
}

void Target::m_checkBounds()
{

	if (getPosition().x > 1920)
	{
		setPosition(glm::vec2(1920.0f, getPosition().y));
	}

	if (getPosition().x < 0)
	{
		setPosition(glm::vec2(0.0f, getPosition().y));
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

void Target::m_reset()
{
	setIsColliding(false);
}
