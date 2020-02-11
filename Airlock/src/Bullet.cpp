/*Bullet Class
Fisayo Akinsulire
Date: Feb/10/2020
Descripton:
		-Added Bullet functionalitly

*/

#include <iostream>
#include<vector>
#include<algorithm>
#include "Bullet.h"
#include "Engine.h"
#include "Game.h"
#define WIDTH 1024





Bullet::Bullet(int x, int y)
{
	m_dst = { x - 2, y - 2 , 4,4 };
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
	if (m_dst.x > WIDTH)
		active = false;


}

void Bullet::render()
{
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &m_dst);

}

