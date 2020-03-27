#pragma once
#ifndef __CHEST__
#define __CHEST__
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Minerals.h"

class Chest : public GameObject
{
public:
	Chest();
	~Chest();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	//Setters
	void setSpawnPoint(glm::vec2);
	void setIsActive(bool);
	void setIsOpen(bool);

	//Getters
	glm::vec2 getSpawnPoint();
	bool getIsActive();
	bool getIsOpen();

	//Public Methods
	void m_reset();
	void m_openChest();

private:

	bool m_pIsActive;
	glm::vec2 m_pChestSpawnPoint;

	//private attributes

	Minerals* m_pChestContent;

	bool m_pIsOpen;

};
#endif /* defined (__CHEST__)*/
