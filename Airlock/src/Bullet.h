#pragma once
#ifndef __BULLET__
#define __BULLET__

#include <iostream>
#include "GameObject.h"
#include "Engine.h"

using namespace std;

class Bullet : public GameObject
{
public:
	bool active = true;
	SDL_Rect m_dst;
	static const int speed = 1;
	bool headRight;


	int m_bulletDmg;

public:
	Bullet(SDL_Rect s, SDL_Rect d, int spd);
	~Bullet();
	void update();
	void render();
	void clean();
	void draw() override;

	void setBulletDmg(int);
	int getBulletDmg();

};

#endif
