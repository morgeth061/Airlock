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
Author: Sojung (Serena) Lee
Date: Jan/31/2020
Description:
	- Added minerals (createGameObjects, render, update handleEvents) with Robert's Updated Assets
	- handleEvents : Collision detection (e.g. what happens if player collides with minerals? enemies?)
Author: Sojung (Serena) Lee
Date: Feb/1/2020
Description:
	- changed enemy speed
	- updated handleEvents (ESC button -> added exit code)
Author: Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	- Added objectPickUp (when player picks mineral, health is added) TEST FUNCTION
		- Once inventory is added, replace adding health to adding inventory function
	- Added enemyAttack (when player hits enemy, health is decreased)
	- handleEvents -> default -> enemy's hit bool is set to false
Author : Fisayo Akinsulire
Date: Feb/11/2020
Description:
	- Added bullets(render, update, handleEvents)
	- Added timer to the bullets so they couldnt be spammed
Author:Sojung (Serena) Lee
Date: Feb/16/2020
Description:
	 - slowed enemy speed for easier ranged combat
**/

#include "Game.h"
#include "Util.h"
#define FPS 60

const int numofEnemies = 3;
const int numofMinerals = 2;

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
	bulletFrame = 0;
	bulletFrameMax = 120;
}

Game::~Game()
{
}

void Game::createGameObjects()
{

	for (int count = 0; count < numofEnemies; count++)
		m_pEnemy[count] = new Enemy();

	for (int count = 0; count < numofMinerals; count++)
	{
		m_pMinerals[count] = new Minerals();
	}

	m_pMinerals[0]->setPosition(glm::vec2(384.0f, 192.0f));
	m_pMinerals[1]->setPosition(glm::vec2(1472.0f, 832.0f));

	m_pEnemy[0]->setPosition(glm::vec2(384.0f, 320.0f));
	m_pEnemy[1]->setPosition(glm::vec2(960.0f, 480.0f));
	m_pEnemy[2]->setPosition(glm::vec2(1472.0f, 640.0f));
	m_pEnemy[0]->setMaxSpeed(0.40f);
	m_pEnemy[1]->setMaxSpeed(0.50f);
	m_pEnemy[2]->setMaxSpeed(0.60f);

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

	/*m_pBullet->render();*/

/*SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);*/
	for (int i = 0; i < BullVec.size(); i++)
		BullVec[i]->render();

	for (int count = 0; count < numofEnemies; count++)
		m_pEnemy[count]->draw();

	for (int count = 0; count < numofMinerals; count++)
		m_pMinerals[count]->draw();

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{

	for (int count = 0; count < numofEnemies; count++)
	{
		Collision::squaredRadiusCheckObjects(m_pTarget, m_pEnemy[count]);
		Collision::squaredRadiusCheck(m_pTarget, m_pEnemy[count]);
		m_pEnemy[count]->update();
	}
	for (int count = 0; count < numofMinerals; count++)
	{
		if (Collision::squaredRadiusCheckObjects(m_pTarget, m_pMinerals[count]))
		{
			//m_pMinerals[count]->update();
		}
	}
	m_pTarget->update();
	for (int i = 0; i < BullVec.size(); i++)
	{
		BullVec[i]->update();
		if (BullVec[i]->active == false)
		{
			delete BullVec[i];
			BullVec[i] = nullptr;
		}
	}
	if (!BullVec.empty())
	{
		BullVec.erase(remove(BullVec.begin(), BullVec.end(), nullptr), BullVec.end());
		BullVec.shrink_to_fit();
	}
	bulletFrame++;
	if (bulletFrame >= bulletFrameMax)
	{
		bulletFrame = bulletFrameMax;
	}
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::enemyAttack()
{
	for (int count = 0; count < numofEnemies; count++)
	{
		if (m_pEnemy[count]->getIsHit() == true)
		{
			// if player collides with enemies, player's health depletes a certain amount (enemy's attack damage)
			m_pTarget->setPlayerHealth(m_pTarget->getPlayerHealth() - m_pEnemy[count]->getEnemyAtkDmg());
			cout << "LOST: " << m_pTarget->getPlayerName() << " = Health: " << m_pTarget->getPlayerHealth() << endl;
			//cout << "\nEnemy " << count << " = getIsHit()->" << m_pEnemy[count]->getIsHit() << endl;
			m_pTarget->m_playerKilled();
		}
	}
}

void Game::objectPickUp()
{
	for (int count = 0; count < numofMinerals; count++)
	{
		if (Collision::squaredRadiusCheckObjects(m_pTarget, m_pMinerals[count]))
		{
			//testing player's health functions (will remove in future updates)
			m_pTarget->setPlayerHealth(m_pTarget->getPlayerHealth() + 50);
			cout << "GAINED: " << m_pTarget->getPlayerName() << " = Health: " << m_pTarget->getPlayerHealth() << endl;

		}
	}
}

bool Game::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
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
				clean();
				exit(EXIT_SUCCESS);
				break;
			case SDLK_w:
				m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, -1.0f));
				break;
			case SDLK_s:
				m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 1.0f));
				break;
			case SDLK_a:
				m_pTarget->setVelocity(glm::vec2(-1.0f, m_pTarget->getVelocity().y));
				m_pTarget->setFlip(SDL_FLIP_NONE);
				break;
			case SDLK_d:
				m_pTarget->setVelocity(glm::vec2(1.0f, m_pTarget->getVelocity().y));
				m_pTarget->setFlip(SDL_FLIP_HORIZONTAL);
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
			case SDLK_SPACE:
				if (bulletFrame == bulletFrameMax)
				{
					BullVec.push_back(new Bullet(Game::Instance()->getTargetPosition().x, Game::Instance()->getTargetPosition().y));
					bulletFrame = 0;
				}
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_w:

				if (m_pTarget->getVelocity().y < 0.0f) {
					m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 0.0f));
					m_pTarget->SetIdle();
				}
				break;
			case SDLK_s:

				if (m_pTarget->getVelocity().y > 0.0f) {
					m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 0.0f));
					m_pTarget->SetIdle();
				}
				break;
			case SDLK_a:

				if (m_pTarget->getVelocity().x < 0.0f) {
					m_pTarget->setVelocity(glm::vec2(0.0f, m_pTarget->getVelocity().y));
					m_pTarget->SetIdle();
				}
				break;
			case SDLK_d:

				if (m_pTarget->getVelocity().x > 0.0f) {
					m_pTarget->setVelocity(glm::vec2(0.0f, m_pTarget->getVelocity().y));
					m_pTarget->SetIdle();
				}
				break;
			}
		default:
			m_pTarget->animate();
			//If enemy collide with player... what happens?			
			for (int count = 0; count < numofEnemies; count++)
			{
				if (m_pEnemy[count]->getIsColliding() == true)
				{
					m_pEnemy[count]->setSteeringState(SteeringState::SEEK);
					m_pEnemy[count]->setTarget(m_pTarget->getPosition());
				}
				if (m_pEnemy[count]->getIsHit() == true && CollisionManager::squaredRadiusCheckObjects(m_pTarget, m_pEnemy[count]))
				{
					m_pEnemy[count]->setIsHit(false);
				}
			}

			//If minerals collide with player.... what happens (add inventory?)
			for (int count = 0; count < numofMinerals; count++)
			{
				//minerals disappear too slowly
				//if (m_pMinerals[count]->getIsHit() == true && CollisionManager::squaredRadiusCheckObjects(m_pTarget, m_pMinerals[count])) 
				//{
				//	m_pMinerals[count]->setPosition(glm::vec2(2000.0f, 2000.0f));
				//}
				
				//issue: enemies can 'steal' object (which shouldn't happen)
				if (m_pMinerals[count]->getIsHit() == true)
				{
					m_pMinerals[count]->setPosition(glm::vec2(2000.0f, 2000.0f));
				}
			}


			break;
		}
	}
}