//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_ASTEROID_H
#define STATEK_ASTEROID_H


#include <Game/Interfaces/Actor.h>
#include <Game/Interfaces/IPhysicsable.h>
#include <Game/Interfaces/IRenderable.h>
#include <Game/Interfaces/ITickable.h>

class btDefaultMotionState;
class btCollisionShape;
class AsteroidGenerator;

class Asteroid : public Actor, public IPhysicsable, public IRenderable, public ITickable {
public:
	static Asteroid * CreateAsteroid(glm::vec3 position, AsteroidGenerator * generator);

	virtual void ReactToCollision(IPhysicsable * other);
	
	AsteroidGenerator * generator;
	
	glm::vec3 rot;
	
	virtual glm::vec3 GetPosition();
	virtual glm::vec3 GetScale();
	virtual glm::vec3 GetRotation();
	
	virtual void Tick(float delta) override;
	
	void SetMesh(Mesh * mesh);
	
	float scaX;
	float scaY;
	float scaZ;
	
private:
	Asteroid(btRigidBodyConstructionInfo CI, AsteroidGenerator * generator);
	virtual ~Asteroid();
	
	
};


#endif //STATEK_ASTEROID_H
