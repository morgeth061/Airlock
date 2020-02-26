#pragma once
#ifndef __Game__
#define __Game__

// Core Libraries
#include <iostream>
#include <vector>

//SDL Libraries
#include <SDL.h>

// Game Managers
#include "CollisionManager.h"

// Game Objects
#include "Enemy.h"
#include "Target.h"
#include "Minerals.h"
#include "Bullet.h"

class Game
{
public:

	//Singleton
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	//Init method
	void init()
	{
		//Simply set the running variable to true
		m_bRunning = true;
	}
	
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	//Public Methods
	void render();
	void update();
	void handleEvents();
	void clean();

	//Public Game Methods
	void enemyAttack();
	void objectPickUp();

	bool running()
	{
		return m_bRunning;
	}

	//Getters
	SDL_Renderer* getRenderer();
	glm::vec2 getTargetPosition();
	int getTargetHealth();

	//Game Objects
	Enemy* m_pEnemy[3];
	Target* m_pTarget;
	Minerals* m_pMinerals[2];
	Bullet* m_pBullet;

	//Keystate Method
	bool KeyDown(SDL_Scancode c);
	
private:
	//Ctor.
	Game();
	//De-Ctor.
	~Game();

	//SDL Objects
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	//Bullet Vector
	vector<Bullet*> BullVec;
	int bulletFrame;
	int bulletFrameMax;
	int m_currentFrame;

	//Engine
	bool m_bRunning;

	//Singleton
	static Game* s_pInstance;

	//Mouse/Keyboard States
	glm::vec2 m_mousePosition;
	const Uint8* m_iKeystates;

	//Private Methods
	void createGameObjects();
};

typedef Game TheGame;

#endif /* defined (__Game__) */

