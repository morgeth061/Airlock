#include "Engine.h"


int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	//	Engine e; // Instance of our engine.
	//	return e.Run(); // Invokes Run() of the engine and stays in the function until engine is done.

	return Engine::Instance().Run();//Invokes Run() of the engine and stays in the function until engine is done
}
