/*
 * GAME CLASS
 * - Runs game, selects level based off of FSM, etc...
 */

//Includes
#include "Game.h"

//Defines
#define FPS 60

const int numofEnemies = 3;
const int numofMinerals = 2;

//Singleton
Game* Game::s_pInstance = 0;

//Returns player position
glm::vec2 Game::getTargetPosition()
{
	return m_pTarget->getPosition();
}

//Returns renderer
SDL_Renderer* Game::getRenderer()
{
	return m_pRenderer;
}

//ctor.
Game::Game()
{
	bulletFrame = 0;
	bulletFrameMax = 120;
}

//de-ctor.
Game::~Game()
{
}

//Creates Game Objects
void Game::createGameObjects()
{

	//**********
	//LEVEL 1
	//**********
	
	//Creates enemies for Level 1
	for (int count = 0; count < numofEnemies; count++)
	{
		m_pEnemy.push_back(new Enemy());
	}

	m_pEnemy[0]->setEnemySpawn(glm::vec2(384.0f, 320.0f));
	m_pEnemy[1]->setEnemySpawn(glm::vec2(960.0f, 480.0f));
	m_pEnemy[2]->setEnemySpawn(glm::vec2(1472.0f, 640.0f));

	for (auto enemies : m_pEnemy)
	{
		enemies->setPosition(enemies->getEnemySpawn());
	}

	//Creates minerals for Level 1
	for (int count = 0; count < numofMinerals; count++)
	{
		m_pMinerals.push_back(new Minerals);
	}

	m_pMinerals[0]->setSpawnPoint(glm::vec2(384.0f, 192.0f));
	m_pMinerals[1]->setSpawnPoint(glm::vec2(1472.0f, 832.0f));

	for (auto minerals : m_pMinerals)
	{
		minerals->setPosition(minerals->getSpawnPoint());
	}

	//Set Speed for Enemies
	m_pEnemy[0]->setMaxSpeed(0.40f);
	m_pEnemy[1]->setMaxSpeed(0.50f);
	m_pEnemy[2]->setMaxSpeed(0.60f);

	//Creates player
	m_pTarget = new Target();

	for (auto bullets : BullVec)
	{
		bullets->setBulletDmg(25);
	}
	//BullVec.push_back(new Bullet(Game::Instance()->getTargetPosition().x, Game::Instance()->getTargetPosition().y));
}

//Game Initialization
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

//Render game objects
void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	//**********
	//LEVEL 1
	//**********
	
	Texture::Instance()->draw("Level1", 0, 0, TheGame::Instance()->getRenderer(), false);

	//Draw player
	m_pTarget->draw();

	//Draw Bullets
	for (int i = 0; i < BullVec.size(); i++)
		BullVec[i]->render();

	//Draw Enemies
	for (auto enemies : m_pEnemy)
		enemies->draw();

	//Draw Minerals
	for (auto minerals : m_pMinerals)
		minerals->draw();

	//Draw to the screen
	SDL_RenderPresent(m_pRenderer);
}

//Update function for the game
void Game::update()
{
	//Check for enemy/player collision
	for (auto enemies : m_pEnemy)
	{
		Collision::squaredRadiusCheck(m_pTarget, enemies, 0.25f);
		Collision::squaredRadiusCheck(m_pTarget, enemies, 1.0f);
		enemies->update();
	}

	//Check for mineral/player collision
	for (auto minerals : m_pMinerals)
	{
		if (Collision::squaredRadiusCheck(m_pTarget, minerals, 0.25f))
		{
			//m_pMinerals[count]->update();
		}
	}

	//Check for bullet/enemy collision
	for (int count = 0; count < numofEnemies; count++)
	{
		//Collision::squaredRadiusCheckObjects(BullVec, m_pEnemy[count]);
	}
	
	m_pTarget->update();

	//Check if bullet needs to be de-spawned
	for (int i = 0; i < BullVec.size(); i++)
	{
		BullVec[i]->update();
		//if (BullVec[i]->active == false)
		//{
		//	delete BullVec[i];
		//	BullVec[i] = nullptr;
		//}

	}
	collide();
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
	if (!m_pEnemy.empty() && m_bENull == true)
	{
		m_pEnemy.erase(remove(m_pEnemy.begin(), m_pEnemy.end(), nullptr), m_pEnemy.end());
		m_pEnemy.shrink_to_fit();
		m_bENull = false;
	}

	//player death/respawn
	if(m_pTarget->getPlayerStatus() == true)
	{
		m_pTarget->m_reset();

		for (auto enemies : m_pEnemy)
		{
			if (enemies->getEnemyDeath() == true)
			{
				enemies->setEnemyDeath(false);
			}
			
			enemies->m_reset();
		}

		for (auto minerals : m_pMinerals)
		{
			minerals->m_reset();
		}
	}
}

//Clean game on exit
void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

//Enemy attack function -> Reduces player health
void Game::enemyAttack()
{
	for (auto enemies : m_pEnemy)
	{
		if (enemies->getIsHit() == true)
		{
			// if player collides with enemies, player's health depletes a certain amount (enemy's attack damage)
			m_pTarget->setPlayerHealth(m_pTarget->getPlayerHealth() - enemies->getEnemyAtkDmg());
			cout << "LOST: " << m_pTarget->getPlayerName() << " = Health: " << m_pTarget->getPlayerHealth() << endl;
			//cout << "\nEnemy " << count << " = getIsHit()->" << m_pEnemy[count]->getIsHit() << endl;
			m_pTarget->m_playerKilled();
		}
	}
}

//Player picks up object
void Game::objectPickUp()
{
	for (auto minerals : m_pMinerals)
	{
		if (Collision::squaredRadiusCheck(m_pTarget, minerals, 0.25f))
		{
			//testing player's health functions (will remove in future updates)
			m_pTarget->setPlayerHealth(m_pTarget->getPlayerHealth() + 50);
			cout << "GAINED: " << m_pTarget->getPlayerName() << " = Health: " << m_pTarget->getPlayerHealth() << endl;

		}
	}
}

//Enemy attack function -> Reduces player health
void Game::playerAttack()
{
	//for (int count = 0; count < numofEnemies; count++)
	//{
	//	if (m_pEnemy[count]->getIsHit() == true && BullVec->getIsHit() == true)
	//	{
	//		// if player collides with enemies, player's health depletes a certain amount (enemy's attack damage)
	//		m_pEnemy[count]->setEnemyHealth(m_pEnemy[count]->getEnemyHealth() - BullVec->getBulletDmg());
	//		cout << "LOST: " << m_pEnemy[count]->getEnemyName() << " = Health: " <<m_pEnemy[count]->getEnemyHealth() << endl;
	//		cout << "\nEnemy " << count << " = getIsHit()->" << m_pEnemy[count]->getIsHit() << endl;
	//		cout << "\nBullet " << count << " = getIsHit()->" << BullVec->getIsHit() << endl;
	//		//m_pTarget->m_playerKilled();
	//	}
	//}
}

void Game::collide()
{
	for (int i = 0; i < (int)BullVec.size(); i++)
	{
		SDL_Rect b = { BullVec[i]->m_dst.x, BullVec[i]->m_dst.y,10,10 };
		for (int j = 0; j < (int)m_pEnemy.size(); j++)
		{
			if (m_pEnemy[j] == nullptr) continue;
			SDL_Rect e = { m_pEnemy[j]->getPosition().x, m_pEnemy[j]->getPosition().y, 64, 64 };
			if (SDL_HasIntersection(&b, &e))
			{

				m_pEnemy[j]->setEnemyHealth(m_pEnemy[j]->getEnemyHealth() - BullVec[i]->getBulletDmg());
				cout << "Enemy HP = " << m_pEnemy[j]->getEnemyHealth() << endl;
				delete BullVec[i];
				BullVec[i] = nullptr;
				if (m_pEnemy[j]->getEnemyHealth() <= 0)
				{
					m_bENull = true;
					delete m_pEnemy[j];
					m_pEnemy[j] = nullptr;
				}
				break;
			}
		}
	}
}

//Checks for keyboard/mouse input
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

//Handle Keyboard/Mouse Input, Collision, etc...
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
				for (auto enemies : m_pEnemy)
				{
					enemies->setSteeringState(SteeringState::SEEK);
					enemies->setTarget(m_pTarget->getPosition());
				}
				break;
			case SDLK_2:
				m_pTarget->setPlayerDeath(true);
				break;
			case SDLK_RIGHT:
				for (auto enemies : m_pEnemy)
				{
					enemies->turnRight();
				}
				break;
			case SDLK_LEFT:
				for (auto enemies : m_pEnemy)
				{
					enemies->turnLeft();
				}
				break;
			case SDLK_SPACE:

				if (bulletFrame == bulletFrameMax)
				{
					BullVec.push_back(new Bullet({0,0,10,10}, {(int)m_pTarget->getPosition().x,(int)m_pTarget->getPosition().y,10,10 }, 30));
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
			for (auto enemies : m_pEnemy)
			{
				if (enemies->getIsColliding() == true)
				{
					enemies->setSteeringState(SteeringState::SEEK);
					enemies->setTarget(m_pTarget->getPosition());
				}
				if (enemies->getIsHit() == true && CollisionManager::squaredRadiusCheck(m_pTarget, enemies,0.25f))
				{
					enemies->setIsHit(false);
				}
			}

			//If minerals collide with player.... what happens (add inventory?)
			for (auto minerals : m_pMinerals)
			{
				//minerals disappear too slowly
				//if (m_pMinerals[count]->getIsHit() == true && CollisionManager::squaredRadiusCheckObjects(m_pTarget, m_pMinerals[count])) 
				//{
				//	m_pMinerals[count]->setPosition(glm::vec2(2000.0f, 2000.0f));
				//}
				
				//issue: enemies can 'steal' object (which shouldn't happen)
				if (minerals->getIsHit() == true)
				{
					minerals->setPosition(glm::vec2(2000.0f, 2000.0f));
				}
			}


			break;
		}
	}
}