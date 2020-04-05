# Airlock
Airlock - by Rapid Fire Games


----------
GAME CLASS
----------

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
Author:Ryan Ethier
Date: Feb/16/2020
Description:
	- Allowed for level reset and respawn
Author:Sojung (Serena) Lee
Date: Feb/25/2020
Description:
	- Changed enemy and mineral objects to vectors (uses vector functions --> e.g. auto, pop_back, push_back, empty)
	- added playerAttack function
		- if player bullets hit enemies, enemies take damange and bullets disappear
		- enemy must be hit 4 times to disappear (Enemy health = 100, Bullet Damage = 25)
Author:Sojung (Serena) Lee
Date: Mar/08/2020
Description:
	- Added Shooting Up & Shooting Down Toggles
		- Press 'Q' to shoot upwards only
		- Press 'E' to shoot downwards only
		- To turn off shooting up, press 'Q' again & to turn off shooting down, press 'E' again
Author:Sojung (Serena) Lee
Date: Apr/05/2020
Description:
	- Added points label to show how much points earned in each level
	- updated deleteGameObjects (target = nullptr)
	- updated render (if target is not null, draw)
	- updated clean (doesn't destroy SDL anymore, just deletes game objects)
	- fixed mineral bug (only one mineral should be hit, not all)
	- updated levelChange (updates points when level changes)


----------
GAME OBJECT CLASS
----------

GameObject class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Definitions for Game Object methods
	- Defining GameObject constructor
	- Adapted by GBC GAME3001 Template v4
	- Helped create methods for objects (e.g. Enemy, Target)
		- e.g.) setPosition, getIsColliding, setSteeringState
Author: Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	- Added hit functions (get & set)
	

----------
COLLISION MANAGER CLASS
----------

Collision Manager class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Definitions for Collision Manager
	- Adapted from GBC GAME3001 Template v3
	- Checks collision box around game object --> using squaredRadiusCheck
		- if object is colliding with .... (switch statement) CASE: ______
		- e.g.) if target/player (object) is colliding with.... (switch statement) CASE: ENEMY,
					then cout << "ENEMY COLLISION" 
Author: Sojung (Serena) Lee
Date: Jan/31/2020
Description:
	- Added squareRadiansCheckObjects (for minerals or other game items only) --> has different (Smaller) radius than enemies
Author: Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	- Added ENEMY GameObjectType to squareRadiansCheckObjects (when enemy hits player through smaller radius)
		- smaller radius = enemy decreases player's health
		- larger radius = enemy seeks player


----------
MINERALS CLASS
----------

Minerals class
Author: Sojung (Serena) Lee
Date: Jan/31/2020
Description:
	- Added minerals class
	- created mineral object
	- placed mineral (Quartz1.png) into game state (screen)
	- Based on Enemy class
	- changed minerals icon (quartz) to larger resolution
Minerals class
Author: Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	- Added hit functions & set to false


----------
ENEMY CLASS
----------

Enemy class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Definitions for Enemy methods
	- Adapted from GBC GAME3001 Template v4 (using "ship.cpp")
	- Creates enemy constructor
	- Defines enemy draw, render, checkState, update, clean, move, max speed, check bounds, seek, check arrival functions
	- Draws enemies (using Assets)
	- MAkes enemy stay within boundaries --> using checkBounds function
		- e.g.) If enemy reaches negative Y axis, then set y axis = 0
Author:Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	 - added Hit get & set functions (bool)
	 - added get & set functions for name, damage, and health
	 - added Enemy resized (sent on Feb 5)
Author:Ryan Ethier
Date: Feb/16/2020
Description:
	 - Added spawn point variable for enemy re-spawning
Author:Sojung (Serena) Lee
Date: Mar/01/2020 & Mar/08/2020
Description:
	 - Updated enemy obstacle avoidance (enemy now moves around the purple islands & walls to seek player)


----------
FSM CLASS
----------

FSM class
 Adapted from GBC GAME1017 SDL Template
 Editors:
 - Ryan Ethier
 - Sojung (Serena) Lee - Jan/23/2020
	- Updated background image with Robert's updated asset (larger resolution)
Author: Sojung (Serena) Lee
Date: Mar/01/2020
Description:
	- Updated title state with play button & level select button
	- Added select level state (player chooses which level to start with)
Author: Sojung (Serena) Lee
Date: Apr/05/2020
Description:
	- Added win state (shows game won screen & total game score)
	- Updated GameState update (update points after winning game; exits while loop that controls game)
	- Added quit button in TitleState (game no longer exits by itself, now exits only through button)


----------
ENGINE CLASS
----------

Engine class
 Adapted from GBC GAME1011 SDL Template
 Editors:
 - Ryan Ethier
  - Sojung (Serena) Lee - Feb/1/2020
	- updated setGameWon (added exit code)
Author: Sojung (Serena) Lee
Date: Mar/01/2020
Description:
	- Added Mouse position (Up, down, motion) for buttons
Author: Sojung (Serena) Lee
Date: Apr/05/2020
Description:
	- removed setGameWon
	- updated handleEvents
		- if the user won the game, they can press any key to return to title state

----------
LEVEL CLASS
----------

Level class
Author: Ryan Ethier
Date: Feb/08/2020
Description:
	- Returns desired level grid


----------
TARGET CLASS
----------

Target class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Target means Player (same thing, but different title)
	- Definitions for Target methods
	- Adapted from GBC GAME3001 Template v4 (using "target.cpp")
	- Creates Target constructor
	- Defines Target draw, render, checkState, update, clean, move, check bounds functions
	- Able to change speed --> using m_move
	- Able to change their boundaries (move within certain area) --> using checkBounds
Author: Ryan Ethier
Date: Jan/31/2020
Description:
	- Added Level Class implementation
Author: Sojung (Serena) Lee
Date: Feb/1/2020
Description:
	- Changed player's sprite, original position, boundaries, and speed
Author: Ryan Ethier
Date: Feb/08/2020
Description:
	- Changed Level Class Implementation to use pointers
Author:Sojung (Serena) Lee
Date: Feb/11/2020
Description:
	- added Hit get & set functions (bool)
	- added get & set functions for name, damage, and health
Author:Sojung (Serena) Lee
Date: Mar/01/2020
Description:
	- Added won screen after player reaches exit (if levelarray == 3)
Author:Sojung (Serena) Lee
Date: Apr/05/2020
Description:
	- After player moves towards exit (levelArray == 3), show points to screen using label
	- If player finishes last level, set gameWon to true & exit game loop (in FSM)
	- OPTIONAL: If player lost all heath, added "Game Over" screen (commented temporarily)


----------
BULLET CLASS
----------

Bullet Class
Author: Fisayo Akinsulire
Date: Feb/10/2020
Descripton:
	- Added Bullet functionality
Author: Sojung (Serena) Lee
Date: Feb/25/2020
Descripton:
	- Changed bullet constructor (parameters uses SDL_Rect x & y instead of integers)
Author: Sojung (Serena) Lee
Date: Mar/08/2020
Descripton:
	- Added vertical shooting
		
----------
UTIL CLASS
----------

GameObject class
Author: Sojung (Serena) Lee
Date: Jan/23/2020
Description:
	- Definitions for Util methods
	- Adapted from GBC GAME3001 Template v4
	- Defines mathematical functions needed for movement of game objects (e.g. enemies, player/target)
		
----------
BUTTON CLASS
----------

Button class
Author: Sojung (Serena) Lee
Date: Mar/01/2020
Description:
	- Added bullet class
	- Adapted from GAME1017 Assignment 1 (Starting Project)
	- Defined play button, exit button, select level button, level 1 2 3 buttons

----------
CONFIG CLASS
----------

Config class
Author: Sojung (Serena) Lee
Date: Apr/05/2020
Description:
	- Added Config class for text and font manager
	- Adapted from GAME3001 Assignment 3
	
----------
FONT MANAGER CLASS
----------

Font Manager class
Author: Sojung (Serena) Lee
Date: Apr/05/2020
Description:
	- Added font manager class for text and label (replaced text manager)
	- Adapted from GAME3001 Assignment 3
	
----------
LABEL MANAGER CLASS
----------

Label class
Author: Sojung (Serena) Lee
Date: Apr/05/2020
Description:
	- Added label class for text
	- Adapted from GAME3001 Assignment 3
	
----------
TEXTURE MANAGER CLASS
----------

Texture Manager class
Author: Sojung (Serena) Lee
Date: Apr/05/2020
Description:
	- Updated texture manager (based on GAME3001 Template 10D)
	- Uses unordered map (not regular map) (uses shared ptr)
	- updated/changed load function
	- added drawText & addTexture functions