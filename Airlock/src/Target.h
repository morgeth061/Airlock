#pragma once
#ifndef __Target__
#define __Target__

#include "GameObject.h"
#include "TextureManager.h"
#include "level.h"

class Target : public GameObject {
public:
	Target();
	~Target();

	Level levelSelect;
	array_type levelArray;

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
private:
	void m_move();

	void m_checkBounds();

	void m_reset();
};

#endif /* defined (__Target__) */