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


#include <Game/GameElements/TestObject.h>
#include <Game/GameElements/Asteroid.h>
#include <time.h>
#include <Game/GameElements/PlayerShip.h>

int main( void )
{
	srand (time(NULL));
	Game::Prepare();
    Game * gra = Game::GetGame();
	gra->renderer->LoadMesh("rock", "./Models/Rock");
	gra->renderer->LoadMesh("ship", "./Models/Ship");
	gra->renderer->LoadMesh("bullet", "./Models/Bullet");
	//TestObject obj;
	PlayerShip * ship = PlayerShip::CreateShip();
	//Asteroid * ast1 = Asteroid::CreateAsteroid(glm::vec3(0, 0, -5));
	//Asteroid * ast2 = Asteroid::CreateAsteroid(glm::vec3(5, 0, -10));
	//Asteroid * ast3 = Asteroid::CreateAsteroid(glm::vec3(0, 0, -5));
	//Asteroid * ast4 = Asteroid::CreateAsteroid(glm::vec3(5, 0, -5));
    gra->Begin();
    gra->Loop();
    gra->End();
	Game::Finish();
}

