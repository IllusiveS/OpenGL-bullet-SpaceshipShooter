//
// Created by wysocki on 22/07/2017.
//

#include "Asteroid.h"
#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <Graphics/Mesh.h>
#include <time.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <Game.h>
#include <Game/GameElements/AsteroidGenerator.h>

Asteroid * Asteroid::CreateAsteroid(glm::vec3 pos, AsteroidGenerator * generator) {
	float a = rand() % 180;
	float b = rand() % 180;
	float c = rand() % 180;
	
	float scaX = 0.5f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0-0.5f)));
	float scaY = 0.5f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0-0.5f)));
	float scaZ = 0.5f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0-0.5f)));
	
	btDefaultMotionState* asteroidMotionState = new btDefaultMotionState(btTransform(btQuaternion(a, b, c, 1), btVector3(pos.x, pos.y, pos.z)));
	btCollisionShape* asteroidShape = new btBoxShape(btVector3(scaX, scaY, scaZ));
	
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	asteroidShape->calculateLocalInertia(mass, fallInertia);
	
	btRigidBody::btRigidBodyConstructionInfo asteroidRigidbodyCI(mass, asteroidMotionState, asteroidShape, fallInertia);
	Asteroid* asteroid = new Asteroid(asteroidRigidbodyCI, generator);
	
	asteroid->setRestitution(1.0);
	
	asteroid->scaX = scaX;
	asteroid->scaY = scaY;
	asteroid->scaZ = scaZ;
	
	float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3)) - 1.5f;
	float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2)) + 3.0f;
	
	asteroid->setDamping(0, 0);
	
	asteroid->rot = glm::vec3(a, b, c);
	
	asteroid->activate(true);
	asteroid->applyCentralImpulse(btVector3(x, 0, y));
	asteroid->SetMesh(Game::GetGame()->renderer->retrieveMesh("rock"));
	asteroid->type = "asteroid";
	return asteroid;
}

Asteroid::Asteroid(btRigidBody::btRigidBodyConstructionInfo CI, AsteroidGenerator * generator) : IPhysicsable(CI), generator(generator) {

}

Asteroid::~Asteroid() {

}

void Asteroid::ReactToCollision(IPhysicsable *other) {
	if(other->type == "bullet"){
		Destroy();
		generator->AsteroidKilled();
	}
}

glm::vec3 Asteroid::GetPosition() {
	btTransform trans;
	getMotionState()->getWorldTransform(trans);
	btVector3 vec = trans.getOrigin();
	//printf("asteroid pos: %f, %f, %f \n", vec.x(), vec.y(), vec.z());
	return glm::vec3(vec.x(), vec.y(), vec.z());
}

glm::vec3 Asteroid::GetScale() {
	return glm::vec3(scaX, scaY, scaZ);
}

glm::vec3 Asteroid::GetRotation() {
	return glm::vec3();
}

void Asteroid::SetMesh(Mesh *mesh) {
	this->mesh = mesh;
}

void Asteroid::Tick(float delta) {
	glm::vec3 pos = GetPosition();
	if (pos.z > 13){
		generator->AsteroidKilled();
		Destroy();
	}
}
