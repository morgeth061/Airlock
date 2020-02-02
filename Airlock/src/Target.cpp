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
Author: Ryan Ethier
Date: Jan/31/2020
Description:
	- Added Level Class implementation
Author: Sojung (Serena) Lee
Date: Feb/1/2020
Description:
	- Changed player's sprite, original position, boundaries, and speed
**/

#include "Target.h"
#include "Game.h"
#include "Engine.h"
#include "Level.h"
#include "GameObjectType.h"

Target::Target()
{
	Texture::Instance()->load("../Assets/textures/player.png",
		"circle", TheGame::Instance()->getRenderer());

	//generates level & collision
	levelSelect = Level();
	levelArray = levelSelect.getLevel();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			cout << levelArray[i][j];
		}
		cout << endl;
	}

	glm::vec2 size = Texture::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(384.0f, 768.0f)); //changes original position
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
	//integers representing the new X and Y coordinates.
	int newX = (getPosition().x + getVelocity().x) / 64;
	int newY = (getPosition().y + getVelocity().y) / 64;

	//checks if new coordinates are ground the player can walk on

	cout << newY << " " << newX << " " << levelArray[newY][newX] << endl;

	if (levelArray[newY][newX] == 0)
	{
		glm::vec2 newPosition = getPosition() + getVelocity() * 0.9f;
		setPosition(newPosition);
	}
	else if (levelArray[newY][newX] == 3)
	{
		glm::vec2 newPosition = getPosition() + getVelocity() * 0.9f;
		setPosition(newPosition);
		Engine::Instance().SetGameWon();
	}
}

void Target::m_checkBounds()
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

void Target::m_reset()
{
	setIsColliding(false);
}
