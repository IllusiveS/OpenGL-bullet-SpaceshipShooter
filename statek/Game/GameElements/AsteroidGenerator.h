//
// Created by wysocki on 24/07/2017.
//

#ifndef STATEK_ASTEROIDGENERATOR_H
#define STATEK_ASTEROIDGENERATOR_H


#include <Game/Interfaces/ITickable.h>
#include <Game/Interfaces/Actor.h>

class AsteroidGenerator : public Actor, public ITickable {
public:
	AsteroidGenerator();
	virtual ~AsteroidGenerator();
	
	void Tick(float delta) override;
	
	void AsteroidKilled();

private:
	float timeBetweenSpawns;
	float prevSpawnTime;
	float currentTime;
	int asteroidsToSpawn;
};


#endif //STATEK_ASTEROIDGENERATOR_H
