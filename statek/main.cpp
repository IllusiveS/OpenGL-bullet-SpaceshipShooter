// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>
#include "Game.h"

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;


#include <time.h>
#include <Game/GameElements/PlayerShip.h>
#include <Game/GameElements/AsteroidGenerator.h>

int main( void )
{
	srand (time(NULL));
	Game::Prepare();
    Game * gra = Game::GetGame();
	gra->renderer->LoadMesh("rock", "./Models/Rock");
	gra->renderer->LoadMesh("ship", "./Models/Ship");
	gra->renderer->LoadMesh("bullet", "./Models/Bullet");
	//TestObject obj;
	gra->RestartScene();
    gra->Begin();
    gra->Loop();
    gra->End();
	Game::Finish();
}

