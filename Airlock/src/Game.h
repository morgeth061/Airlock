
#pragma once
#ifndef __Game__
#define __Game__

// Core Libraries
#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

// Game Managers
#include "TextureManager.h"
#include "CollisionManager.h"

// Game Objects
#include "Enemy.h"
#include "Target.h"
#include "Minerals.h"
#include "Bullet.h"

class Game
{
public:

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	// simply set the running variable to true
	void init() { m_bRunning = true; }

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	// public functions
	void render();
	void update();
	void handleEvents();
	void clean();

	// a function to access the private running variable
	bool running() { return m_bRunning; }

	glm::vec2 getTargetPosition();

	// getters
	SDL_Renderer* getRenderer();
	Enemy* m_pEnemy[3];
	Target* m_pTarget;
	Minerals* m_pMinerals[2];
	Bullet* m_pBullet;

	bool KeyDown(SDL_Scancode c);
private:
	Game();
	~Game();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	vector<Bullet*> BullVec;

	int m_currentFrame;
	int bulletFrame;
	int bulletFrameMax;

	bool m_bRunning;

	static Game* s_pInstance;

	void createGameObjects();

	glm::vec2 m_mousePosition;

	const Uint8* m_iKeystates; // Keyboard state container.
};

typedef Game TheGame;

#endif /* defined (__Game__) */

