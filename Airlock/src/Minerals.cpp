/**
Minerals class
Author: Sojung (Serena) Lee
Date: Jan/31/2020
Description:
	- Added minerals class
	- created mineral object
	- placed mineral (Quartz1.png) into game state (screen)
	- Based on Enemy class
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
	setPosition(glm::vec2(192.0f, 96.0f)); //changes original position
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
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
	//m_move();
	//m_checkBounds();
	//clean();
}

void Minerals::clean()
{
}


void Minerals::m_reset()
{
	setIsColliding(false);
}