/*
 * TARGET (Player) CLASS
 * - Deals with all player functions
 */
#include "Target.h"
#include "Game.h"
#include "Engine.h"
#include "Level.h"
#include "GameObjectType.h"

 //SDL Libraries
#include <SDL.h>

const int Target::Size = 7;

//Target Ctor.
Target::Target()
{
	//Animation init
	Texture::Instance()->load("../Assets/textures/Player_SMG_Walking_Sheet.png", "player", TheGame::Instance()->getRenderer());

	m_iSprite = 0;
	m_iSpriteMax = 0;
	m_iFrame = 0;
	m_iFrameMax = 4;

	//Set Player Spawn
	//DEFAULT

	//generates level & collision
	

	//Player Init
	glm::vec2 size = Texture::Instance()->getTextureSize("player");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(m_playerSpawn); //changes original position
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::TARGET);
	setFlip(SDL_FLIP_HORIZONTAL);
	SetIdle();
	m_pKeysHeld = 0;
	int inventory[Size];

	//Set up health, name, and attack damage
	setPlayerName("Astro");
	setPlayerHealth(100);
	setPlayerAtkDmg(50);
	setPlayerDeath(false);
	setInvIndex(0);
	
}

//Target De-Ctor.
Target::~Target()
{
}

//Draw to Buffer
void Target::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	Texture::Instance()->draw("playerCircle", xComponent, yComponent, Engine::Instance().GetRenderer(), true);

	if(Game::Instance()->getCurrentLevel() == LEVEL1)
	{
		Texture::Instance()->draw("Level1Walls", 0, 0, Engine::Instance().GetRenderer(), false);
	}
	else if(Game::Instance()->getCurrentLevel() == LEVEL2)
	{
		Texture::Instance()->draw("Level2Walls", 0, 0, Engine::Instance().GetRenderer(), false);
	}
	else if(Game::Instance()->getCurrentLevel() == LEVEL3)
	{
		Texture::Instance()->draw("Level3Walls", 0, 0, Engine::Instance().GetRenderer(), false);
	}
	
	Texture::Instance()->draw("playerCircleTransparent", xComponent, yComponent, Engine::Instance().GetRenderer(), true);
	Texture::Instance()->drawFrame("player", xComponent - 64, yComponent - 64, 128, 128, 1, m_iFrame, TheGame::Instance()->getRenderer(), getFlip());
}

//Animate player
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

//Idle Animation
void Target::SetIdle()
{
	m_rSrc.y = 0;
	m_iFrame = 0;
	m_iSprite = 0;
}

//Update Method
void Target::update()
{
	//this->animate();
	//m_rSrc.x = (m_rSrc.w * m_iSprite); // Update animation.
	//m_rSrc.x = m_rSrc.w * static_cast<int>((SDL_GetTicks() / 500) % m_iFrameMax);

	//cout << m_playerHealth << endl;

	//m_levelSelect.setLevel(Game::s_pInstance->getCurrentLevel());
	m_move();
	m_checkBounds();
	

}

//Clean on exit
void Target::clean()
{
}

//Move player
void Target::m_move()
{
	//integers representing the new X and Y coordinates.
	int newX = (getPosition().x + getVelocity().x) / 64;
	int newY = (getPosition().y + getVelocity().y) / 64;

	array_type currentArray = m_levelArray;

	//Checks if new coordinates are ground the player can walk on
	glm::vec2 newPosition = getPosition() + getVelocity() * 0.9f;

	//cout << currentArray[newY][newX] << endl;
	
	if (currentArray[newY][newX] == 0) //Tile is traversable
	{
		if ((currentArray[(getPosition().y + getVelocity().y + 32) / 64][newX] == 1) || (currentArray[newY][(getPosition().x + getVelocity().x + 8) / 64] == 1) || (currentArray[newY][(getPosition().x + getVelocity().x - 8) / 64] == 1))
		{
			newPosition = getPosition();
		}
		setPosition(newPosition);
	}
	else if (currentArray[newY][newX] == 1) //Tile is not traversable
	{
		newPosition = getPosition();
		setPosition(newPosition);
	}
	else if (currentArray[newY][newX] == 3) //Tile is an Exit Tile
	{
		newPosition = getPosition() + getVelocity() * 0.9f;
		setPosition(newPosition);

		if(Game::Instance()->getCurrentLevel() == LEVEL1)
		{
			Texture::Instance()->draw("WonScreen", 0, 0, TheGame::Instance()->getRenderer(), false);
			SDL_RenderPresent(Game::Instance()->getRenderer());
			this_thread::sleep_for(chrono::milliseconds(1500));
			Game::Instance()->levelChange(LEVEL2);
		}
		else if(Game::Instance()->getCurrentLevel() == LEVEL2)
		{
			Texture::Instance()->draw("WonScreen", 0, 0, TheGame::Instance()->getRenderer(), false);
			SDL_RenderPresent(Game::Instance()->getRenderer());
			this_thread::sleep_for(chrono::milliseconds(1500));
			Game::Instance()->levelChange(LEVEL3);
			//Engine::Instance().SetGameWon();
		}
		else if (Game::Instance()->getCurrentLevel() == LEVEL3)
		{
			Texture::Instance()->draw("WonScreen", 0, 0, TheGame::Instance()->getRenderer(), false);
			SDL_RenderPresent(Game::Instance()->getRenderer());
			this_thread::sleep_for(chrono::milliseconds(1500));
			Engine::Instance().SetGameWon();
		}
		else
		{
			Engine::Instance().SetGameWon();
		}
	}
}

//Check collision with Window Edges
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

//Resets player status
void Target::m_reset()
{
	setPlayerDeath(false);
	setPlayerHealth(100);
	setPosition(getPlayerSpawn());
	setIsColliding(false);
}

//Setter for player health
void Target::setPlayerHealth(int health)
{
	m_playerHealth = health;
}

//Setter for player score
void Target::setPlayerScore(int score)
{
	playerScore = score;
}

//Setter for player's inventory index
void Target::setInvIndex(short index)
{
	m_invIndex = index;
}

//Setter for player name
void Target::setPlayerName(string name)
{
	m_playerName = name;
}

//Setter for player attack damage
void Target::setPlayerAtkDmg(int damage)
{
	m_playerAtkDmg = damage;
}

//Setter for player death
void Target::setPlayerDeath(bool death)
{
	m_playerDeath = death;
}

//Setter for player spawn point
void Target::setPlayerSpawn(glm::vec2 spawn)
{
	m_playerSpawn = spawn;
}

void Target::setKeysHeld(int totalKeys)
{
	m_pKeysHeld = totalKeys;
}

//Checker for player death
void Target::m_playerKilled()
{
	if (m_playerHealth <= 0)
	{
		m_playerDeath = true;
		cout << "player died" << endl;
		//exit(EXIT_SUCCESS);
	}
}

void Target::addKey()
{
	m_pKeysHeld++;
}

//Getter for player health
int Target::getPlayerHealth()
{
	return m_playerHealth;
}

//Getter for player score
int Target::getPlayerScore()
{
	return playerScore;
}

//Getter for player's inventory index
short Target::getInvIndex()
{
	return m_invIndex;
}

//Getter for player name
string Target::getPlayerName()
{
	return m_playerName;
}

//Getter for player attack damage
int Target::getPlayerAtkDmg()
{
	return m_playerAtkDmg;
}

//Getter for player status (Alive/Dead)
bool Target::getPlayerStatus()
{
	return m_playerDeath;
}

//Getter for player spawn point
glm::vec2 Target::getPlayerSpawn()
{
	return m_playerSpawn;
}

int Target::getKeysHeld()
{
	return m_pKeysHeld;
}

void Target::updateLevel()
{
	m_levelPtr = Level::Instance()->getLevel();
	m_levelArray = *m_levelPtr;
}


