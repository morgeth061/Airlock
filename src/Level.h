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
	array_type m_pLevel3Array;

	array_type m_pLevel1ObjectArray;
	array_type m_pLevel2ObjectArray;
	array_type m_pLevel3ObjectArray;
	
	array_type m_pLevelPtr;
	array_type m_pObjectPtr;

	//Singleton
	static Level* s_pInstance;

	//ctor.
	Level();
	//de-ctor.
	~Level();

public:

	//Singleton
	static Level* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Level();
			return s_pInstance;
		}

		return s_pInstance;
	}

	//setters
	void setLevel(int);
	void setObjects(int);
	
	//getters
	array_type* getLevel();
	array_type* getObjects();
	
};

#endif //defined __LEVEL__