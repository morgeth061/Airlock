#pragma once
#ifndef __MINERALS__
#define __MINERALS__

#include "GameObject.h"
#include "TextureManager.h"

class Minerals : public GameObject {
public:
	Minerals();
	~Minerals();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
private:
	//void m_checkBounds();

	void m_reset();
};

#endif /* defined (__MINERALS__) */