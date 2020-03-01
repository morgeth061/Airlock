/*
 * GAME CLASS
 * - Runs game, selects level based off of FSM, etc...
 */

//Includes
#include "Game.h"
#include "Util.h"

//Defines
#define FPS 60

int numofEnemies = 3;
int numofMinerals = 2;

//Singleton
Game* Game::s_pInstance = 0;

//Returns player position
glm::vec2 Game::getTargetPosition()
{
	return m_pTarget->getPosition();
}

int Game::getCurrentLevel()
{
	return m_currentLevel;
}

void Game::setCurrentLevel(int level)
{
	m_currentLevel = level;
	Level::Instance()->setLevel(level);

	cout << "SET LEVEL TO " << level << endl;
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
	isLoading = false;
	canShoot = true;

	setCurrentLevel(LEVEL1);
	cout << "CTOR" << endl;
}

//de-ctor.
Game::~Game()
{
}

//Creates Game Objects
void Game::createGameObjects()
{

	cout << "CREATING GAME OBJECTS" << endl;

	//Creates player
	m_pTarget = new Target();

	if(getCurrentLevel() == LEVEL1)
	{
		numofEnemies = 3;
		
		//Creates enemies for Level 1
		for (int count = 0; count < numofEnemies; count++)
		{
			m_pEnemy.push_back(new Enemy());
			cout << "LEVEL 1 NEW ENEMY" << endl;
		}

		m_pEnemy[0]->setEnemySpawn(glm::vec2(384.0f, 320.0f));
		m_pEnemy[1]->setEnemySpawn(glm::vec2(960.0f, 480.0f));
		m_pEnemy[2]->setEnemySpawn(glm::vec2(1472.0f, 640.0f));

		numofMinerals = 2;
		//Creates minerals for Level 1
		for (int count = 0; count < numofMinerals; count++)
		{
			m_pMinerals.push_back(new Minerals);
		}

		m_pMinerals[0]->setSpawnPoint(glm::vec2(384.0f, 192.0f));
		m_pMinerals[1]->setSpawnPoint(glm::vec2(1472.0f, 832.0f));

		//Set Speed for Enemies
		m_pEnemy[0]->setMaxSpeed(0.40f);
		m_pEnemy[1]->setMaxSpeed(0.50f);
		m_pEnemy[2]->setMaxSpeed(0.60f);

		m_pTarget->setPlayerSpawn(glm::vec2(384.0f, 768.0f));
	}
	else if (getCurrentLevel() == LEVEL2)
	{
		numofEnemies = 4;
		
		//Creates enemies for Level 2
		for (int count = 0; count < numofEnemies; count++)
		{
			m_pEnemy.push_back(new Enemy());
			cout << "LEVEL 2 NEW ENEMY" << endl;
		}

		m_pEnemy[0]->setEnemySpawn(glm::vec2(512.0f, 768.0f));
		m_pEnemy[1]->setEnemySpawn(glm::vec2(842.0f, 512.0f));
		m_pEnemy[2]->setEnemySpawn(glm::vec2(1280.0f, 512.0f));
		m_pEnemy[3]->setEnemySpawn(glm::vec2(1728.0f, 512.0f));

		numofMinerals = 3;
		//Creates minerals for Level 2
		for (int count = 0; count < numofMinerals; count++)
		{
			m_pMinerals.push_back(new Minerals);
		}

		m_pMinerals[0]->setSpawnPoint(glm::vec2(512.0f, 256.0f));
		m_pMinerals[1]->setSpawnPoint(glm::vec2(970.0f, 768.0f));
		m_pMinerals[2]->setSpawnPoint(glm::vec2(1728.0f, 256.0f));

		//Set Speed for Enemies
		m_pEnemy[0]->setMaxSpeed(0.40f);
		m_pEnemy[1]->setMaxSpeed(0.50f);
		m_pEnemy[2]->setMaxSpeed(0.60f);
		m_pEnemy[3]->setMaxSpeed(0.60f);

		m_pTarget->setPlayerSpawn(glm::vec2(64.0f, 512.0f));
	}
	
	

	for (auto enemies : m_pEnemy)
	{
		enemies->setPosition(enemies->getEnemySpawn());
	}

	for (auto minerals : m_pMinerals)
	{
		minerals->setPosition(minerals->getSpawnPoint());
	}

	m_pTarget->setPosition(m_pTarget->getPlayerSpawn());
}

void Game::deleteGameObjects()
{
	m_pTarget = nullptr;

	if(m_pEnemy.empty() == false)
	{
		for (int count = 0; count < numofEnemies; count++)
		{
			delete Instance()->m_pEnemy[count];
			Instance()->m_pEnemy[count] = nullptr;
		}
		m_pEnemy.erase(remove(m_pEnemy.begin(), m_pEnemy.end(), nullptr), m_pEnemy.end());
		m_pEnemy.shrink_to_fit();
		numofEnemies = 0;
	}
	
	if(m_pMinerals.empty() == false)
	{
		for (int count = 0; count < numofMinerals; count++)
		{
			delete Instance()->m_pMinerals[count];
			Instance()->m_pMinerals[count] = nullptr;
		}
		m_pMinerals.erase(remove(m_pMinerals.begin(), m_pMinerals.end(), nullptr), m_pMinerals.end());
		m_pMinerals.shrink_to_fit();
		Instance()->m_pMinerals.shrink_to_fit();
		numofMinerals = 0;
	}
}

bool Game::init()
{
	m_pRenderer = Engine::Instance().GetRenderer();
	createGameObjects();
	m_bRunning = true;
	return true;
}

//Render game objects
void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	if(isLoading == true)
	{
		Texture::Instance()->draw("loadingScreen", 0, 0, TheGame::Instance()->getRenderer(), false);
	}
	else if(isLoading == false)
	{
		if (getCurrentLevel() == LEVEL1)
		{
			Texture::Instance()->draw("Level1", 0, 0, TheGame::Instance()->getRenderer(), false);
		}
		else if (getCurrentLevel() == LEVEL2)
		{
			Texture::Instance()->draw("Level2", 0, 0, TheGame::Instance()->getRenderer(), false);
		}

		//Draw Bullets
		for (int i = 0; i < BullVec.size(); i++)
			BullVec[i]->render();

		//Draw Enemies
		for (auto enemies : m_pEnemy)
			enemies->draw();

		//Draw Minerals
		for (auto minerals : m_pMinerals)
			minerals->draw();

		//Draw player
		m_pTarget->draw();
		
		//Draw Health Bar
		Texture::Instance()->draw("playerHealthBack", 0, 0, TheGame::Instance()->getRenderer(), false);
		Texture::Instance()->draw("playerHealthBar", 100, 12, m_pTarget->getPlayerHealth() * 4, 40, TheGame::Instance()->getRenderer());

		//Draw Inventory
		Texture::Instance()->draw("playerInv", 715, 875, TheGame::Instance()->getRenderer(), false);
		Texture::Instance()->draw("playerInvSelected", 715 + (64 * (m_pTarget->getInvIndex())), 875, TheGame::Instance()->getRenderer(), false);
	}

	
	


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
	
	m_pTarget->update();

	//updates bullet objects
	for (int i = 0; i < BullVec.size(); i++)
	{
		if (!BullVec.empty())
		{
			BullVec[i]->update();
			playerAttack(); //check if bullet is colliding with enemy
		}
\
		//Check if bullet needs to be de-spawned
		if (BullVec[i]->active == false && !BullVec.empty())
		{
			delete BullVec[i];
			BullVec[i] = nullptr;
			BullVec.erase(remove(BullVec.begin(), BullVec.end(), nullptr), BullVec.end());
			BullVec.shrink_to_fit();
		}
	}

	//increases bullet frames	
	bulletFrame++;
	if (bulletFrame >= bulletFrameMax)
	{
		bulletFrame = bulletFrameMax;
	}

	//check if enemy needs to be de-spawned
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
	cout << "Player Score: " << m_pTarget->getPlayerScore() << endl;
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
			m_pTarget->setPlayerHealth(100);
			m_pTarget->setPlayerScore(m_pTarget->getPlayerScore() + 500);
			cout << "GAINED: " << m_pTarget->getPlayerName() << " = Health: " << m_pTarget->getPlayerHealth() << endl;

		}
	}
}

//player bullet collision with enemy object
void Game::playerAttack()
{
	for (int i = 0; i < (int)BullVec.size(); i++)
	{
		SDL_Rect b = { BullVec[i]->m_dst.x, BullVec[i]->m_dst.y,10,10 };
		for (int j = 0; j < (int)m_pEnemy.size(); j++)
		{
			if (m_pEnemy[j] == nullptr) continue;
			SDL_Rect e = { m_pEnemy[j]->getPosition().x, m_pEnemy[j]->getPosition().y - 32, 64, 64 };
			if (SDL_HasIntersection(&b, &e))// if enemy & bullet intersect...
			{
				//bullet object deleted
				m_pEnemy[j]->setEnemyHealth(m_pEnemy[j]->getEnemyHealth() - BullVec[i]->getBulletDmg());
				//cout << "Enemy HP = " << m_pEnemy[j]->getEnemyHealth() << endl;
				BullVec[i]->active = false;
				if (m_pEnemy[j]->getEnemyHealth() <= 0)
				{
					//if enemy health <= 0, enemy objects deleted
					m_bENull = true;
					delete m_pEnemy[j];
					m_pEnemy[j] = nullptr;

					m_pTarget->setPlayerScore(m_pTarget->getPlayerScore() + 100);
				}
				break;
			}
		}

	}
	
}

void Game::levelChange(int newLevel)
{
	m_pTarget->setPlayerScore((m_pTarget->getPlayerScore()) + (m_pTarget->getPlayerHealth()));

	deleteGameObjects();
	setCurrentLevel(newLevel);
	isLoading = true;
	render();
	this_thread::sleep_for(chrono::milliseconds(1500));
	isLoading = false;
	createGameObjects();
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
			clean();
			exit(EXIT_SUCCESS);
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
			case SDLK_f:
				for (int i = 0; i < numofEnemies; i++)
				{
					//if (Collision::squaredRadiusCheckObjects(m_pTarget, m_pEnemy[i]) && Collision::squaredRadiusCheck(m_pTarget, m_pEnemy[i]))
					if(Collision::squaredRadiusCheck(m_pTarget, m_pEnemy[i], (Util::distance(m_pTarget->getPosition(), m_pEnemy[i]->getPosition()))))
					{
						m_pEnemy[i]->setEnemyHealth((m_pEnemy[i]->getEnemyHealth())-25);
						cout << "ENEMY HIT" << " " << m_pEnemy[i]->getEnemyHealth() << endl;
					}
				}
				break;
			case SDLK_UP:
				if (m_pTarget->getInvIndex() == 6) 
				{
					m_pTarget->setInvIndex(0);
				}
				else 
				{
					short ind = m_pTarget->getInvIndex();
					m_pTarget->setInvIndex(ind+1);
				}
				break;
			case SDLK_DOWN:
				if ((m_pTarget->getInvIndex() == 0))
				{
					m_pTarget->setInvIndex(6);
				}
				else
				{
					short ind = m_pTarget->getInvIndex();
					m_pTarget->setInvIndex(ind-1);
				}
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
					if (canShoot)
					{
						BullVec.push_back(new Bullet({ 0,0,10,10 }, { (int)m_pTarget->getPosition().x,(int)m_pTarget->getPosition().y,10,10 }, 30));
						bulletFrame = 0;
						canShoot = false;
					}
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
			case SDLK_SPACE:
				canShoot = true;
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