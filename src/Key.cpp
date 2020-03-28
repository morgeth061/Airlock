/* 
KEY Class
Deals with all Key functionality
*/


#include "Key.h"
#include "Game.h"
#include "Engine.h"

//Key Ctor
Key::Key()
{
	Texture::Instance()->load("../Assets/textures/ChestKey.png", "chestKey", Game::Instance()->getRenderer());
	// Chest Key Init
	glm::vec2 size = Texture::Instance()->getTextureSize("chestKey");
	setWidth(size.x);
	setHeight(size.y);
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setIsHit(false);
	setIsActive(true);
	setType(GameObjectType::CHEST_KEY);
}

//Key De-Ctor
Key::~Key()
{
}

// Key Draw to Buffer
void Key::draw()
{
	if(m_pIsActive == true)
	{
		int xComponent = getPosition().x;
		int yComponent = getPosition().y;
		Texture::Instance()->draw("chestKey", xComponent, yComponent,
			Game::Instance()->getRenderer(), true);
		//cout << "DRAW KEY" << (getPosition().x)/64 << " " << (getPosition().y) / 64 << endl;
	}
}

// Key Update
void Key::update()
{
}

// Key Clean on Exit
void Key::clean()
{
}

// Key Spawnpoint Setter
void Key::setSpawnPoint(glm::vec2 spawn)
{
	m_keySpawnPoint = spawn;
}

// Key is Active Setter
void Key::setIsActive(bool active)
{
	m_pIsActive = active;
}

// Key Spawnpoint Getter
glm::vec2 Key::getSpawnPoint()
{
	return m_keySpawnPoint;
}
// Key is Active Getter
bool Key::getIsActive()
{
	return m_pIsActive;
}
// Key Reset
void Key::m_reset()
{
	setIsColliding(false);
	setIsHit(false);
	setPosition(m_keySpawnPoint);
}
