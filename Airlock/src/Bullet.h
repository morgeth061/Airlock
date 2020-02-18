#pragma once
#ifndef __BULLET__
#define __BULLET__

#include <iostream>
#include "GameObject.h"
#include "Engine.h"
#include "GameObject.h"

using namespace std;

class Bullet : public GameObject
{
public:
	bool active = true;
	SDL_Rect m_dst;
	static const int speed = 1;
	bool headRight;

public:
	Bullet(int x, int y);
	~Bullet();
	void update();
	void render();
	void clean();
	int bulletDamage;
	int getBulletDamage();
	void setBulletDamage(int);
private:
	
};




#endif
