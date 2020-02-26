#pragma once
#ifndef __LEVEL__
#define __LEVEL__

#include "LevelNumber.h"
#include <array>

using namespace std;

typedef array<int, 29> row_type;
typedef array<row_type, 15> array_type;

class Level
{
private:
	array_type m_pLevel1Array;
	array_type m_pLevel2Array;
	array_type m_pLevelPtr;

public:
	//ctor.
	Level();
	//de-ctor.
	~Level();

	//setters
	void setLevel(int);
	//getters
	array_type* getLevel();
	
};

#endif //defined __LEVEL__