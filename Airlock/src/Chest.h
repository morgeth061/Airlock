#pragma once
#ifndef __CHEST__
#define __CHEST__
#include "GameObject.h"

class Chest : public GameObject
{
public:
	Chest();
	~Chest();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	
};
#endif /* defined (__CHEST__) */
