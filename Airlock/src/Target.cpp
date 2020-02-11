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
Author: Ryan Ethier
Date: Feb/08/2020
Description:
	- Changed Level Class Implementation to use pointers
Author:Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	 - added Hit get & set functions (bool)
	 - added get & set functions for name, damage, and health
**/

#include "Target.h"
#include "Game.h"
#include "Engine.h"
#include "Level.h"
#include "GameObjectType.h"

const int Target::Size = 7;

Target::Target()
{
	Texture::Instance()->load("../Assets/textures/Player_SMG_Walking_Sheet.png", "player", TheGame::Instance()->getRenderer());
	m_iSprite = 0;
	m_iSpriteMax = 0;
	m_iFrame = 0;
	m_iFrameMax = 4;


	//generates level & collision
	m_levelSelect = Level();
	m_levelPtr = m_levelSelect.getLevel();
	m_levelArray = *m_levelPtr;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			cout << &m_levelArray[i][j];
		}
		cout << endl;
	}

	glm::vec2 size = Texture::Instance()->getTextureSize("player");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(384.0f, 768.0f)); //changes original position
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::TARGET);
	setFlip(SDL_FLIP_HORIZONTAL);
	SetIdle();
	int inventory[Size];

	// set up health, name, and attack damage
	setPlayerName("Astro");
	setPlayerHealth(250);
	setPlayerAtkDmg(50);
	setPlayerDeath(false);

}

Target::~Target()
{
}

void Target::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	//Texture::Instance()->draw("player", xComponent, yComponent, TheGame::Instance()->getRenderer(), true);
	Texture::Instance()->drawFrame("player", xComponent-64, yComponent-64, 128, 128, 1, m_iFrame, TheGame::Instance()->getRenderer(), getFlip());
}


void Target::animate()
{

	m_iFrame++;
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprite++;
		if (m_iSprite == m_iSpriteMax)
			m_iSprite = 0;
		m_rSrc.x = m_rSrc.w * static_cast<int>((SDL_GetTicks() / 500) % m_iFrameMax);
	}

}

void Target::SetIdle()
{
	m_rSrc.y = 0;
	m_iFrame = 0;
	m_iSprite = 0;
}



void Target::update()
{
	//this->animate();
	//m_rSrc.x = (m_rSrc.w * m_iSprite); // Update animation.
	//m_rSrc.x = m_rSrc.w * static_cast<int>((SDL_GetTicks() / 500) % m_iFrameMax);

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

	array_type currentArray = m_levelArray;

	//checks if new coordinates are ground the player can walk on


	glm::vec2 newPosition = getPosition() + getVelocity() * 0.9f;

	if (currentArray[newY][newX] == 0)
	{
		if ((currentArray[(getPosition().y + getVelocity().y + 32) / 64][newX] == 1) || (currentArray[newY][(getPosition().x + getVelocity().x + 8) / 64] == 1) || (currentArray[newY][(getPosition().x + getVelocity().x - 8) / 64] == 1))
		{
			newPosition = getPosition();
		}
		setPosition(newPosition);
	}
	else if (currentArray[newY][newX] == 1)
	{
		newPosition = getPosition();
		setPosition(newPosition);
	}
	else if (currentArray[newY][newX] == 3)
	{
		newPosition = getPosition() + getVelocity() * 0.9f;
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

void Target::setPlayerHealth(int health)
{
	m_playerHealth = health;
}

void Target::setPlayerName(string name)
{
	m_playerName = name;
}

void Target::setPlayerAtkDmg(int damage)
{
	m_playerAtkDmg = damage;
}

void Target::setPlayerDeath(bool death)
{
	m_playerDeath = death;
}

void Target::m_playerKilled()
{
	if (m_playerHealth <= 0)
	{
		m_playerDeath = true;
		cout << "player died" << endl;
		exit(EXIT_SUCCESS);
	}
}

int Target::getPlayerHealth()
{
	return m_playerHealth;
}

string Target::getPlayerName()
{
	return m_playerName;
}

int Target::getPlayerAtkDmg()
{
	return m_playerAtkDmg;
}

bool Target::getPlayerStatus()
{
	return m_playerDeath;
}


