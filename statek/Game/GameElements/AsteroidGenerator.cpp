//
// Created by wysocki on 24/07/2017.
//

#include <chrono>
#include <cstdlib>
#include "AsteroidGenerator.h"
#include "Asteroid.h"

void AsteroidGenerator::Tick(float delta){
	currentTime = std::chrono::system_clock::now().time_since_epoch().count();
	
	if(currentTime > prevSpawnTime + timeBetweenSpawns && asteroidsToSpawn > 0){
		float x = -15 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(15+15)));
		float y = 0;
		float z = 10;
		Asteroid::CreateAsteroid(glm::vec3(x, y, -13), this);
		asteroidsToSpawn--;
		prevSpawnTime += timeBetweenSpawns;
	}
}

AsteroidGenerator::AsteroidGenerator()
		: timeBetweenSpawns(1.0f), asteroidsToSpawn(5), prevSpawnTime(0.0f), currentTime(std::chrono::system_clock::now().time_since_epoch().count()) {
	
}

AsteroidGenerator::~AsteroidGenerator() {

}

void AsteroidGenerator::AsteroidKilled() {
	if ((rand() % 3) + 1 ==  2){
		asteroidsToSpawn++;
	}
	asteroidsToSpawn++;
}
