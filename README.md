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
Author: Brandon Law
Date: Feb/25/2020
Descsription:
	-Added working health bar (scales according to player health)
	-Added visual for 7-slot inventory
	-Allowed UP and DOWN keys to be used to scroll right and left respectively through inventory bar
	-Added melee attack feature upon pressing F

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



----------
FSM CLASS
----------

FSM class
 Adapted from GBC GAME1017 SDL Template
 Editors:
 - Ryan Ethier
 - Sojung (Serena) Lee - Jan/23/2020
	- Updated background image with Robert's updated asset (larger resolution)

Author: Brandon Law
Date: Feb/25/2020
Descricption:
	-Loads 4 textures for player's health(2) and inventory(2)

----------
ENGINE CLASS
----------

Engine class
 Adapted from GBC GAME1011 SDL Template
 Editors:
 - Ryan Ethier
  - Sojung (Serena) Lee - Feb/1/2020
	- updated setGameWon (added exit code)


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


----------
BULLET CLASS
----------

Bullet Class
Fisayo Akinsulire
Date: Feb/10/2020
Descripton:
		-Added Bullet functionality