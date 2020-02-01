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
#include "Engine.h"

/*Array represents grid-based game map with a width of 29 cells and a height of 15 cells.
0 -> Ground, will be walked on by player during regular play
1 -> Forrest, impassable
3 -> Level end/exit, will look like ground and end level*/
int level1[15][29] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					   {1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1},
					   {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
					   {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
					   {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
					   {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
					   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
					   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
					   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
					   {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
					   {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
					   {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
					   {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
					   {1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1},
					   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};


Target::Target()
{
	Texture::Instance()->load("../Assets/textures/Circle.png",
		"circle", TheGame::Instance()->getRenderer());

	glm::vec2 size = Texture::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(192.0f, 384.0f)); //changes original position
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
	int newX = (getPosition().x+getVelocity().x)/32;
	int newY = (getPosition().y + getVelocity().y)/32;

	//checks if new coordinates are ground the player can walk on
	if (level1[newY][newX]==0)
	{
		glm::vec2 newPosition = getPosition() + getVelocity() * 0.1f;
		setPosition(newPosition);
	}
	else if(level1[newY][newX]==3)
	{
		glm::vec2 newPosition = getPosition() + getVelocity() * 0.1f;
		setPosition(newPosition);
		Engine::Instance().SetGameWon();
	}
}

void Target::m_checkBounds()
{

	if (getPosition().x > 928)
	{
		setPosition(glm::vec2(928.0f, getPosition().y));
	}

	if (getPosition().x < 0)
	{
		setPosition(glm::vec2(0.0f, getPosition().y));
	}

	if (getPosition().y > 480)
	{
		setPosition(glm::vec2(getPosition().x, 480.0f));
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
