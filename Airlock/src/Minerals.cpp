/**
Minerals class
Author: Sojung (Serena) Lee
Date: Jan/31/2020
Description:
	- Added minerals class
	- created mineral object
	- placed mineral (Quartz1.png) into game state (screen)
	- Based on Enemy class
	- changed minerals icon (quartz) to larger resolution
Minerals class
Author: Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	- Added hit functions & set to false
**/

#include "Minerals.h"
#include "Game.h"
#include "Engine.h"

Minerals::Minerals()
{
	Texture::Instance()->load("../Assets/textures/Quartz1.png",
		"minerals", TheGame::Instance()->getRenderer());

	glm::vec2 size = Texture::Instance()->getTextureSize("minerals");
	setWidth(size.x);
	setHeight(size.y);
	//setPosition(glm::vec2(192.0f, 96.0f)); //changes original position
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setIsHit(false);
	setType(GameObjectType::MINERALS);
}

Minerals::~Minerals()
{
}

void Minerals::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	Texture::Instance()->draw("minerals", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), true);
}

void Minerals::update()
{
	
}

void Minerals::clean()
{
}

void Minerals::setSpawnPoint(glm::vec2 spawn)
{
	m_mineralSpawnPoint = spawn;
}

glm::vec2 Minerals::getSpawnPoint()
{
	return m_mineralSpawnPoint;
}


void Minerals::m_reset()
{
	setIsColliding(false);
	setIsHit(false);
	setPosition(m_mineralSpawnPoint);
	cout << getIsColliding() << " " << getIsHit() << endl;
}
