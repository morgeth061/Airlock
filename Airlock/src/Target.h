#pragma once
#ifndef __Target__
#define __Target__

#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"

class Target : public GameObject {
public:
	Target();
	~Target();

	Level m_levelSelect;
	array_type* m_levelPtr;
	array_type m_levelArray;

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	virtual void animate();
	virtual void SetIdle();

	void setPlayerHealth(int);
	void setPlayerName(string);
	void setPlayerAtkDmg(int);
	void setPlayerDeath(bool);

	void m_playerKilled();

	int getPlayerHealth();
	string getPlayerName();
	int getPlayerAtkDmg();
	bool getPlayerStatus();

protected:
	int m_iSprite = 0,	// Which sprite to display for animation.
		m_iSpriteMax,	// How many sprites total.
		m_iFrame = 0,	// Frame counter.
		m_iFrameMax;	// Number of frames per sprite.
	SDL_Rect m_rSrc;	// Rectangle for source pixels.
	SDL_FRect m_rDst;	// Rectangle for destination window.

	const static int Size;

private:
	void m_move();

	void m_checkBounds();

	void m_reset();

	string m_playerName;
	int m_playerHealth;
	int m_playerAtkDmg;

	bool m_playerDeath;
};

#endif /* defined (__Target__) */