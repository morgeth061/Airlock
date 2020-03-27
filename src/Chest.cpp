#include "Chest.h"
#include "Game.h"
#include "Engine.h"

Chest::Chest()
{
	Texture::Instance()->load("../Assets/textures/Chest_Closed.png", "chestClosed", Game::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/Chest_Open.png", "chestOpen", Game::Instance()->getRenderer());
	// Chest Key Init
	glm::vec2 size = Texture::Instance()->getTextureSize("chestClosed");
	setWidth(size.x);
	setHeight(size.y);
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setIsHit(false);
	setIsActive(true);
	setType(GameObjectType::CHEST);
}

Chest::~Chest()
{
}

void Chest::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	if(m_pIsOpen)
	{
		Texture::Instance()->draw("chestOpen", xComponent, yComponent, Game::Instance()->getRenderer(), true);
	}
	else
	{
		Texture::Instance()->draw("chestClosed", xComponent, yComponent, Game::Instance()->getRenderer(), true);
	}
}

void Chest::update()
{
}

void Chest::clean()
{
}

void Chest::setSpawnPoint(glm::vec2 spawn)
{
	m_pChestSpawnPoint = spawn;
}

void Chest::setIsActive(bool active)
{
	m_pIsActive = active;
}

glm::vec2 Chest::getSpawnPoint()
{
	return m_pChestSpawnPoint;
}

bool Chest::getIsActive()
{
	return m_pIsActive;
}

void Chest::m_reset()
{
	setIsColliding(false);
	setIsHit(false);
	setIsOpen(false);
	setPosition(m_pChestSpawnPoint);
}

void Chest::m_openChest()
{
	if(getIsOpen() == false)
	{
		setIsOpen(true);
	}
}

void Chest::setIsOpen(bool open)
{
	m_pIsOpen = open;
}

bool Chest::getIsOpen()
{
	return m_pIsOpen;
}
