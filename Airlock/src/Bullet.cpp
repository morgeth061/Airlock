/*Bullet Class
Fisayo Akinsulire
Date: Feb/10/2020
Descripton:
		-Added Bullet functionalitly

*/


#include "Bullet.h"
#include "Engine.h"
#include "Game.h"
#include"GameObjectType.h"

<<<<<<< Updated upstream

<<<<<<< Updated upstream




=======
#define WIDTH 1024
>>>>>>> Stashed changes
=======

#define WIDTH 1024
>>>>>>> Stashed changes
Bullet::Bullet(int x, int y)
{
	m_dst = { x - 2, y - 2 , 4,4 };
	if (Game::Instance()->m_pTarget->getFlip() == SDL_FLIP_HORIZONTAL)
		headRight = true;
	else
		headRight = false;

<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
=======
>>>>>>> Stashed changes
	setBulletDamage(25);
	
	setType(GameObjectType::BULLET);
	
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	if (headRight)
		m_dst.x += speed;
	else
		m_dst.x -= speed;
	if (m_dst.x > WIDTH)
		active = false;


}

void Bullet::render()
{
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &m_dst);

}

int Bullet::getBulletDamage()
{
	return bulletDamage;
}

void Bullet::setBulletDamage(int damage)
{
	bulletDamage = damage;
}

int Bullet::getBulletDamage()
{
	return bulletDamage;
}

void Bullet::setBulletDamage(int damage)
{
	bulletDamage = damage;
}

