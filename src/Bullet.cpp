/*
BULLET class
- deals with player bullet functionality
*/

#include <iostream>
#include<vector>
#include<algorithm>
#include "Bullet.h"
#include "Engine.h"
#include "Game.h"
#include <Windows.h>
#define WIDTH 1024


// Bullet Ctor
Bullet::Bullet(SDL_Rect s, SDL_Rect d, int spd)
{
	setType(GameObjectType::BULLET);
	setIsColliding(false);
	setIsHit(false);
	setBulletDmg(25);
	m_dst = { d.x , d.y , 4,4 };
	//Makes sure Bullets shoots the way the player is looking
	if (Game::Instance()->m_pTarget->getFlip() == SDL_FLIP_HORIZONTAL)
		headRight = true;
	else if (Game::Instance()->m_pTarget->getFlip() == SDL_FLIP_NONE)
		headRight = false;
	else if (Game::Instance()->m_pTarget->up == true)
		up = true;
}

// Bullet De-Ctor
Bullet::~Bullet()
{
}
// Bullet Update
void Bullet::update()
{
	if (Game::Instance()->m_pTarget->up == true)
	{ 
		m_dst.y -= speed;
		//m_dst.x = Game::Instance()->m_pTarget->getPosition().x;
	}
	else if (Game::Instance()->m_pTarget->bottom == true)
	{
		m_dst.y += speed;
		//m_dst.x = Game::Instance()->m_pTarget->getPosition().x;
	}
	else if (headRight)
	{
		m_dst.x += speed;
		//m_dst.y = Game::Instance()->m_pTarget->getPosition().y;
	}
	else
	{
		m_dst.x -= speed;
		//m_dst.y = Game::Instance()->m_pTarget->getPosition().y;
	}
	if (m_dst.x > TheGame::Instance()->getTargetPosition().x + 150 || m_dst.x < TheGame::Instance()->getTargetPosition().x - 150 || m_dst.y < TheGame::Instance()->getTargetPosition().y - 150)
	{
		active = false;
	}
}
// Bullet Render
void Bullet::render()
{
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &m_dst);	   
}
// Clean on Exit
void Bullet::clean()
{
}

void Bullet::draw()
{
}

//Bullet Damage 
void Bullet::setBulletDmg(int damage)
{
	m_bulletDmg = damage;
}
int Bullet::getBulletDmg()
{
	return m_bulletDmg;
}