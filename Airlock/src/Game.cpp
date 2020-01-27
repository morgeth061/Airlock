/**
Game class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Definitions for Game methods
	- Created Game Objects (e.g. Array of 3 enemies, single target/player)
	- Intializes the Game window, render, update, clean
	- Setup for Player movements (handleEvents)
	- Setup Automatic SEEK state if player/target is within range (handleEvents : default)
	- Setup for Button functions
		- WASD for target/player movement
		- Default : SEEK state
		- 1 = SEEK state
**/
	
#include "Game.h"
#include "Util.h"

const int numofEnemies = 3;

Game* Game::s_pInstance = 0;

glm::vec2 Game::getTargetPosition()
{
	return m_pTarget->getPosition();
}

SDL_Renderer* Game::getRenderer()
{
	return m_pRenderer;
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::createGameObjects()
{

	for (int count = 0; count < numofEnemies; count++)
		m_pEnemy[count] = new Enemy();
	
	m_pEnemy[0]->setPosition(glm::vec2(192.0f, 160.0f));
	m_pEnemy[1]->setPosition(glm::vec2(464.0f, 240.0f));
	m_pEnemy[2]->setPosition(glm::vec2(736.0f, 320.0f));
	m_pEnemy[0]->setMaxSpeed(0.04f);
	m_pEnemy[1]->setMaxSpeed(0.05f);
	m_pEnemy[2]->setMaxSpeed(0.03f);

	m_pTarget = new Target();
}

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if window creation successful create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			//TheTextureManager::Instance()->load("../../Assets/textures/animate-alpha.png", "animate", m_pRenderer);
			createGameObjects();
		}
		else
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

	Texture::Instance()->draw("Level1", 0, 0, TheGame::Instance()->getRenderer(), false);

	m_pTarget->draw();

	for (int count = 0; count < numofEnemies; count++)
		m_pEnemy[count]->draw();

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{

	for (int count = 0; count < numofEnemies; count++)
	{
		Collision::squaredRadiusCheck(m_pTarget, m_pEnemy[count]);
		m_pEnemy[count]->update();
	}
	m_pTarget->update();

}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				m_bRunning = false;
				break;
			case SDLK_w:
				m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, -1.0f));
				break;
			case SDLK_s:
				m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 1.0f));
				break;
			case SDLK_a:
				m_pTarget->setVelocity(glm::vec2(-1.0f, m_pTarget->getVelocity().y));
				break;
			case SDLK_d:
				m_pTarget->setVelocity(glm::vec2(1.0f, m_pTarget->getVelocity().y));
				break;
			case SDLK_0:
				for (int count = 0; count < numofEnemies; count++)
				{
					m_pEnemy[count]->setSteeringState(SteeringState::IDLE);
				}
				break;
			case SDLK_1:
				for (int count = 0; count < numofEnemies; count++)
				{
					m_pEnemy[count]->setSteeringState(SteeringState::SEEK);
					m_pEnemy[count]->setTarget(m_pTarget->getPosition());
				}
				break;
			case SDLK_RIGHT:
				for (int count = 0; count < numofEnemies; count++)
				{
					m_pEnemy[count]->turnRight();
				}
				break;
			case SDLK_LEFT:
				for (int count = 0; count < numofEnemies; count++)
				{
					m_pEnemy[count]->turnLeft();
				}
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				if (m_pTarget->getVelocity().y < 0.0f) {
					m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 0.0f));
				}
				break;

			case SDLK_s:
				if (m_pTarget->getVelocity().y > 0.0f) {
					m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 0.0f));
				}
				break;

			case SDLK_a:
				if (m_pTarget->getVelocity().x < 0.0f) {
					m_pTarget->setVelocity(glm::vec2(0.0f, m_pTarget->getVelocity().y));
				}
				break;
			case SDLK_d:
				if (m_pTarget->getVelocity().x > 0.0f) {
					m_pTarget->setVelocity(glm::vec2(0.0f, m_pTarget->getVelocity().y));
				}
				break;
			}
		default:
			for (int count = 0; count < numofEnemies; count++)
			{
				if (m_pEnemy[count]->getIsColliding() == true)
				{
					m_pEnemy[count]->setSteeringState(SteeringState::SEEK);
					m_pEnemy[count]->setTarget(m_pTarget->getPosition());
				}
			}

			break;
		}
	}
}