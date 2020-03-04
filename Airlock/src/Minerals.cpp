/*
Minerals Class
-Deals with all the Mineral Functionality
*/

#include "Minerals.h"
#include "Game.h"

//Mineral Ctor
Minerals::Minerals()
{
	Texture::Instance()->load("../Assets/textures/Quartz1.png",
		"minerals", TheGame::Instance()->getRenderer());
// Mineral Init
	glm::vec2 size = Texture::Instance()->getTextureSize("minerals");
	setWidth(size.x);
	setHeight(size.y);
	//setPosition(glm::vec2(192.0f, 96.0f)); //changes original position
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setIsHit(false);
	setType(GameObjectType::MINERALS);
}
//Mineral De-Ctor
Minerals::~Minerals()
{
}
// Draw to Buffer
void Minerals::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	Texture::Instance()->draw("minerals", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), true);
}
// Mineral Update
void Minerals::update()
{
	
}
// Clean on Exit
void Minerals::clean()
{
}

//Mineral Spawnpoint Setter
void Minerals::setSpawnPoint(glm::vec2 spawn)
{
	m_mineralSpawnPoint = spawn;
}
//Mineral Spawnpoint Getter
glm::vec2 Minerals::getSpawnPoint()
{
	return m_mineralSpawnPoint;
}

// Mineral Reset
void Minerals::m_reset()
{
	setIsColliding(false);
	setIsHit(false);
	setPosition(m_mineralSpawnPoint);
	cout << getIsColliding() << " " << getIsHit() << endl;
}
