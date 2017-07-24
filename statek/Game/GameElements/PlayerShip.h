//
// Created by wysocki on 24/07/2017.
//

#ifndef STATEK_PLAYERSHIP_H
#define STATEK_PLAYERSHIP_H


#include <Game/Interfaces/IPhysicsable.h>
#include <Game/Interfaces/Actor.h>
#include <Game/Interfaces/IRenderable.h>
#include <Game/Interfaces/ITickable.h>

class PlayerShip : public Actor, public IPhysicsable, public IRenderable, public ITickable {
public:
	static PlayerShip * CreateShip();
	
	PlayerShip(const btRigidBodyConstructionInfo &constructionInfo);
	
	virtual void ReactToCollision(IPhysicsable * other);
	
	virtual void Tick(float delta);
	
	float speed;
	float limit;
	
	btTypedConstraint * constraint;
	
	virtual glm::vec3 GetPosition();
	virtual glm::vec3 GetScale();
	virtual glm::vec3 GetRotation();

private:
	int timeBetweenSpawns;
	long long int prevSpawnTime;
	long long int currentTime;
	
};


#endif //STATEK_PLAYERSHIP_H
