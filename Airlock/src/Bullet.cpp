#include <iostream>
#include<vector>
#include<algorithm>
#include "Bullet.h"
#include "Engine.h"
#include "Game.h"
#define WIDTH 1024

Bullet::Bullet(SDL_Rect s, SDL_Rect d, int spd)
{
	setType(GameObjectType::BULLET);
	setIsColliding(false);
	setIsHit(false);
	setBulletDmg(25);
	m_dst = { d.x , d.y , 4,4 };
	if (Game::Instance()->m_pTarget->getFlip() == SDL_FLIP_HORIZONTAL)
		headRight = true;
	else
		headRight = false;
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
	if (m_dst.x > TheGame::Instance()->getTargetPosition().x + 150 || m_dst.x < TheGame::Instance()->getTargetPosition().x - 150)
	{
		active = false;
	}
}

void Bullet::render()
{
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &m_dst);	   
}

void Bullet::clean()
{
}

void Bullet::draw()
{
}

void Bullet::setBulletDmg(int damage)
{
	m_bulletDmg = damage;
}

int Bullet::getBulletDmg()
{
	return m_bulletDmg;
}

