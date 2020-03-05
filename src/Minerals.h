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

	void setSpawnPoint(glm::vec2);

	glm::vec2 getSpawnPoint();

	void m_reset();
	
private:
	//void m_checkBounds();

	glm::vec2 m_mineralSpawnPoint;

	
};

#endif /* defined (__MINERALS__) */