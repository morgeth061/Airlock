#pragma once
#ifndef __KEY__
#define __KEY__
#include "GameObject.h"
#include "TextureManager.h"

class Key : public GameObject
{
public:
	Key();
	~Key();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	//Setters
	void setSpawnPoint(glm::vec2);
	void setIsActive(bool);

	//Getters
	glm::vec2 getSpawnPoint();
	bool getIsActive();

	//Public Methods
	void m_reset();

private:

	bool m_pIsActive;
	glm::vec2 m_keySpawnPoint;
	
};
#endif /* defined (__KEY__)*/