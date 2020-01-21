/*
 * Main function for AIRLOCK
 * by Rapid Fire Games (division of Single Fire Games)
 *
 * Editors:
 * - Ryan Ethier
 */

//includes
#include "Engine.h"

//functions
int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	return Engine::Instance().Run();//Invokes Run() of the engine and stays in the function until engine is done
}
