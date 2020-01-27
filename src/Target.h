#pragma once
#ifndef __Target__
#define __Target__

#include "GameObject.h"
#include "TextureManager.h"

class Target : public GameObject {
public:
	Target();
	~Target();

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