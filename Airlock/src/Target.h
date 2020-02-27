#pragma once
#ifndef __Target__
#define __Target__

#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"

class Target : public GameObject {
public:
	//Ctor.
	Target();
	//De-Ctor.
	~Target();

	//Level Attributes
	array_type* m_levelPtr;
	array_type m_levelArray;

	//Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	//Animation Methods
	virtual void animate();
	virtual void SetIdle();

	//Setters
	void setPlayerHealth(int);
	void setInvIndex(short);
	void setPlayerName(string);
	void setPlayerAtkDmg(int);
	void setPlayerDeath(bool);
	void setPlayerSpawn(glm::vec2);

	//Checker for Player Death
	void m_playerKilled();

	//Getters
	int getPlayerHealth();
	short getInvIndex();
	string getPlayerName();
	int getPlayerAtkDmg();
	bool getPlayerStatus();
	glm::vec2 getPlayerSpawn();

	//Reset Method
	void m_reset();

protected:
	//Animation Methods
	int m_iSprite = 0,	// Which sprite to display for animation.
		m_iSpriteMax,	// How many sprites total.
		m_iFrame = 0,	// Frame counter.
		m_iFrameMax;	// Number of frames per sprite.
	SDL_Rect m_rSrc;	// Rectangle for source pixels.
	SDL_FRect m_rDst;	// Rectangle for destination window.

	const static int Size;

private:
	//Private Methods
	void m_move();
	void m_checkBounds();

	//Game Instance

	//Private Attributes
	int m_playerHealth;
	short m_invIndex;
	string m_playerName;
	int m_playerAtkDmg;
	glm::vec2 m_playerSpawn;
	bool m_playerDeath;
};

#endif /* defined (__Target__) */