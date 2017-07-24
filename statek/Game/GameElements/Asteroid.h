//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_ASTEROID_H
#define STATEK_ASTEROID_H


#include <Game/Interfaces/Actor.h>
#include <Game/Interfaces/IPhysicsable.h>
#include <Game/Interfaces/IRenderable.h>

class btDefaultMotionState;
class btCollisionShape;

class Asteroid : public Actor, public IPhysicsable, public IRenderable {
public:
	static Asteroid * CreateAsteroid(glm::vec3 position);

	virtual void ReactToCollision(IPhysicsable * other);
	
	glm::vec3 rot;
	
	virtual glm::vec3 GetPosition();
	virtual glm::vec3 GetScale();
	virtual glm::vec3 GetRotation();
	
	void SetMesh(Mesh * mesh);
	
private:
	Asteroid(btRigidBodyConstructionInfo CI, btDefaultMotionState* state, btCollisionShape* collShape);
	virtual ~Asteroid();
};


#endif //STATEK_ASTEROID_H
