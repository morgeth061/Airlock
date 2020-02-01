#pragma once
#ifndef __LEVEL__
#define __LEVEL__

#include "LevelNumber.h"
#include <vector>

using namespace std;

class Level
{
private:
	int Level1[15][29];

public:
	//ctor.
	Level();
	//de-ctor.
	~Level();

	//setters

	//getters
	vector<vector<int>> getLevel(int level);
	

	
};

#endif //defined __LEVEL__