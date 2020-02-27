#pragma once
#ifndef __Game__
#define __Game__

// Core Libraries
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

//SDL Libraries
#include <SDL.h>

// Game Managers
#include "CollisionManager.h"

//Enums
#include "LevelNumber.h"

// Game Objects
#include "Level.h"
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

	// checks if enemy vector is null
	bool m_bENull; 


	//Public Game Methods
	void enemyAttack();
	void objectPickUp();
	void playerAttack();
	void levelChange(int);

	bool running()
	{
		return m_bRunning;
	}

	//Setters
	void setCurrentLevel(int);
	
	//Getters
	SDL_Renderer* getRenderer();
	glm::vec2 getTargetPosition();
	int getTargetHealth();
	int getCurrentLevel();

	//Game Objects
	Target* m_pTarget;
	vector <Enemy*> m_pEnemy;
	vector <Minerals*> m_pMinerals;
	
	Level* levelPtr;

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

	//Private variables
	int m_currentLevel;
	bool isLoading;

	//Private Methods
	void createGameObjects();
	void deleteGameObjects();
};

typedef Game TheGame;

#endif /* defined (__Game__) */

