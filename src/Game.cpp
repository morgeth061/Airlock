/*
 * GAME CLASS
 * - Runs game, selects level based off of FSM, etc...
 */

//Includes
#include "Game.h"
#include "Util.h"

//Defines
#define FPS 60

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

int Game::getMineralCounter()
{
	return mineralCounter;
}

int Game::getkeyCounter()
{
	return keyCounter;
}

void Game::setCurrentLevel(int level)
{
	m_currentLevel = level;
	Level::Instance()->setLevel(level);
	Level::Instance()->setObjects(level);

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
}

//de-ctor.
Game::~Game()
{
}

//Creates Game Objects
void Game::createGameObjects()
{
	cout << "CREATING GAME OBJECTS" << endl;

	//Player Creation/Update
	if (m_pTarget == nullptr)
		m_pTarget = new Target();
	
	m_pTarget->updateLevel();

	//Reset Counts
	numOfEnemies = 0;
	numOfMinerals = 0;
	numOfKeys = 0;

	//Update Level Objects
	Level::Instance()->setObjects(getCurrentLevel());
	m_objectPtr = Level::Instance()->getObjects();
	m_objectArray = *m_objectPtr;
	array_type currentArray = m_objectArray;

	//Spawn Objects
	for (int x = 0; x < 29; x++) //X Coordinate
	{
		for (int y = 0; y < 15; y++) //Y Coordinate
		{
			//cout << currentArray[y][x] << endl;
			if(currentArray[y][x] == 1) //Enemies
			{
				m_pEnemy.push_back(new Enemy());
				m_pEnemy[numOfEnemies]->setEnemySpawn(glm::vec2((x*64.0f)+32.0f, (y * 64.0f) + 32.0f));
				m_pEnemy[numOfEnemies]->setMaxSpeed(0.6f);
				numOfEnemies++;
				cout << "NEW ENEMY #" << numOfEnemies + 1 << " at (" << (x * 64.0f) + 32.0f << " , " << (y * 64.0f) + 32.0f << ")" << endl;
			}
			else if (currentArray[y][x] == 2) //Minerals
			{
				m_pMinerals.push_back(new Minerals());
				m_pMinerals[numOfMinerals]->setSpawnPoint(glm::vec2((x * 64.0f) + 32.0f, (y * 64.0f) + 32.0f));
				numOfMinerals++;
				cout << "NEW MINERAL #" << numOfMinerals << " at (" << (x * 64.0f) + 32.0f << " , " << (y * 64.0f) + 32.0f << ")" << endl;
			}
			else if (currentArray[y][x] == 3) //Breakable Rocks
			{

			}
			else if (currentArray[y][x] == 4) //Chests
			{
				m_pChests.push_back(new Chest());
				m_pChests[numOfChests]->setSpawnPoint(glm::vec2((x * 64.0f) + 32.0f, (y * 64.0f) + 32.0f));
				numOfChests++;
				cout << "NEW CHEST #" << numOfChests << " at (" << (x * 64.0f) + 32.0f << " , " << (y * 64.0f) + 32.0f << ")" << endl;
			}
			else if (currentArray[y][x] == 5) //Keys
			{
				m_pKeys.push_back(new Key());
				m_pKeys[numOfKeys]->setSpawnPoint(glm::vec2((x * 64.0f) + 32.0f, (y * 64.0f) + 32.0f));
				numOfKeys++;
				cout << "NEW KEY #" << numOfKeys << " at (" << (x * 64.0f) + 32.0f << " , " << (y * 64.0f) + 32.0f << ")" << endl;
				
			}
			else if (currentArray[y][x] == 9) //Player Spawn
			{
				m_pTarget->setPlayerSpawn(glm::vec2(x * 64.0f, y * 64.0f));
			}
		}
	}

	//Set Position for each object
	for (auto enemies : m_pEnemy)
	{
		enemies->setPosition(enemies->getEnemySpawn());
	}

	for (auto minerals : m_pMinerals)
	{
		minerals->setPosition(minerals->getSpawnPoint());
	}

	for (auto keys : m_pKeys)
	{
		keys->setPosition(keys->getSpawnPoint());
	}

	for (auto chests : m_pChests)
	{
		chests->setPosition(chests->getSpawnPoint());
	}

	m_pTarget->setPosition(m_pTarget->getPlayerSpawn());
}

void Game::deleteGameObjects()
{
	//m_pTarget = nullptr;

	if(m_pEnemy.empty() == false)
	{
		for (int count = 0; count < numOfEnemies; count++)
		{
			delete Instance()->m_pEnemy[count];
			Instance()->m_pEnemy[count] = nullptr;
		}
		m_pEnemy.erase(remove(m_pEnemy.begin(), m_pEnemy.end(), nullptr), m_pEnemy.end());
		m_pEnemy.shrink_to_fit();
		numOfEnemies = 0;
	}
	
	if(m_pMinerals.empty() == false)
	{
		for (int count = 0; count < numOfMinerals; count++)
		{
			delete Instance()->m_pMinerals[count];
			Instance()->m_pMinerals[count] = nullptr;
		}
		m_pMinerals.erase(remove(m_pMinerals.begin(), m_pMinerals.end(), nullptr), m_pMinerals.end());
		m_pMinerals.shrink_to_fit();
		Instance()->m_pMinerals.shrink_to_fit();
		numOfMinerals = 0;
	}

	if (m_pKeys.empty() == false)
	{
		for (int count = 0; count < numOfKeys; count++)
		{
			delete Instance()->m_pKeys[count];
			Instance()->m_pKeys[count] = nullptr;
		}
		m_pKeys.erase(remove(m_pKeys.begin(), m_pKeys.end(), nullptr), m_pKeys.end());
		m_pKeys.shrink_to_fit();
		Instance()->m_pKeys.shrink_to_fit();
		numOfKeys = 0;
	}

	if (m_pChests.empty() == false)
	{
		for (int count = 0; count < numOfChests; count++)
		{
			delete Instance()->m_pChests[count];
			Instance()->m_pChests[count] = nullptr;
		}
		m_pChests.erase(remove(m_pChests.begin(), m_pChests.end(), nullptr), m_pChests.end());
		m_pChests.shrink_to_fit();
		Instance()->m_pChests.shrink_to_fit();
		numOfChests = 0;
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
		else if (getCurrentLevel() == LEVEL3)
		{
			Texture::Instance()->draw("Level3", 0, 0, TheGame::Instance()->getRenderer(), false);
		}
		else if (getCurrentLevel() == DEBUG)
		{
			Texture::Instance()->draw("Debug", 0, 0, TheGame::Instance()->getRenderer(), false);			
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

		//Draw Keys
		for (auto keys : m_pKeys)
		{
			if(keys->getIsActive() == true)
			{
				keys->draw();
			}
		}

		//Draw Chests
		for (auto chests : m_pChests)
		{
			chests->draw();
		}
			
		//Draw player
		m_pTarget->draw();

		//Draw Health Bar
		Texture::Instance()->draw("playerHealthBack", 0, 0, TheGame::Instance()->getRenderer(), false);
		Texture::Instance()->draw("playerHealthBar", 100, 12, m_pTarget->getPlayerHealth() * 4, 40, TheGame::Instance()->getRenderer());

		//Draw Inventory
		Texture::Instance()->draw("playerInv", 715, 875, TheGame::Instance()->getRenderer(), false);
		Texture::Instance()->draw("invSMG", 715, 875, TheGame::Instance()->getRenderer(), false);
		if (getMineralCounter() > 0)
		{
			Texture::Instance()->draw("minerals", 715 + 64, 875, TheGame::Instance()->getRenderer(), false);
		}
		if (m_pTarget->getKeysHeld() > 0)
		{
			Texture::Instance()->draw("chestKey", 715 + (64 * 2), 875, TheGame::Instance()->getRenderer(), false);
		}
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
		//SoundManager::Instance()->playSound("playerHurt", 0);
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

	//Check for key/player collision
	for (auto keys : m_pKeys)
	{
		//cout << "KEY ";
		if (Collision::squaredRadiusCheck(m_pTarget, keys, 0.25f) && keys->getIsActive() == true)
		{
			
		}
	}

	//Check for key/player collision
	for (auto chests : m_pChests)
	{
		//cout << "KEY ";
		if (Collision::squaredRadiusCheck(m_pTarget, chests, 0.25f) && chests->getIsActive() == true)
		{

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

		for (auto keys : m_pKeys)
		{
			keys->m_reset();
		}

		for (auto chests : m_pChests)
		{
			chests->m_reset();
		}
	}
	//cout << m_pKeys[0]->getPosition().x / 64 << " " << m_pKeys[0]->getPosition().y /64 << endl;
	//cout << m_pKeys[0]->getIsActive() << " ";
	//cout << "Player Score: " << m_pTarget->getPlayerScore() << endl;
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
			mineralCounter += 1;
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
				SoundManager::Instance()->playSound("enemyHurt", 0);
				if (m_pEnemy[j]->getEnemyHealth() <= 0)
				{
					//if enemy health <= 0, enemy objects deleted
					m_bENull = true;
					delete m_pEnemy[j];
					m_pEnemy[j] = nullptr;
					numOfEnemies--;
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
				for (int i = 0; i < numOfEnemies; i++)
				{
					//if (Collision::squaredRadiusCheckObjects(m_pTarget, m_pEnemy[i]) && Collision::squaredRadiusCheck(m_pTarget, m_pEnemy[i]))
					if(Collision::squaredRadiusCheck(m_pTarget, m_pEnemy[i], (Util::distance(m_pTarget->getPosition(), m_pEnemy[i]->getPosition()))))
					{
						m_pEnemy[i]->setEnemyHealth((m_pEnemy[i]->getEnemyHealth())-25);
						cout << "ENEMY HIT" << " " << m_pEnemy[i]->getEnemyHealth() << endl;
						SoundManager::Instance()->playSound("playerSlash", 0);
						SoundManager::Instance()->playSound("enemyHurt", 0);
					}
				}
				break;
			case SDLK_q:
				for (auto bullets : BullVec) bullets->active = false;
				m_pTarget->bottom = false;
				if (m_pTarget->up == false)
				{
					m_pTarget->up = true;
				}
				else if (m_pTarget->up == true)
					m_pTarget->up = false;

				break;
			case SDLK_e:
				for (auto bullets : BullVec) bullets->active = false;
				m_pTarget->up = false;
				if (m_pTarget->bottom == false)
				{
					m_pTarget->bottom = true;
				}
				else if (m_pTarget->bottom == true)
					m_pTarget->bottom = false;

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
				for (int count = 0; count < numOfEnemies; count++)
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

						SoundManager::Instance()->playSound("playerShot1", 0);
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
					SoundManager::Instance()->playSound("playerHurt", 0);
				}
			}

			//If minerals collide with player.... what happens (add inventory?)
			for (int count = 0; count < numOfMinerals; count++)
			{
				//minerals disappear too slowly
				//if (m_pMinerals[count]->getIsHit() == true && CollisionManager::squaredRadiusCheckObjects(m_pTarget, m_pMinerals[count])) 
				//{
				//	m_pMinerals[count]->setPosition(glm::vec2(2000.0f, 2000.0f));
				//}
				
				//issue: enemies can 'steal' object (which shouldn't happen)
				if (m_pMinerals[count]->getIsHit() == true)
				{
					SoundManager::Instance()->playSound("playerPickup", 0);
					m_pMinerals[count]->setPosition(glm::vec2(2000.0f, 2000.0f));
					m_pMinerals[count]->setIsHit(false);
				}
			}

			for (int count = 0; count < numOfKeys; count++)
			{
				if (m_pKeys[count]->getIsHit() == true)
				{
					SoundManager::Instance()->playSound("playerPickup", 0);
					cout << "KEY COLLISION" << endl;
					m_pTarget->addKey();
					m_pKeys[count]->setIsActive(false);
					m_pKeys[count]->setIsHit(false);
				}
			}

			for (int count = 0; count < numOfChests; count++)
			{
				if (m_pChests[count]->getIsHit() == true)
				{
					//SoundManager::Instance()->playSound("playerPickup", 0);
					cout << "CHEST COLLISION" << endl;

					if(m_pTarget->getKeysHeld() > 0)
					{
						mineralCounter++;
						m_pChests[count]->m_openChest();
						m_pTarget->setKeysHeld(m_pTarget->getKeysHeld() - 1);
					}
					
				}
			}


			break;

			
		}
	}
}