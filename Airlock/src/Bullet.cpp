#include <iostream>
#include<vector>
#include<algorithm>
#include "Bullet.h"
#include "Engine.h"
#include "Game.h"
#define WIDTH 1024

Bullet::Bullet(int x, int y)
{
	Texture::Instance()->load("../Assets/textures/bullet.png", "bullet", TheGame::Instance()->getRenderer());

	setType(GameObjectType::BULLET);
	setIsColliding(false);
	setIsHit(false);
	setBulletDmg(25);
	setPosition(glm::vec2(-2000, -2000));
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
	if (m_dst.x > TheGame::Instance()->getTargetPosition().x+150 || m_dst.x < TheGame::Instance()->getTargetPosition().x - 150)
		active = false;
}

void Bullet::render()
{
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &m_dst);
	//Texture::Instance()->draw("bullet", TheGame::Instance()->getTargetPosition().x, TheGame::Instance()->getTargetPosition().y, TheGame::Instance()->getRenderer(),  255, true);
	   
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

